#include QMK_KEYBOARD_H
#include "version.h"
#define MOUSEKEY_WHEEL_MAX_SPEED 1
#define MOUSEKEY_WHEEL_TIME_TO_MAX 200

#define BASE 0 // default layer
#define RUSSIAN 1
#define SYMB 2 // symbols
#define MDIA 3 // media keys
#define NAVI 4 // Navigation layer

enum {
  QUOTES_DBLQUOTES,
  SLASH_BACKSLASH,
  RUSSIAN_YO_QSTN,
  RUSSIAN_YO_E,
  RUSSIAN_YO_E_VIM,
  RUSSIAN_HARD_SOFT,
};

enum custom_keycodes {
  EPRM = SAFE_RANGE,
  VRSN,
  RGB_SLD,
  SWITCH_RUSSIAN,
  SWITCH_ENGLISH,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,----------------------------------------------------.       ,--------------------------------------------------.
 * |   =    |   1  |   2  |   3  |   4  |   5  | SW_RUS |       |  SW_ENG |   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+---------------|       |---------+------+------+------+------+------+--------|
 * | -> MDIA|   Q  |   W  |   E  |   R  |   T  |   Ё    |       |   ъ     |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|        |       |         |------+------+------+------+------+--------|
 * | -> NAV |   A  |   S  |   D  |   F  |   G  |--------|       |---------|   H  |   J  |   K  |   L  |; / L2|' / Cmd |
 * |--------+------+------+------+------+------| Hyper  |       |   Meh   |------+------+------+------+------+--------|
 * | LShift |Z/Ctrl|   X  |   C  |   V  |   B  |        |       |         |   N  |   M  |   ,  |   .  |//Ctrl| RShift |
 * `--------+------+------+------+------+---------------'       `-------------+------+------+------+------+--------'
 *   |LGUI  | LALT |      |      | esc  |                                     |      |      |      | RALT | RGUI |
 *   `----------------------------------'                                     `----------------------------------'
 *                                        ,-------------.       ,---------------
 *                                        | App  | LGui |       | Alt  |  Esc   |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 | Space|Backsp|------|       |------|  Tab   |Enter |
 *                                 |      |ace   |->Symb|       |->Symb|        |      |
 *                                 |      |      |      |       |      |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_EQL,         KC_1,         KC_2,   KC_3,   KC_4,   KC_5,   SWITCH_RUSSIAN,
        MO(MDIA),        KC_Q,         KC_W,   KC_E,   KC_R,   KC_T,   KC_TILD,
        MO(NAVI),        KC_A,         KC_S,   KC_D,   KC_F,   KC_G,
        KC_LSFT,        CTL_T(KC_Z),  KC_X,   KC_C,   KC_V,   KC_B,   KC_HYPR,
        KC_LGUI,KC_LALT,      KC_NO,  KC_MEH, KC_ESC,
                                              ALT_T(KC_APP),  KC_LGUI,
                                                              KC_HOME,
                                               KC_SPC,KC_BSPC,MO(SYMB),
        // right hand
             SWITCH_ENGLISH,     KC_6,   KC_7,  KC_8,   KC_9,   KC_0,             KC_MINS,
             KC_RBRC,      KC_Y,   KC_U,  KC_I,   KC_O,   KC_P,             KC_BSLS,
                            KC_H,   KC_J,  KC_K,   KC_L,   KC_SCLN, KC_QUOT ,
             KC_HYPR,  KC_N,  KC_M,  KC_COMM,KC_DOT, CTL_T(KC_SLSH),   KC_RSFT,
                                  KC_ESC, KC_MEH,KC_NO,  KC_RALT,          KC_RGUI,
             KC_LALT,        KC_ESC,
             KC_PGUP,
             MO(SYMB), KC_TAB, KC_ENT
    ),
/* Keymap 1: Russian Layer - made to replace some things to make it possible to type russian language
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |         |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |      |      |      |      |      |  Ё   |           | Ъ    |      |      |      |      | p(3) |   [(x) |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |      |      |      |      |      |------|           |------|      |      |      |      |  ;   |   '(ee)|
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  LShift |      |      |      |      |      |      |           |      |      |      |      |      |  \   | RShift |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |       |      |      |      |      |                                       |      |      |      |      |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// Russian layout helper
[RUSSIAN] = LAYOUT_ergodox(
       // left hand
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_BSLS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
       KC_LSFT,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
          KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                               KC_TRNS,KC_TRNS,KC_TRNS,
       // right hand
       KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
       KC_RBRC, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_P   ,KC_LBRC,
                KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_SCLN,KC_QUOT,
       KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS /*TD(RUSSIAN_YO_QSTN)*/,KC_RSFT,
                        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
/* Keymap 1: Symbol Layer 
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |         |  f1  |  f2  |  f3  |  f4  |  f5  |  f6  |           |      |  f7  |  f8  |  f9  | f10  |  f11 |  f12   |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |  !   |  @   |  #   |  $   |  %   |      |           |      |  ^   |  &   |   *  |  -   |   +  |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |  <   |  [   |  {   |  (   |  `   |------|           |------| ' "  |  )   |   }  |  ]   |   >  |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |      |      |  ?   |  ~   |      |      |           |      |      |  =   |  /\  |      |      |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |       |      |      |      |      |                                       |      |      |      |      |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |Animat|      |       |Toggle|Solid |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |Bright|Bright|      |       |      |Hue-  |Hue+  |
 *                                 |ness- |ness+ |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[SYMB] = LAYOUT_ergodox(
       // left hand
       KC_TRNS,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5, KC_F6,
       KC_TRNS,KC_EXLM,KC_AT,  KC_HASH,KC_DLR,KC_PERC,KC_TRNS,
       KC_TRNS,KC_LABK,KC_LBRC,KC_LCBR,KC_LPRN,KC_GRV,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_QUES,KC_TILD,KC_TRNS,KC_TRNS,
          EPRM,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                       RGB_MOD,KC_TRNS,
                                               KC_TRNS,
                               RGB_VAD,RGB_VAI,KC_TRNS,
       // right hand
       KC_TRNS, KC_F7,   KC_F8,  KC_F9,   KC_F10,   KC_F11,  KC_F12,
       KC_TRNS, KC_CIRC,   KC_AMPR,   KC_ASTR,    KC_MINS,    KC_PLUS, KC_TRNS,
                TD(QUOTES_DBLQUOTES),KC_RPRN,KC_RCBR,KC_RBRC,KC_RABK,KC_TRNS,
       KC_TRNS, KC_TRNS, TD(SLASH_BACKSLASH),   KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS,
                         KC_TRNS,KC_TRNS,  KC_TRNS,    KC_TRNS,  KC_TRNS,
       RGB_TOG, RGB_SLD,
       KC_TRNS,
       KC_TRNS, RGB_HUD, RGB_HUI
),

/* Keymap NAVI: Navigation layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           | D <- | Home | pg_dw| pg_up| End  |      | D ->   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------| left | down |  up  | right|      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[NAVI] = LAYOUT_ergodox(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_TRNS, KC_TRNS,
                 KC_LEFT, KC_DOWN, KC_UP  , KC_RIGHT, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      | LKM  | MKM  |RKM   | scrlu|        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------| MLeft|MDown | Mup  |MRight| scrld|  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      | Prev | Next |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |VolUp |VolDn | Mute |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |Brwser|
 *                                 | lkm  | rkm  |------|       |------|      |Back  |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[MDIA] = LAYOUT_ergodox(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_BTN1, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_BTN1, KC_BTN3, KC_BTN2, KC_WH_D, KC_TRNS,
                 KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_WH_U, KC_MPLY,
       KC_TRNS,  KC_TRNS, KC_WH_L, KC_WH_R, KC_NO,   KC_TRNS, KC_TRNS,
                          KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
};

const uint16_t PROGMEM fn_actions[] = {
    // [1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [QUOTES_DBLQUOTES]  = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, KC_DQUO),
  [SLASH_BACKSLASH]  = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, KC_BSLS),
  [RUSSIAN_YO_QSTN]  = ACTION_TAP_DANCE_DOUBLE(KC_BSLS, KC_SLSH),
  [RUSSIAN_YO_E]  = ACTION_TAP_DANCE_DOUBLE(KC_T, KC_BSLS),
  [RUSSIAN_YO_E_VIM]  = ACTION_TAP_DANCE_DOUBLE(KC_T, KC_TILD),
  [RUSSIAN_HARD_SOFT]  = ACTION_TAP_DANCE_DOUBLE(KC_M, KC_RBRC)
};


uint16_t actualKeyPressed = 0;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  uint16_t HYPER = MOD_BIT(KC_LSFT) | MOD_BIT(KC_LALT) | MOD_BIT(KC_LCTRL) | MOD_BIT(KC_LGUI);
  switch (keycode) {
    case SWITCH_RUSSIAN: {
      if (!record->event.pressed) {
        layer_on(RUSSIAN);
        register_mods(HYPER);
        register_code(KC_EQL);
        unregister_code(KC_EQL);
        unregister_mods(HYPER);
      }
      return false;
    }
    case SWITCH_ENGLISH: {
      if (!record->event.pressed) {
        layer_off(RUSSIAN);
        register_mods(HYPER);
        register_code16(ALL_T(KC_MINS));
        unregister_code16(ALL_T(KC_MINS));
        unregister_mods(HYPER);
      }

      return false;
    }
    #ifdef RGBLIGHT_ENABLE
    case RGB_SLD:
      if (record->event.pressed) {
        rgblight_mode(1);
        return false;
      }
    break;
    #endif
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
#ifdef RGBLIGHT_COLOR_LAYER_0
  rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
};

// Runs whenever there is a layer state change.
uint32_t layer_state_set_user(uint32_t state) {
  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();

  uint8_t layer = biton32(state);
  switch (layer) {
      case 0:
        #ifdef RGBLIGHT_COLOR_LAYER_0
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
        #else
        #ifdef RGBLIGHT_ENABLE
          rgblight_init();
        #endif
        #endif
        break;
      case 1:
        ergodox_right_led_1_on();
        #ifdef RGBLIGHT_COLOR_LAYER_1
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_1);
        #endif
        break;
      case 2:
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_2
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_2);
        #endif
        break;
      case 3:
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_3
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_3);
        #endif
        break;
      case 4:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_4
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_4);
        #endif
        break;
      case 5:
        ergodox_right_led_1_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_5
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_5);
        #endif
        break;
      case 6:
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_6
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        break;
      case 7:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_7
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_7);
        #endif
        break;
      default:
        break;
    }

  return state;
};
