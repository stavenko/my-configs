use serde::{Deserialize, Serialize};
use super::bool_from_int::bool_from_int;

#[derive(Serialize, Deserialize)]
#[serde(rename_all = "kebab-case")]
pub struct Frame {
  x: f32,
  y: f32,
  w: f32,
  h: f32,
}
#[derive(Serialize, Deserialize)]
#[serde(rename_all = "kebab-case")]
pub struct Window {
  pub id: i32,
  pub pid: i16,
  pub app: String,
  pub title: String,
  pub frame: Frame,
  pub level: i16,
  pub role: String,
  pub subrole: String,
  #[serde(deserialize_with = "bool_from_int")]
  pub movable: bool,
  #[serde(deserialize_with = "bool_from_int")]
  pub resizable: bool,
  pub display: i16,
  pub space: i16,
  #[serde(deserialize_with = "bool_from_int")]
  pub visible: bool,
  #[serde(deserialize_with = "bool_from_int")]
  pub focused: bool,
  pub split: String,
  #[serde(deserialize_with = "bool_from_int")]
  pub floating: bool,
  #[serde(deserialize_with = "bool_from_int")]
  pub sticky: bool,
  #[serde(deserialize_with = "bool_from_int")]
  pub minimized: bool,
  #[serde(deserialize_with = "bool_from_int")]
  pub topmost: bool,
  pub opacity: f32,
  pub shadow: i16,
  pub border: i16,
  pub stack_index: i16,
  pub zoom_parent: i16,
  pub zoom_fullscreen: i16,
  pub native_fullscreen: i16,
}

