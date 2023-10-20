/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "oneshot.h"
#include "swapper.h"

#define LA_SYM LT(SYMB, KC_SPC)
#define LA_ALT MO(ALT_ERGO)
#define LA_NAV LT(NAVI, KC_SPC)
#define CTL_Z CTL_T(KC_Z)
#define SLSH KC_BSLS // /
#define CTL_SL CTL_T(SLSH)
#define TRNS KC_TRNS


#define GRV KC_NUBS        // `
#define TILD S(KC_NUBS)       // ~
#define COMMA  KC_LBRC // ,
#define DOT    KC_RBRC // .
#define SCLN   S(KC_LBRC) // ;
#define CLN    S(KC_RBRC) // :
#define QUOT   KC_QUOT // '
#define DQUOT  S(KC_QUOT) // '
#define SLSH   KC_BSLS // /
#define BSLS   S(KC_BSLS) // back slash
#define HS     LALT(KC_M)  
#define YO     LALT(KC_T) 
#define SCHA   LALT(KC_I)  
#define HR   RSG(KC_SPC)  
#define HRS   RSG(KC_J)  

#define LA_EL    LT(ALT_ERGO_LEFT, CLN)
#define LA_EL_RU LT(ALT_ERGO_LEFT, KC_SCLN)
#define LA_ER    LT(ALT_ERGO_RIGHT, KC_A)

// Brackets
#define LBRK A(KC_F) // left bracket (
#define LCBK A(KC_D) // left curly bracket {
#define LSBK A(KC_S) // left square bracket [
#define LABK A(KC_A) // left angle bracket <
                        //
#define RBRK A(KC_J) // left bracket (
#define RCBK A(KC_K) // left curly bracket {
#define RSBK A(KC_L) // left square bracket [
#define RABK A(KC_SCLN) // left angle bracket <

enum keyboard_side {
  LEFT, RIGHT, UNSPECIFIED

};
enum layers {
    BASE, //7
    RUSSIAN, //8
    SYMB, // 9
    ALT_ERGO, // 9
    ALT_ERGO_LEFT, // 9
    ALT_ERGO_RIGHT, // 9
    NAVI, // 10
    _NUM

};
enum keycodes {
    // Custom oneshot mod implementation with no timers.
    OS_SHFT = SAFE_RANGE,
    OS_CTRL,
    OS_ALT,
    OS_CMD,

    SW_WIN,  // Switch to next window         (alt-tab)
    SW_TAB,  // Switch to next browser tab    (ctrl-tab)
    SW_RUS,
    SW_ENG,
    LEFT_SPACE,
    RIGHT_SPACE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_split_3x6_3(
      KC_NO  ,  KC_Q, KC_W, KC_E, KC_R, KC_T,                  KC_Y, KC_U, KC_I,     KC_O,   KC_P,   KC_NO,
      KC_NO  ,  LA_ER, KC_S, KC_D, KC_F, KC_G,                 KC_H, KC_J, KC_K,     KC_L,   LA_EL,  KC_NO,
      KC_LSFT, CTL_Z, KC_X, KC_C, KC_V, KC_B,                  KC_N, KC_M, KC_COMM,  KC_DOT, CTL_SL, KC_RSFT,
                          KC_NO,   KC_LSFT,  LA_NAV,     LA_SYM , KC_RSFT, LA_ALT

  ),

    [RUSSIAN] = LAYOUT_split_3x6_3(
      TRNS,       TRNS,    TRNS,    TRNS,    TRNS,    TRNS,                   TRNS,TRNS, TRNS, TRNS, TRNS   ,       TRNS,                   
      TRNS,       TRNS,    TRNS,    TRNS,    TRNS,    TRNS,                   TRNS,TRNS, TRNS, TRNS, LA_EL_RU,       TRNS,
      TRNS,       TRNS,    TRNS,    TRNS,    TRNS,    TRNS,                   TRNS,TRNS, TRNS, TRNS, CTL_T(KC_SLSH),TRNS,
                                          TRNS, TRNS,  TRNS,     TRNS,   TRNS, TRNS
  ),

    [SYMB] = LAYOUT_split_3x6_3(
      KC_NO, S(KC_1),S(KC_2),  S(KC_3), S(KC_4),    S(KC_5),                      S(KC_6),   S(KC_7),  S(KC_8),  S(KC_9),   S(KC_0), KC_NO,
      KC_NO, TILD,   GRV,     KC_QUOT,  S(KC_QUOT), KC_MINS,                      KC_PLUS,   OS_SHFT,  OS_CTRL,  OS_ALT,    OS_CMD,  KC_NO,
      KC_NO, BSLS,   KC_NO,   SCLN,     COMMA,      KC_UNDS,                      KC_EQL,    DOT,      CLN,      KC_NO,     SLSH,    KC_NO,
                          TRNS,   TRNS,  TRNS,     TRNS, TRNS, TRNS
  ),

    [ALT_ERGO] = LAYOUT_split_3x6_3(
      TRNS,   KC_NO,  KC_NO,  KC_NO,  KC_NO,  A(KC_T),                     KC_NO,   KC_NO,  A(KC_I), KC_NO,     KC_NO,   KC_NO,
      TRNS,   LABK,   LSBK,   LCBK,   LBRK,   KC_QUOT,                       S(KC_QUOT),   RBRK,   RCBK,    RSBK,      RABK,    KC_NO,
      TRNS,   KC_NO,  TRNS,   KC_NO,  KC_NO,  TRNS,                        TRNS,    A(KC_M),TRNS,    TRNS,      TRNS,    TRNS,
                                          TRNS, TRNS,  TRNS,     TRNS, TRNS, TRNS
  ),
    [ALT_ERGO_LEFT] = LAYOUT_split_3x6_3(
      TRNS,   KC_NO,  KC_NO,  KC_NO,  KC_NO,  A(KC_T),                     KC_NO, KC_NO,  A(KC_I), KC_NO, KC_NO, KC_NO,
      TRNS,   LABK,   LSBK,   LCBK,   LBRK,   KC_QUOT,                       KC_NO, KC_NO,  KC_NO,   KC_NO, TRNS,  KC_NO,
      TRNS,   KC_NO,  TRNS,   KC_NO,  KC_NO,  TRNS,                        TRNS,  A(KC_M),TRNS,    TRNS,  TRNS,  TRNS,
                                          TRNS, TRNS,  TRNS,     TRNS, TRNS, TRNS
  ),
    [ALT_ERGO_RIGHT] = LAYOUT_split_3x6_3(
      TRNS,   KC_NO,  KC_NO,  KC_NO,  KC_NO,  A(KC_T),                     KC_NO,   KC_NO,  A(KC_I), KC_NO,     KC_NO,   KC_NO,
      TRNS,   TRNS,   KC_NO,  KC_NO,  KC_NO,  KC_NO,                       S(KC_QUOT),   RBRK,   RCBK,    RSBK,      RABK,    KC_NO,
      TRNS,   KC_NO,  TRNS,   KC_NO,  KC_NO,  TRNS,                        TRNS,    A(KC_M),TRNS,    TRNS,      TRNS,    TRNS,
                                          TRNS, TRNS,  TRNS,     TRNS, TRNS, TRNS
  ),
    [NAVI] = LAYOUT_split_3x6_3(
      KC_NO,   KC_ESC,   KC_NO,   KC_NO,   KC_NO,   SW_RUS,                      SW_ENG,  KC_NO,   KC_NO, KC_BSPC,  KC_NO,   KC_NO,
      KC_NO,   OS_CMD,   OS_ALT,  OS_CTRL, OS_SHFT, KC_ENT,                      KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_SPC,  KC_NO,
      TRNS,    KC_TAB,   KC_NO,   KC_NO,   KC_NO,   KC_TAB,                      HR,   HRS,   KC_NO, KC_NO,    KC_NO,   KC_NO,
                                          TRNS,   TRNS,  TRNS,     TRNS, TRNS, TRNS
  ),
  [_NUM] = LAYOUT_split_3x6_3(
      KC_NO,   KC_1,    KC_P2,   KC_P3,   KC_P4,   KC_P5,                       KC_P6,   KC_P7,   KC_P8,   KC_P9,   KC_P0,     KC_NO,
      KC_NO,   OS_CMD,  OS_ALT,  OS_CTRL, OS_SHFT, KC_F11,                      KC_F12,  OS_SHFT, OS_CTRL, OS_ALT,  OS_CMD,    KC_NO,
      KC_NO,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,    KC_NO,
                                          TRNS,   TRNS,  TRNS,         TRNS, TRNS, TRNS
  ),
};

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case LA_SYM:
    case LA_NAV:
    case LA_ALT:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case LA_SYM:
    case LA_NAV:
    case LA_ALT:
    case KC_LSFT:
    case OS_SHFT:
    case OS_CTRL:
    case OS_ALT:
    case OS_CMD:
        return true;
    default:
        return false;
    }
}

bool sw_win_active = false;
bool sw_tab_active = false;

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;

void update_lang(uint16_t keycode, keyrecord_t *record) {
  uint16_t HYPER = MOD_BIT(KC_LSFT) | MOD_BIT(KC_LALT) | MOD_BIT(KC_LCTL) | MOD_BIT(KC_LGUI);
  switch (keycode) {
    case SW_RUS: {
      if (!record->event.pressed) {
        layer_on(RUSSIAN);
        register_mods(HYPER);
        register_code(KC_EQL);
        unregister_code(KC_EQL);
        unregister_mods(HYPER);
      }
      break;
    }
    case SW_ENG: {
      if (!record->event.pressed) {
        layer_off(RUSSIAN);
        register_mods(HYPER);
        register_code16(ALL_T(KC_MINS));
        unregister_code16(ALL_T(KC_MINS));
        unregister_mods(HYPER);
      }

      break;
    }
  }
}



uint8_t last_button_side = UNSPECIFIED;

void update_keyboard_side(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) { 
    last_button_side = UNSPECIFIED;
    switch (keycode) {
      case KC_Q:
      case KC_W:
      case KC_E:
      case KC_R:
      case KC_T:

      case KC_A:
      case KC_S:
      case KC_D:
      case KC_F:
      case KC_G:

      case KC_Z:
      case KC_X:
      case KC_C:
      case KC_V:
      case KC_B:

      case KC_1:
      case KC_2:
      case KC_3:
      case KC_4:
      case KC_5:
        last_button_side = LEFT;
        break;
      case KC_Y:
      case KC_U:
      case KC_I:
      case KC_O:
      case KC_P:

      case KC_H:
      case KC_J:
      case KC_K:
      case KC_L:
      case KC_SCLN:

      case KC_N:
      case KC_M:
      case KC_COMM:
      case KC_DOT:
      case KC_SLSH:

      case KC_6:
      case KC_7:
      case KC_8:
      case KC_9:
      case KC_0:
        last_button_side = RIGHT;
        break;

    }
  }

}

void process_spaces(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case RIGHT_SPACE:
      {
      uint8_t can_emit = (last_button_side == LEFT || last_button_side == UNSPECIFIED);
      if (record->event.pressed && can_emit) {
        register_code(KC_SPC);
        unregister_code(KC_SPC);
      }
      break;
      }
    case LEFT_SPACE:
      {
      uint8_t can_emit = last_button_side == RIGHT || last_button_side == UNSPECIFIED;
      if (record->event.pressed && can_emit) {
        register_code(KC_SPC);
        unregister_code(KC_SPC);
      }
      break;
      }
  }
  update_keyboard_side(keycode, record);

}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    update_swapper(
        &sw_win_active, KC_LCMD, KC_TAB, SW_WIN, OS_SHFT,
        keycode, record
    );
    update_swapper(
        &sw_tab_active, KC_LCTL, KC_TAB, SW_TAB, OS_SHFT,
        keycode, record
    );

    update_oneshot(
        &os_shft_state, KC_LSFT, OS_SHFT,
        keycode, record
    );
    update_oneshot(
        &os_ctrl_state, KC_LCTL, OS_CTRL,
        keycode, record
    );
    update_oneshot(
        &os_alt_state, KC_LALT, OS_ALT,
        keycode, record
    );
    update_oneshot(
        &os_cmd_state, KC_LCMD, OS_CMD,
        keycode, record
    );

    update_lang(keycode, record);

    process_spaces(keycode, record);

    return true;
}





layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, SYMB, NAVI, _NUM);
}


