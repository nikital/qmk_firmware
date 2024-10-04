// Copyright 2022 Nikita Leshenko (@nikital)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _RL,
    _LL,
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    QMKBEST = SAFE_RANGE,
    QMKURL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
KC_ESC,  KC_F1, KC_F2, KC_F3, KC_F4,  KC_F5,           KC_F6, KC_F7, KC_F8,  KC_F9, KC_F10, KC_F11, KC_F12,   KC_PSCR, KC_SCRL, KC_PAUS,

 KC_GRV,  KC_1, KC_2, KC_3, KC_4, KC_5,                KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC,      KC_INS, KC_PGUP,
KC_TAB,   KC_Q, KC_W, KC_E, KC_R, KC_T,                KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,     KC_DEL, KC_PGDN,
KC_CAPS,  KC_A, KC_S, KC_D, KC_F, KC_G,                KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,  KC_ENT ,          KC_HOME, KC_END,
KC_LSFT,  KC_Z, KC_X, KC_C, KC_V, KC_B,                KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,               KC_UP,
MO(_LL), KC_LGUI, KC_LALT,      KC_LCTL,  KC_SPC,        MO(_RL), KC_BSPC,   KC_RALT, KC_DEL, KC_RCTL, KC_APP,  KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_RL] = LAYOUT(
KC_TRNS,  KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO,        KC_NO, KC_NO, KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS,

 KC_NO,  LGUI(KC_1), LGUI(KC_2), LGUI(KC_3), LGUI(KC_4), LGUI(KC_5),          KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,         KC_NO, KC_NO,
KC_TRNS,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,        KC_NO, LCTL(KC_PGUP), LCTL(KC_PGDN), KC_NO, KC_NO, KC_PGUP, KC_PGDN, KC_TRNS,     KC_NO, KC_NO,
KC_TRNS,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,        KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_NO, KC_NO,   KC_TRNS,       KC_NO, KC_NO,
KC_TRNS,   KC_NO, KC_NO, LCTL(KC_INS), LSFT(KC_INS), KC_NO,        KC_ESC, KC_ENT, KC_HOME, KC_END, KC_NO,   KC_TRNS,                KC_NO,
KC_NO, KC_TRNS, KC_TRNS,        KC_TRNS, KC_NO,   KC_TRNS, KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_NO, KC_NO, KC_NO
    ),
    [_LL] = LAYOUT(
KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO,        KC_NO, KC_NO, KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO, KC_NUMLOCK, KC_NO,

 KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                 KC_NO, KC_KP_7, KC_KP_8, KC_KP_9, KC_NO, KC_KP_MINUS, KC_NO, KC_NO,    KC_NO, KC_NO,
KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                 KC_NO, KC_KP_4, KC_KP_5, KC_KP_6, KC_NO, KC_NO, KC_NO, KC_NO,    KC_NO, KC_NO,
KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                 KC_NO, KC_KP_1, KC_KP_2, KC_KP_3, KC_NO, KC_NO,   KC_NO,         KC_NO, KC_NO,
KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                 KC_NO, KC_KP_0, KC_NO, KC_KP_DOT, KC_NO,   KC_NO,                KC_NO,
KC_TRNS, KC_NO, KC_NO,      KC_NO, KC_NO,                 KC_NO, KC_TRNS,   KC_NO, KC_NO, KC_NO, KC_NO,         KC_NO, KC_NO, KC_NO
    ),
};
