/* Copyright 2023 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * KC_NO / XXXXXXX nothing
 * _______ / _______ transparent
 * */

#include QMK_KEYBOARD_H

#include "sendstring_german.h"

#define DE_LBRC_OSX A(DE_5) // [
#define DE_RBRC_OSX A(DE_6) // ]
#define DE_LCBR_OSX A(DE_8) // {
#define DE_RCBR_OSX A(DE_9) // }
#define DE_BSLS_OSX S(A(DE_7)) // (backslash)
#define DE_PIPE_OSX A(DE_7) // |
#define DE_STIL_OSX S(A(DE_8)) // ~
#define DE_AT_OSX A(DE_L) // @

// clang-format off
enum layers{
  MAC_BASE,
  MAC_FN,
  WIN_BASE,
  WIN_FN,
  MAC_DEV,
  WIN_DEV,
};

enum custom_keycodes {
    BACKTICK = SAFE_RANGE,
    CIRC,
    TILD_OSX,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case BACKTICK:
        if (record->event.pressed) {
            SEND_STRING("`");
        }
        return false;
    case CIRC:
        if (record->event.pressed) {
            SEND_STRING("^");
        }
        return false;
    case TILD_OSX:
        if (record->event.pressed) {
            SEND_STRING(SS_LOPT("n") SS_TAP(X_SPC));
        }
        return false;

    default:
        return true;

    return true;
    }
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[MAC_BASE] = LAYOUT_iso_85(
     KC_ESC,       KC_BRID,  KC_BRIU,  KC_MCTL,  KC_LPAD,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_SNAP,  KC_DEL,   RGB_MOD,
     KC_GRV,       KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_PGUP,
     KC_TAB,       KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_ENT,             KC_PGDN,
     MO(MAC_DEV),  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            MO(MAC_DEV),        KC_HOME,
     KC_LSFT,      KC_NUBS,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,  KC_UP,    KC_END,
     KC_LCTL,      KC_LOPTN, KC_LCMMD,                               KC_SPC,                                 KC_RCMMD, MO(MAC_FN),KC_RCTL, KC_LEFT,  KC_DOWN,  KC_RGHT),

[MAC_FN] = LAYOUT_iso_85(
     _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,  _______,  RGB_TOG,
     _______,  BT_HST1,  BT_HST2,  BT_HST3,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
     BAT_LVL,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
     _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  _______,  _______,  _______,  _______,  _______,  _______,            _______,            _______,
     _______,  _______,  _______,  _______,  _______,  _______,  BAT_LVL,  NK_TOGG,  _______,  _______,  _______,  _______,            _______,  _______,  _______,
     _______,  _______,  _______,                                _______,                                _______,  _______,  _______,  _______,  _______,  _______),

[MAC_DEV] = LAYOUT_iso_85(
     _______,  _______,     _______,  _______,      _______,      _______,     _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
     _______,  _______,     _______,  _______,      _______,      _______,     _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
     _______,  _______,     DE_UNDS,  DE_LBRC_OSX,  DE_RBRC_OSX,  CIRC,        DE_EXLM,  DE_LABK,  DE_RABK,  DE_EQL,   DE_AMPR,  _______,  _______,  _______,            _______,
     _______,  DE_BSLS_OSX, DE_SLSH,  DE_LCBR_OSX,  DE_RCBR_OSX,  DE_ASTR,     DE_QUES,  DE_LPRN,  DE_RPRN,  DE_SCLN,  DE_COLN,  DE_AT_OSX,              _______,            _______,
     _______,  _______,     DE_HASH,  DE_DLR,       DE_PIPE_OSX,  TILD_OSX, BACKTICK, DE_PLUS,  DE_PERC,  DE_DQUO,  DE_QUOT,  _______,            _______,  _______,  _______,
     _______,  _______,     _______,                              KC_ESC,                                 _______,  _______,  _______,  _______,  _______,  _______),

[WIN_BASE] = LAYOUT_iso_85(
     KC_ESC,   KC_BRID,  KC_BRIU,  KC_TASK,  KC_FILE,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_PSCR,  KC_DEL,   RGB_MOD,
     KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_PGUP,
     KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_ENT,             KC_PGDN,
     MO(WIN_DEV),KC_A,   KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            MO(WIN_DEV),        KC_HOME,
     KC_LSFT,  KC_NUBS,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,  KC_UP,    KC_END,
     KC_LCTL,  KC_LGUI,  KC_LALT,                                KC_SPC,                                 KC_RALT, MO(WIN_FN),KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

[WIN_FN] = LAYOUT_iso_85(
     _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,  _______,  RGB_TOG,
     _______,  BT_HST1,  BT_HST2,  BT_HST3,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
     RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
     _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  _______,  _______,  _______,  _______,  _______,  _______,            _______,            _______,
     _______,  _______,  _______,  _______,  _______,  _______,  BAT_LVL,  NK_TOGG,  _______,  _______,  _______,  _______,            _______,  _______,  _______,
     _______,  _______,  _______,                                _______,                                _______,  _______,  _______,  _______,  _______,  _______),

[WIN_DEV] = LAYOUT_iso_85(
     _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
     _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
     _______,  _______,  DE_UNDS,  DE_LBRC,  DE_RBRC,  CIRC,     DE_EXLM,  DE_LABK,  DE_RABK,  DE_EQL,   DE_AMPR,  _______,  _______,  _______,            _______,
     _______,  DE_BSLS,  DE_SLSH,  DE_LCBR,  DE_RCBR,  DE_ASTR,  DE_QUES,  DE_LPRN,  DE_RPRN,  DE_SCLN,  DE_COLN,  DE_AT,              _______,            _______,
     _______,  _______,  DE_HASH,  DE_DLR,   DE_PIPE,  DE_TILD,  BACKTICK, DE_PLUS,  DE_PERC,  DE_DQUO,  DE_QUOT,  _______,            _______,  _______,  _______,
     _______,  _______,  _______,                                KC_ESC,                                 _______,  _______,  _______,  _______,  _______,  _______),
};