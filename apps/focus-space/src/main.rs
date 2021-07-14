use clap::{AppSettings, Clap};
use common::{ collect_spaces, create_space, focus_space, cleanup_spaces };

#[derive(Clap, Debug)]
#[clap(version = "1.0", author = "Vasiliy G. <kbknapp@gmail.com>")]
#[clap(setting = AppSettings::ColoredHelp)]
struct Options {
  /// Space counts as empty, when these app-titles are in it. 
  /// Use multiple times:
  /// e.g --ignore-apps=Teams --ignore-apps="Hidden Window"
  #[clap(long)]
  ignore_apps: Vec<String>,
  desired_space: String,
}

#[tokio::main]
async fn main() {
  let opts = Options::parse();
  let spaces = collect_spaces().await;

  if spaces.iter().any(|s| s.label == opts.desired_space) {
    focus_space(&opts.desired_space).await;
  } else {
    create_space(&spaces, &opts.desired_space).await;
    focus_space(&opts.desired_space).await;
  }

  cleanup_spaces(&opts.ignore_apps).await;

}
