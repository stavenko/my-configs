mod space;
mod bool_from_int;
mod window;

pub use space::Space;
pub use window::Window;
use std::process::Stdio;
use tokio::io::{AsyncBufReadExt, BufReader};
use tokio::process::Command;


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

pub async fn enumerate_spaces() {
  let spaces = collect_spaces().await;

  for (id, space) in spaces.iter().filter(|space| !space.native_fullscreen).enumerate() {

    if space.label.is_empty() {
      let name = get_space_name((id+1) as i32);
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


pub async fn focus_space(label: &str) {
  let mut cmd = Command::new("yabai");

  cmd
    .arg("-m")
    .arg("space")
    .arg(label)
    .arg("--focus")
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

  run_command(cmd).await;
  let new_spaces = collect_spaces().await;
  if let Some(new_space) = new_spaces
    .iter()
    .find(|s| spaces.iter().position(|ss| ss.index == s.index).is_none())
  {
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

fn is_empty_space(space: &Space, ignored_window_ids: &[i32]) -> bool {
  let windows_left = space.windows.iter()
    .filter(|id| !ignored_window_ids.contains(id))
    .count();

  println!("windows_left {:?}, original {:?}", windows_left, space.windows); 

  !space.focused && windows_left == 0
}

pub async fn cleanup_spaces(ignore_apps_titles: &[String]) {
  let windows_to_ignore = collect_windows().await.into_iter()
    .filter(|win| ignore_apps_titles.contains(&win.title))
    .map(|win| win.id)
    .collect::<Vec<_>>();


  let spaces: Vec<Space> = collect_spaces()
    .await
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

  for space in spaces.into_iter() {
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
#[cfg(test)]
mod tests {
  #[test]
  fn it_works() {
    assert_eq!(2 + 2, 4);
  }
}
