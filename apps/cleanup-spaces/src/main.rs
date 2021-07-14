use clap::{AppSettings, Clap};
use common::cleanup_spaces;

#[derive(Clap, Debug)]
#[clap(version = "1.0", author = "Vasiliy G. <kbknapp@gmail.com>")]
#[clap(setting = AppSettings::ColoredHelp)]
struct Options {
  /// Space counts as empty, when these app-titles are in it. (use multiple time
  /// --ignore-apps=Teams --ignore-apps="Hidden Window"
  #[clap(long)]
  ignore_apps: Vec<String>
}

#[tokio::main]
async fn main() {
  let opts = Options::parse();
  cleanup_spaces(&opts.ignore_apps).await;
}
