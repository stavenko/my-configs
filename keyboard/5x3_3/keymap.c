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
#define GRV KC_GRV        // `
#define TILD S(KC_GRV)       // ~
// #define BSL RALT(KC_BSLS)
#define COMMA KC_LBRC // ,
#define DOT KC_RBRC // .
#define SCLN S(KC_LBRC) // ;
#define CLN S(KC_RBRC) // :
#define QUOT KC_QUOT // '
#define DQUOT S(KC_QUOT) // '
#define SLSH KC_BSLS // /
#define BSLS S(KC_BSLS) // 
#define HS LALT(KC_M)  
#define YO LALT(KC_T) 
#define SCHA LALT(KC_I)  

// Brackets
#define LBRK RALT(KC_F) // left bracket (
#define LSBK RALT(KC_D) // left square bracket [
#define LCBK RALT(KC_S) // left curly bracket {
#define LABK RALT(KC_A) // left angle bracket <
                        //
#define RBRK RALT(KC_J) // left bracket (
#define RSBK RALT(KC_K) // left square bracket [
#define RCBK RALT(KC_L) // left curly bracket {
#define RABK RALT(KC_SCLN // left angle bracket <

#define SPACE_L C(KC_LEFT)
#define SPACE_R C(KC_RGHT)

#define TAB_L C(S(KC_TAB))
#define TAB_R C(KC_TAB)

enum layers {
    _DEF,
    _GAM,
    _GFN,
    _SYM,
    _NAV,
    _NUM,
    _ALT,
};

enum keycodes {
    // Custom oneshot mod implementation with no timers.
    OS_SHFT = SAFE_RANGE,
    OS_CTRL,
    OS_ALT,
    OS_CMD,

    SW_WIN,  // Switch to next window         (alt-tab)
    SW_TAB,  // Switch to next browser tab    (ctrl-tab)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEF] = LAYOUT_split_3x5_3(
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,           KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,           KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,           KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
                          LA_NAV, KC_SPC,  KC_ESC,         LA_SYM , KC_LSFT, LA_ALT
    ),

    [_GAM] = LAYOUT_split_3x5_3(
        KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,           KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_LSFT,  KC_A,   KC_S,    KC_D,    KC_F,           KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
        KC_LCTL,  KC_Z,   KC_X,    KC_C,    KC_V,           KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
                          KC_LALT, KC_SPC,  LA_GFN,         DF(_DEF), KC_LSFT, KC_PSCR
    ),

    [_GFN] = LAYOUT_split_3x5_3(
        KC_5,    KC_1,    KC_2,    KC_3,    KC_4,           KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_0,    KC_6,    KC_7,    KC_8,    KC_9,           KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
        KC_G,    KC_J,    KC_I,    KC_M,    KC_T,           KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
                          KC_ESC,  KC_ENT, _______,        _______, _______, _______
    ),

    [_SYM] = LAYOUT_split_3x5_3(
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        SCLN,    GRV,     QUOT,    DQUOT,   KC_MINS,        KC_PLUS, OS_SHFT, OS_CTRL, OS_ALT,  OS_CMD,
        BSLS,    KC_NO,   SCLN,    COMMA ,  KC_UNDS,        KC_EQL,  DOT,     CLN,     KC_NO,   SLSH,
                          _______, _______, _______,        _______, _______, _______
    ),

    [_NAV] = LAYOUT_split_3x5_3(
        SW_TAB,  SW_WIN,  TAB_L,    TAB_R,   KC_ESC,        KC_ESC,  KC_HOME, KC_END,  KC_BSPC, KC_DEL,
        OS_CMD,  OS_ALT,  OS_CTRL,  OS_SHFT, KC_ENT,        KC_ENT,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
        SPACE_L, SPACE_R, DF(_GAM), KC_PSCR, KC_TAB,        KC_TAB,  KC_PGUP, KC_PGDN, XXXXXXX, XXXXXXX,
                          _______, _______, _______,        _______, _______, _______
    ),

    [_NUM] = LAYOUT_split_3x5_3(
        KC_P1,   KC_P2,   KC_P3,   KC_P4,   KC_P5,          KC_P6,   KC_P7,   KC_P8,   KC_P9,   KC_P0,
        OS_CMD,  OS_ALT,  OS_CTRL, OS_SHFT, KC_F11,         KC_F12,  OS_SHFT, OS_CTRL, OS_ALT,  OS_CMD,
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,          KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
                          _______, _______, _______,        _______, _______, _______
    ),

    [_ALT] = LAYOUT_split_3x5_3(
        KC_NO,   KC_NO,   KC_NO,   KC_NO,      YO,          KC_NO,   KC_NO,   SCHA,   KC_NO,   KC_NO,
        LABK,    LSBK,    LCBK,    LBRK,    KC_NO,          KC_NO,   RBRK,    RCBK,   RSBK,    RABK,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,          KC_NO,   HS,      KC_NO,  KC_NO,   KC_NO,
                          _______, _______, _______,        _______, _______, _______
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

    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _SYM, _NAV, _NUM);
}
