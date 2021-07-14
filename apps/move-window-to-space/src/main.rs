use common::{cleanup_spaces, collect_spaces, create_space, move_focused_window_to_space};

use clap::{AppSettings, Clap};

#[derive(Clap)]
#[clap(version = "1.0", author = "Vasiliy G. <kbknapp@gmail.com>")]
#[clap(setting = AppSettings::ColoredHelp)]
struct Options {
  desired_space: String,
  /// Space counts as empty, when these app-titles are in it. (use multiple time
  /// --ignore-apps=Teams --ignore-apps="Hidden Window"
  #[clap(long)]
  ignore_apps: Vec<String>
}

#[tokio::main]
async fn main() {
  let opts = Options::parse();
  let spaces = collect_spaces().await;

  if spaces.iter().any(|s| s.label == opts.desired_space) {
    move_focused_window_to_space(&opts.desired_space).await;
  } else {
    create_space(&spaces, &opts.desired_space).await;
    move_focused_window_to_space(&opts.desired_space).await;
    println!("need to create space");
  }

  cleanup_spaces(&opts.ignore_apps).await;
}
