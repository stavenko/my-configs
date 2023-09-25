#include QMK_KEYBOARD_H

#include "oneshot.h"
#include "swapper.h"

#define RESET QK_BOOT

#define XXXX KC_NONE

#define LA_SYM MO(_SYM)
#define LA_ALT MO(_ALT)
#define LA_NAV MO(_NAV)
#define LA_GFN MO(_GFN)

// #define PIPE S(KC_BSLS)
// #define DPIPE S(RALT(KC_BSLS))
#define GRV KC_NUBS        // `
#define TILD S(KC_NUBS)       // ~
// #define BSL RALT(KC_BSLS)
#define COMMA KC_LBRC // ,
#define DOT KC_RBRC // .
#define SCLN S(KC_LBRC) // ;
#define CLN S(KC_RBRC) // :
#define QUOT KC_QUOT // '
#define DQUOT S(KC_QUOT) // '
#define SLSH KC_BSLS // /
#define BSLS S(KC_BSLS) // back slash
#define HS LALT(KC_M)  
#define YO LALT(KC_T) 
#define SCHA LALT(KC_I)  

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

#define SPACE_L C(KC_LEFT)
#define SPACE_R C(KC_RGHT)

#define TAB_L C(S(KC_TAB))
#define TAB_R C(KC_TAB)


// Features to adapt plan:
// 1. move backspace on symb with opt, set bcsp KC_NO
// 2. move russian keycodes щ з х
// 2.a use it for 1-2 weeks
// 
// 2. move esc to backspace - use for 1-2 week
// 2. move ent, tab to SYMB+G
// 3. Adapt
//
// 4. Create alt layer for brackets - put it on enter
// 5. remove brackets from symb layer

enum layers {
    _DEF, // 0 
    _GAM, 
    _GFN,
    _SYM,
    _NAV,
    _NUM,
    _ALT, //6

    BASE, //7
    RUSSIAN, //8
    SYMB, // 9
    NAVI // 10

};

enum tap_dances{
  QUOTES_DBLQUOTES,
};

enum keycodes {
    // Custom oneshot mod implementation with no timers.
    OS_SHFT = SAFE_RANGE,
    OS_CTRL,
    OS_ALT,
    OS_CMD,

    SW_WIN,  // Switch to next window         (alt-tab)
    SW_TAB,  // Switch to next browser tab    (ctrl-tab)
    RGB_SLD,
    SWITCH_RUSSIAN,
    SWITCH_ENGLISH,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_DEF] = LAYOUT_ergodox(
        KC_NO,   KC_NO,    KC_NO,    KC_NO,  KC_NO,   KC_NO,    KC_NO, 
        KC_NO,   KC_Q,     KC_W,     KC_E,   KC_R,    KC_T,     KC_NO, 
        KC_NO,   KC_A,     KC_S,     KC_D,   KC_F,    KC_G,
        KC_NO,   KC_Z,     KC_X,     KC_C,   KC_V,    KC_B,     KC_NO, 
        KC_NO,   KC_NO,    KC_NO,    KC_NO,  KC_NO,
                                                      KC_NO,    DF(BASE),  
                                                                KC_NO, 
                                             KC_ESC,  KC_SPC,  LA_NAV,

        // right hand
        KC_NO,   KC_NO,   KC_NO,  KC_NO,    KC_NO,   KC_NO,     KC_NO,
        KC_NO,   KC_Y,    KC_U,   KC_I,     KC_O,    KC_P,      KC_NO,
                 KC_H,    KC_J,   KC_K,     KC_L,    KC_SCLN,   KC_NO,
        KC_NO,   KC_N,    KC_M,   KC_COMM,  KC_DOT,  KC_SLSH,   KC_NO,
                          KC_NO,  KC_NO,    KC_NO,   KC_NO,     KC_NO,
        KC_NO,   KC_NO,
        KC_NO,
        LA_SYM,  KC_LSFT,  LA_ALT
),
[_SYM] = LAYOUT_ergodox(
       // left hand
        KC_NO,   KC_NO,   KC_NO,    KC_NO,   KC_NO,   KC_NO,    KC_NO, 
        KC_NO,   S(KC_1), S(KC_2),  S(KC_3), S(KC_4), S(KC_5),  KC_NO, 
        KC_NO,   SCLN,    GRV,      QUOT,    DQUOT,   KC_MINS,
        KC_NO,   BSLS,    TILD,    SCLN,    COMMA ,  KC_UNDS,    KC_NO, 
        KC_NO,   KC_NO,    KC_NO,    KC_NO,  KC_NO,
                                                      KC_NO,    KC_NO,  
                                                                KC_NO, 
                                             KC_TRNS,  KC_TRNS,  KC_TRNS,

        // right hand
        KC_NO,   KC_NO,   KC_NO,  KC_NO,    KC_NO,   KC_NO,     KC_NO,
        KC_NO,   S(KC_6), S(KC_7),S(KC_8),  S(KC_9), S(KC_0),  KC_NO,
                 KC_PLUS, OS_SHFT, OS_CTRL, OS_ALT,  OS_CMD,    KC_NO,
        KC_NO,   KC_EQL,  DOT,     CLN,     KC_NO,   SLSH,      KC_NO,
                          KC_NO,  KC_NO,    KC_NO,   KC_NO,     KC_NO,
        KC_NO,   KC_NO,
        KC_NO,
        KC_TRNS,   KC_TRNS,  KC_TRNS
),
[_NAV] = LAYOUT_ergodox(
       // left hand
        KC_NO,   KC_NO,    KC_NO,    KC_NO,  KC_NO,   KC_NO,    KC_NO, 
        KC_NO,   SW_TAB,  SW_WIN,  TAB_L,    TAB_R,   KC_ESC,   KC_NO, 
        KC_NO,   OS_CMD,  OS_ALT,  OS_CTRL,  OS_SHFT, KC_ENT,
        KC_NO,   SPACE_L, SPACE_R, DF(_GAM), KC_PSCR, KC_TAB,   KC_NO, 
        KC_NO,   KC_NO,    KC_NO,    KC_NO,  KC_NO,
                                                      KC_NO,    KC_NO,  
                                                                KC_NO, 
                                             KC_TRNS,  KC_TRNS,  KC_TRNS,

        // right hand
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,     KC_NO,
        KC_NO,   KC_ESC,  KC_HOME, KC_END,  KC_BSPC, KC_DEL,     KC_NO,
                 KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_NO,    KC_NO,
        KC_NO,   KC_TAB,  KC_PGUP, KC_PGDN, XXXXXXX, XXXXXXX,    KC_NO,
                          KC_NO,  KC_NO,    KC_NO,   KC_NO,     KC_NO,
        KC_NO,   KC_NO,
        KC_NO,
        KC_TRNS,   KC_TRNS,  KC_TRNS
),
[_NUM] = LAYOUT_ergodox(
       // left hand
        KC_NO,   KC_NO,    KC_NO,    KC_NO,  KC_NO,   KC_NO,    KC_NO, 
        KC_NO,   KC_1,   KC_P2,   KC_P3,   KC_P4,   KC_P5,   KC_NO, 
        KC_NO,   OS_CMD,  OS_ALT,  OS_CTRL, OS_SHFT, KC_F11,
        KC_NO,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_NO, 
        KC_NO,   KC_NO,    KC_NO,    KC_NO,  KC_NO,
                                                      KC_NO,    KC_NO,  
                                                                KC_NO, 
                                             KC_TRNS,  KC_TRNS,  KC_TRNS,

        // right hand
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,     KC_NO,
        KC_NO,   KC_P6,   KC_P7,   KC_P8,   KC_P9,   KC_P0,    KC_NO,
                 KC_F12,  OS_SHFT, OS_CTRL, OS_ALT,  OS_CMD,   KC_NO,
        KC_NO,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_NO,
                          KC_NO,  KC_NO,    KC_NO,   KC_NO,     KC_NO,
        KC_NO,   KC_NO,
        KC_NO,
        KC_TRNS,   KC_TRNS,  KC_TRNS
),
[_ALT] = LAYOUT_ergodox(
       // left hand
        KC_NO,   KC_NO,    KC_NO,    KC_NO,  KC_NO,   KC_NO,    KC_NO, 
        KC_NO,   KC_NO,    KC_NO,    KC_NO,  KC_NO,   YO,       KC_NO, 
        KC_NO,   LABK,     LSBK,     LCBK,   LBRK,    KC_NO,
        KC_NO,   KC_NO,    KC_NO,    KC_NO,  KC_NO,   KC_NO,    KC_NO, 
        KC_NO,   KC_NO,    KC_NO,    KC_NO,  KC_NO,
                                                      KC_NO,    KC_NO,  
                                                                KC_NO, 
                                             KC_NO,  KC_NO,  KC_NO,

        // right hand
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,     KC_NO,
        KC_NO,   KC_NO,   KC_NO,   SCHA,    KC_NO,   KC_NO,    KC_NO,
                 KC_NO,   RBRK,    RCBK,    RSBK,    RABK,     KC_NO,
        KC_NO,   KC_NO,   HS,      KC_NO,   KC_NO,   KC_NO,    KC_NO,
                          KC_NO,  KC_NO,    KC_NO,   KC_NO,    KC_NO,
        KC_NO,   KC_NO,
        KC_NO,
        KC_NO,   KC_NO,  KC_NO
  ),


[BASE] = LAYOUT_ergodox(  // Old layout
        // left hand
        KC_EQL,         KC_1,         KC_2,   KC_3,   KC_4,   KC_5,   SWITCH_RUSSIAN,
        KC_NO,        KC_Q,         KC_W,   KC_E,   KC_R,   KC_T,   KC_TILD,
        MO(NAVI),        KC_A,         KC_S,   KC_D,   KC_F,   KC_G,
        KC_LSFT,        CTL_T(KC_Z),  KC_X,   KC_C,   KC_V,   KC_B,   KC_HYPR,
        KC_LGUI,KC_LALT,      KC_NO,  KC_MEH, KC_ESC,
                                              DF(_DEF),  KC_LGUI,
                                                              KC_HOME,
                                               KC_SPC, KC_NO, MO(SYMB),
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
       KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_RSFT,
                        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
[SYMB] = LAYOUT_ergodox(
       // left hand
       KC_NO,   KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO, KC_NO,
       KC_NO,   KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO, KC_NO,
       KC_TRNS, KC_LABK,KC_LBRC,KC_LCBR,KC_LPRN,KC_GRV,
       KC_TRNS, KC_TRNS,KC_TRNS,KC_QUES,KC_TILD,KC_TRNS,KC_TRNS,
          KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                       RGB_MOD,KC_TRNS,
                                               KC_TRNS,
                               RGB_VAD,RGB_VAI,KC_TRNS,
       // right hand
       KC_NO,  KC_NO,   KC_NO,  KC_NO,   KC_NO,   KC_NO,  KC_NO,
       KC_NO,  KC_NO,   KC_NO,  KC_NO,    A(KC_BSPC),    KC_NO, KC_NO,
                TD(QUOTES_DBLQUOTES),KC_RPRN,KC_RCBR,KC_RBRC,KC_RABK,KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS,
                         KC_TRNS,KC_TRNS,  KC_TRNS,    KC_TRNS,  KC_TRNS,
       RGB_TOG, RGB_SLD,
       KC_TRNS,
       KC_TRNS, RGB_HUD, RGB_HUI
),
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
)
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
    case SWITCH_RUSSIAN: {
      if (!record->event.pressed) {
        layer_on(RUSSIAN);
        register_mods(HYPER);
        register_code(KC_EQL);
        unregister_code(KC_EQL);
        unregister_mods(HYPER);
      }
      break;
    }
    case SWITCH_ENGLISH: {
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

void updata_rgb(uint16_t keycode, keyrecord_t *record) {
    if (keycode == RGB_SLD) {
      if (record->event.pressed) {
      #ifdef RGBLIGHT_ENABLE
        rgblight_mode(1);
      #endif
      }
    }
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

    #ifdef RGBLIGHT_ENABLE
    updata_rgb(keycode, record);
    #endif

    update_lang(keycode, record);

    return true;
}




void setup_lights(uint32_t state) {
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
      case 8:
        ergodox_right_led_1_on();
        #ifdef RGBLIGHT_COLOR_LAYER_1
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_1);
        #endif
        break;
      case 9:
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_2
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_2);
        #endif
        break;
      case 10:
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_3
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_3);
        #endif
        break;
      case 11:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_4
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_4);
        #endif
        break;
      default:
        break;
    }

}

layer_state_t layer_state_set_user(layer_state_t state) {
    setup_lights(state);
    return update_tri_layer_state(state, _SYM, _NAV, _NUM);
}


void matrix_init_user(void) {
#ifdef RGBLIGHT_COLOR_LAYER_0
  rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
};

tap_dance_action_t tap_dance_actions[] = {
  [QUOTES_DBLQUOTES]  = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, KC_DQUO)
};
