mod space;
mod bool_from_int;
mod window;

pub use space::Space;
pub use window::Window;
use std::collections::HashMap;
use std::process::Stdio;
use std::time::Duration;
use tokio::io::{AsyncBufReadExt, BufReader};
use tokio::time::sleep;
use tokio::process::Command;


fn parse_label(item: &str)->i32 {
  match item {
    "one" => 1,
    "two" => 2,
    "three" => 3,
    "four" => 4,
    "five" => 5,
    "six" => 6,
    "seven" => 7,
    "eight" => 8,
    "nine" => 9,
    "ten" => 10,
    _ => -1,
  }
}
fn get_space_name(id: i32)->String {
  match id {
    1 => "one".into(),
    2 => "two".into(),
    3 => "three".into(),
    4 => "four".into(),
    5 => "five".into(),
    6 => "six".into(),
    7 => "seven".into(),
    8 => "eight".into(),
    9 => "nine".into(),
    10 => "ten".into(),
    id => format!("Display-{}",id)
  }
}


fn find_smallest_gap(labels: &[i32]) -> i32 {
  let mut set = Vec::new();
  for i in 1..11 {
    if !labels.contains(&i) {
      set.push(i);
    }
  }
  set.sort_unstable();
  println!("exist labels {:?}, created set {:?}", labels, set );
  set[0]
}



pub async fn enumerate_spaces() {
  let spaces = collect_spaces().await;
  let mut labels = spaces.iter()
    .map(|s| parse_label(&s.label))
    .filter(|id| *id > 0)
    .collect::<Vec<_>>();


  for space in spaces.iter().filter(|space| !space.native_fullscreen) {

    if space.label.is_empty() {
      let gap = find_smallest_gap(&labels);
      let name = get_space_name((gap) as i32);
      labels.push(gap);
      let mut cmd = Command::new("yabai");

      cmd
        .arg("-m")
        .arg("space")
        .arg(format!("{}", space.index))
        .arg("--label")
        .arg(&name)
        .stdout(Stdio::piped());

      run_command(cmd).await;
    }
  }
}
pub async fn run_command(mut cmd: Command) -> String {
  let mut child = cmd.spawn().expect("Failed to spawn child");

  let stdout = child.stdout.take().expect("can not take stdout");
  let mut reader = BufReader::new(stdout).lines();

  tokio::spawn(async move {
    child.wait().await.expect("Command ended with error");
  });

  let mut buffer: Vec<String> = Vec::new();
  while let Some(line) = reader.next_line().await.unwrap() {
    buffer.push(line)
  }

  buffer.join("\n")
}

pub async fn collect_spaces() -> Vec<Space> {
  let mut cmd = Command::new("yabai");

  cmd
    .arg("-m")
    .arg("query")
    .arg("--spaces")
    .stdout(Stdio::piped());

  let result = run_command(cmd).await;

  serde_json::from_str(&result).expect("Cannot parse result")
}

async fn collect_spaces_on_display(display_id: i16) -> Vec<Space> {
  let mut cmd = Command::new("yabai");

  cmd
    .arg("-m")
    .arg("query")
    .arg("--spaces")
    .arg("--display")
    .arg(format!("{}", display_id ))
    .stdout(Stdio::piped());

  let result = run_command(cmd).await;

  serde_json::from_str(&result).expect("Cannot parse result")
}


pub async fn focus_space(label: &str) {
  let mut cmd = Command::new("yabai");
  cmd
    .arg("-m")
    .arg("space")
    .arg("--focus")
    .arg(label)
    .stdout(Stdio::piped());
  run_command(cmd).await;
}

pub async fn collect_windows() -> Vec<Window> {
  let mut cmd = Command::new("yabai");

  cmd
    .arg("-m")
    .arg("query")
    .arg("--windows")
    .stdout(Stdio::piped());

  let result = run_command(cmd).await;

  serde_json::from_str(&result).expect("Cannot parse result")
}

pub async fn move_focused_window_to_space(space_label: &str) {
  let mut cmd = Command::new("yabai");
  cmd
    .arg("-m")
    .arg("window")
    .arg("--space")
    .arg(space_label)
    .stdout(Stdio::piped());

  run_command(cmd).await;
}

pub async fn create_space(spaces: &[Space], space_label: &str) {
  let mut cmd = Command::new("yabai");
  cmd
    .arg("-m")
    .arg("space")
    .arg("--create")
    .stdout(Stdio::piped());


  for space in spaces{
    println!("Before {:?}", space); 
  }

  run_command(cmd).await;
  let new_spaces = collect_spaces().await;
  for space in new_spaces.iter(){
    println!("After {:?}", space); 
  }
  if let Some(new_space) = new_spaces
    .iter()
    .find(|s| s.label.is_empty())
  {
    println!("put label {} on space {}", space_label, new_space.index);
    let mut cmd = Command::new("yabai");
    cmd
      .arg("-m")
      .arg("space")
      .arg(format!("{}", new_space.index))
      .arg("--label")
      .arg(space_label)
      .stdout(Stdio::piped());
    run_command(cmd).await;
  }
}


fn spaces_per_display(spaces: &[Space])->HashMap<i16, i32> {
  let mut result = HashMap::new();
  for space in spaces {
    #[allow(clippy::map_entry)] 
    if result.contains_key(&space.display) {
      if let Some(x) = result.get_mut(&space.display){
        *x += 1;
      }
    } else {
      result.insert(space.display, 1);
    }

  }
  result
}

pub async fn wait_until_focused(label: &str) {
  loop {
    if let Some(space) = collect_spaces().await.into_iter().find(|space| space.label == label) {
      if space.visible {
        break;
      }
    } else {
      panic!("no such space with label {}", label);
    }
    sleep(Duration::from_millis(100)).await
  }
}


fn is_empty_space(space: &Space, ignored_window_ids: &[i32]) -> bool {
  let windows_left = space.windows.iter()
    .filter(|id| !ignored_window_ids.contains(id))
    .count();

  if space.index ==3 {
    println!("space to check {:?}", space);
  }

  !space.visible && windows_left == 0
}

pub async fn cleanup_spaces(ignore_apps_titles: &[String]) {
  let windows_to_ignore = collect_windows().await.into_iter()
    .filter(|win| ignore_apps_titles.contains(&win.title))
    .map(|win| win.id)
    .collect::<Vec<_>>();


  let all_spaces = collect_spaces()
    .await;
  let spaces_per_display = spaces_per_display(&all_spaces);
  let spaces: Vec<Space> = all_spaces
    .into_iter()
    .filter(|s| {
      is_empty_space(s, &windows_to_ignore)
    })
    .collect();

  if !spaces.is_empty() {
    println!(
      "Spaces to remove {}",
      spaces
        .iter()
        .map(|s| format!("{}", s.index))
        .collect::<Vec<_>>()
        .join(" ")
    );
  }
  println!("spaces per display {:?}", spaces_per_display);

  for space in spaces.into_iter() {
    if spaces_per_display[&space.display] > 1 {
      let mut cmd = Command::new("yabai");
      cmd
        .arg("-m")
        .arg("space")
        .arg(format!("{}", space.index))
        .arg("--destroy")
        .stdout(Stdio::piped())
        ;
      
      run_command(cmd).await;
    }
  }
}
#[cfg(test)]
mod tests {
  #[test]
  fn it_works() {
    assert_eq!(2 + 2, 4);
  }
}
