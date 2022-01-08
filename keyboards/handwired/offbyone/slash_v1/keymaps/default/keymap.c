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
    KC_1, KC_1, KC_1,  KC_1, KC_1, KC_1, KC_1,   KC_1, KC_1, KC_1,

    KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1,    KC_1, KC_1,
    KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1, KC_1,    KC_1, KC_1,
    KC_1, KC_1, KC_1, KC_1, KC_1, KC_1,   KC_1,        KC_1, KC_1,
    KC_1, KC_1, KC_1, KC_1, KC_1,   KC_1,              KC_1,
    KC_1, KC_1,   KC_1, KC_1, KC_1, KC_1,        KC_1, KC_1, KC_1
    ),
};
