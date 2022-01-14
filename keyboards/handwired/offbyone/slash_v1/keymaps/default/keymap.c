// Copyright 2022 Nikita Leshenko (@nikital)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    QMKBEST = SAFE_RANGE,
    QMKURL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
KC_ESC,  KC_F1, KC_F2, KC_F3, KC_F4,  KC_F5,           KC_1, KC_1, KC_1,  KC_1, KC_1, KC_1, KC_1,   KC_1, KC_1, KC_1,

 KC_GRV,  KC_1, KC_2, KC_3, KC_4, KC_5,                KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1,    KC_1, KC_1,
KC_TAB,   KC_Q, KC_W, KC_E, KC_R, KC_T,                KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1,    KC_1, KC_1,
KC_CAPS,  KC_A, KC_S, KC_D, KC_F, KC_G,                KC_1, KC_1, KC_1, KC_1, KC_1, KC_1,    KC_1,       KC_1, KC_1,
KC_LSFT,  KC_Z, KC_X, KC_C, KC_V, KC_B,                KC_1, KC_1, KC_1, KC_1, KC_1,     KC_1,            KC_1,
KC_LCTL, KC_LGUI, KC_LALT,      KC_SPC, KC_SPC,        KC_1, KC_1,    KC_1, KC_1, KC_1, KC_1,       KC_1, KC_1, KC_1
    ),
};
