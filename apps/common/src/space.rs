use serde::de::{self, Deserializer, Unexpected};
use serde::{Deserialize, Serialize};
use super::bool_from_int::bool_from_int;

#[derive(Serialize, Deserialize)]
#[serde(rename_all = "kebab-case")]
pub struct Space {
  pub id: i16,
  pub label: String,
  pub index: i32,
  pub display: i16,
  pub windows: Vec<i32>,
  #[serde(rename = "type")]
  pub tp: String,

  #[serde(deserialize_with = "bool_from_int")]
  pub visible: bool,
  #[serde(deserialize_with = "bool_from_int")]
  pub focused: bool,
  #[serde(deserialize_with = "bool_from_int")]
  pub native_fullscreen: bool,
  pub first_window: i32,
  pub last_window: i32,
}

