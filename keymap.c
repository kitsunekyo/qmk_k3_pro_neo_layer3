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
// @see https://docs.qmk.fm/newbs

#include QMK_KEYBOARD_H

/**
 * use DE keycode aliases
 * {@see keymap} https://github.com/qmk/qmk_firmware/blob/master/quantum/keymap_extras/keymap_german.h
 * https://github.com/qmk/qmk_firmware/blob/master/quantum/keymap_extras/sendstring_german.h
 */
#include "sendstring_german.h"

enum layers {
    MAC_BASE,
    MAC_FN,
    WIN_BASE,
    WIN_FN,
    /**
     * dont move layers above, as the keychron OS switch relies on the index
     */
    MAC_L3,
    WIN_L3,
    UTIL_L4,
    GAMING,
};

/**
 * DE MAC SYMBOLS
 * map keymap_german.h to keymap_german_osx.h
 * so that we have the same keys when switching from osx to win
 *                                    WIN                         MAC
 * [              DE_LBRC             ALGR(DE_8)                  A(DE_5)
 * ]              DE_RBRC             ALGR(DE_9)                  A(DE_6)
 * {              DE_LCBR             ALGR(DE_7)                  A(DE_8)
 * }              DE_RCBR             ALGR(DE_0)                  A(DE_9)
 * (backslash)    DE_BSLS             ALGR(DE_SS))                S(A(DE_7))
 * ~ (deadkey)    DE_TILD             ALGR(DE_PLUS)               A(DE_N)
 * |              DE_PIPE             ALGR(DE_LABK)               A(DE_7)
 * @              DE_AT               ALGR(DE_Q)                  A(DE_L)
 * €              DE_EURO             ALGR(DE_E)                  A(DE_E)
 */
#define MAC_LBRC    A(DE_5)      // [
#define MAC_RBRC    A(DE_6)      // ]
#define MAC_LCBR    A(DE_8)      // {
#define MAC_RCBR    A(DE_9)      // }
#define MAC_BSL     S(A(DE_7))   // (backslash)
#define MAC_PIPE    A(DE_7)      // |
#define MAC_AT      A(DE_L)      // @

// HOME ROW MODS
#define HOME_A LGUI_T(KC_A)
#define HOME_S LALT_T(KC_S)
#define HOME_D LSFT_T(KC_D)
#define HOME_F LCTL_T(KC_F)
#define HOME_J RCTL_T(KC_J)
#define HOME_K RSFT_T(KC_K)
#define HOME_L LALT_T(KC_L)
#define HOME_SCLN RGUI_T(KC_SCLN)

enum custom_keycodes {
    BACKTICK = SAFE_RANGE,           // `
    CIRC,                            // ^
    MAC_TILDE,                       // ~
};

// immediately send deadkey characters
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
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
        case MAC_TILDE:
            if (record->event.pressed) {
                SEND_STRING(SS_LOPT("n") SS_TAP(X_SPC));
            }
            return false;
        default:
            return true;
    }
};

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        case KC_SLSH:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;
        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
            return true;
        default:
            return false;  // Deactivate Caps Word.
    }
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    for (uint8_t i = led_min; i < led_max; i++) {
        switch(get_highest_layer(layer_state|default_layer_state)) {
            case WIN_BASE:
                rgb_matrix_set_color(i, RGB_BLUE);
                break;
            case MAC_BASE:
                rgb_matrix_set_color(i, RGB_SPRINGGREEN);
                break;
            case GAMING:
                rgb_matrix_set_color(i, RGB_RED);
                break;
            case UTIL_L4:
                rgb_matrix_set_color(i, RGB_PINK);
                break;
            default:
                rgb_matrix_set_color(i, RGB_ORANGE);
                break;
        }
    }
    return false;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//    ┌────────────┬────────┬──────┬──────┬────────┬─────────┬─────────┬────────┬──────┬──────┬───────────┬────────────┬───────────────┬──────┬──────┬─────────┐
//    │    esc     │  bRID  │ bRIU │ mCTL │  lPAD  │ RGB_VAD │ RGB_VAI │  mprv  │ mply │ mnxt │   mute    │    vold    │     volu      │ sNAP │ del  │ RGB_MOD │
//    ├────────────┼────────┼──────┼──────┼────────┼─────────┼─────────┼────────┼──────┼──────┼───────────┼────────────┼───────────────┼──────┴──────┼─────────┤
//    │     `      │   1    │  2   │  3   │   4    │    5    │    6    │   7    │  8   │  9   │     0     │     -      │       =       │    bspc     │  pgup   │
//    ├────────────┼────────┼──────┼──────┼────────┼─────────┼─────────┼────────┼──────┼──────┼───────────┼────────────┼───────────────┼─────────────┼─────────┤
//    │    tab     │   q    │  w   │  e   │   r    │    t    │    y    │   u    │  i   │  o   │     p     │     [      │       ]       │     ent     │  pgdn   │
//    ├────────────┼────────┼──────┼──────┼────────┼─────────┼─────────┼────────┼──────┼──────┼───────────┼────────────┼───────────────┼─────────────┼─────────┤
//    │ MO(MAC_L3) │ HOME_A │  s   │  d   │ HOME_F │    g    │    h    │ HOME_J │  k   │  l   │ HOME_SCLN │     '      │ LT(MAC_L3, \) │             │  home   │
//    ├────────────┼────────┼──────┼──────┼────────┼─────────┼─────────┼────────┼──────┼──────┼───────────┼────────────┼───────────────┴──────┬──────┼─────────┤
//    │    lsft    │  iso\  │  z   │  x   │   c    │    v    │    b    │   n    │  m   │  ,   │     .     │     /      │         rsft         │  up  │   end   │
//    ├────────────┼────────┼──────┼──────┼────────┴─────────┴─────────┴────────┴──────┼──────┼───────────┼────────────┼───────────────┬──────┼──────┼─────────┤
//    │    lctl    │  lalt  │ lgui │      │              LT(UTIL_L4, spc)              │      │   rgui    │ MO(MAC_FN) │     rctl      │ left │ down │  rght   │
//    └────────────┴────────┴──────┘      └────────────────────────────────────────────┘      └───────────┴────────────┴───────────────┴──────┴──────┴─────────┘
[MAC_BASE] = LAYOUT_iso_85(
  KC_ESC     , KC_BRID , KC_BRIU , KC_MCTL , KC_LPAD , RGB_VAD , RGB_VAI , KC_MPRV , KC_MPLY , KC_MNXT , KC_MUTE   , KC_VOLD    , KC_VOLU             , KC_SNAP , KC_DEL  , RGB_MOD,
  KC_GRV     , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    , KC_6    , KC_7    , KC_8    , KC_9    , KC_0      , KC_MINS    , KC_EQL              ,           KC_BSPC , KC_PGUP,
  KC_TAB     , KC_Q    , KC_W    , KC_E    , KC_R    , KC_T    , KC_Y    , KC_U    , KC_I    , KC_O    , KC_P      , KC_LBRC    , KC_RBRC             ,            KC_ENT , KC_PGDN,
  MO(MAC_L3) , HOME_A  , KC_S    , KC_D    , HOME_F  , KC_G    , KC_H    , HOME_J  , KC_K    , KC_L    , HOME_SCLN , KC_QUOT    , LT(MAC_L3, KC_BSLS) ,                     KC_HOME,
  KC_LSFT    , KC_NUBS , KC_Z    , KC_X    , KC_C    , KC_V    , KC_B    , KC_N    , KC_M    , KC_COMM , KC_DOT    , KC_SLSH    ,                       KC_RSFT , KC_UP   , KC_END ,
  KC_LCTL    , KC_LALT , KC_LGUI ,                         LT(UTIL_L4, KC_SPC)               ,           KC_RGUI   , MO(MAC_FN) , KC_RCTL             , KC_LEFT , KC_DOWN , KC_RGHT
),

//    ┌─────────┬──────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────────┐
//    │         │    f1    │   f2    │   f3    │   f4    │   f5    │   f6    │   f7    │ f8  │ f9  │ f10 │ f11 │ f12 │     │     │ RGB_TOG │
//    ├─────────┼──────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────────┤
//    │         │ BT_HST1  │ BT_HST2 │ BT_HST3 │         │         │         │         │     │     │     │     │     │           │         │
//    ├─────────┼──────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────┼─────┼─────┼─────┼─────┼───────────┼─────────┤
//    │ BAT_LVL │ RGB_MOD  │ RGB_VAI │ RGB_HUI │ RGB_SAI │ RGB_SPI │         │         │     │     │     │     │     │           │         │
//    ├─────────┼──────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────┼─────┼─────┼─────┼─────┼───────────┼─────────┤
//    │         │ RGB_RMOD │ RGB_VAD │ RGB_HUD │ RGB_SAD │ RGB_SPD │         │         │     │     │     │     │     │           │         │
//    ├─────────┼──────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────┼─────┼─────┼─────┼─────┴─────┬─────┼─────────┤
//    │         │          │         │         │         │         │ BAT_LVL │ NK_TOGG │     │     │     │     │           │     │         │
//    ├─────────┼──────────┼─────────┼─────────┼─────────┴─────────┴─────────┴─────────┴─────┼─────┼─────┼─────┼─────┬─────┼─────┼─────────┤
//    │         │          │         │         │                                             │     │     │     │     │     │     │         │
//    └─────────┴──────────┴─────────┘         └─────────────────────────────────────────────┘     └─────┴─────┴─────┴─────┴─────┴─────────┘
[MAC_FN] = LAYOUT_iso_85(
  _______ , KC_F1    , KC_F2   , KC_F3   , KC_F4   , KC_F5   , KC_F6   , KC_F7   , KC_F8   , KC_F9   , KC_F10  , KC_F11  , KC_F12  , _______ , _______ , RGB_TOG,
  _______ , BT_HST1  , BT_HST2 , BT_HST3 , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,           _______ , _______,
  BAT_LVL , RGB_MOD  , RGB_VAI , RGB_HUI , RGB_SAI , RGB_SPI , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,           _______ , _______,
  _______ , RGB_RMOD , RGB_VAD , RGB_HUD , RGB_SAD , RGB_SPD , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,                     _______,
  _______ , _______  , _______ , _______ , _______ , _______ , BAT_LVL , NK_TOGG , _______ , _______ , _______ , _______ ,           _______ , _______ , _______,
  _______ , _______  , _______ ,                               _______                     ,           _______ , _______ , _______ , _______ , _______ , _______
),

//    ┌─────┬─────────┬─────────┬──────────┬──────────┬───────────┬──────────┬─────────┬─────────┬─────────┬─────────┬────────┬─────┬─────┬─────┬─────┐
//    │     │         │         │          │          │           │          │         │         │         │         │        │     │     │     │     │
//    ├─────┼─────────┼─────────┼──────────┼──────────┼───────────┼──────────┼─────────┼─────────┼─────────┼─────────┼────────┼─────┼─────┴─────┼─────┤
//    │     │         │         │          │          │           │          │         │         │         │         │        │     │           │     │
//    ├─────┼─────────┼─────────┼──────────┼──────────┼───────────┼──────────┼─────────┼─────────┼─────────┼─────────┼────────┼─────┼───────────┼─────┤
//    │     │         │ DE_UNDS │ MAC_LBRC │ MAC_RBRC │   CIRC    │ DE_EXLM  │ DE_LABK │ DE_RABK │ DE_EQL  │ DE_AMPR │        │     │           │     │
//    ├─────┼─────────┼─────────┼──────────┼──────────┼───────────┼──────────┼─────────┼─────────┼─────────┼─────────┼────────┼─────┼───────────┼─────┤
//    │     │ MAC_BSL │ DE_SLSH │ MAC_LCBR │ MAC_RCBR │  DE_ASTR  │ DE_QUES  │ DE_LPRN │ DE_RPRN │ DE_SCLN │ DE_COLN │ MAC_AT │     │           │     │
//    ├─────┼─────────┼─────────┼──────────┼──────────┼───────────┼──────────┼─────────┼─────────┼─────────┼─────────┼────────┼─────┴─────┬─────┼─────┤
//    │     │         │ DE_HASH │  DE_DLR  │ MAC_PIPE │ MAC_TILDE │ BACKTICK │ DE_PLUS │ DE_PERC │ DE_DQUO │ DE_QUOT │        │           │     │     │
//    ├─────┼─────────┼─────────┼──────────┼──────────┴───────────┴──────────┴─────────┴─────────┼─────────┼─────────┼────────┼─────┬─────┼─────┼─────┤
//    │     │         │         │          │                                                     │         │         │        │     │     │     │     │
//    └─────┴─────────┴─────────┘          └─────────────────────────────────────────────────────┘         └─────────┴────────┴─────┴─────┴─────┴─────┘
[MAC_L3] = LAYOUT_iso_85(
  _______ , _______ , _______ , _______  , _______  , _______   , _______  , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______,
  _______ , _______ , _______ , _______  , _______  , _______   , _______  , _______ , _______ , _______ , _______ , _______ , _______ ,           _______ , _______,
  _______ , _______ , DE_UNDS , MAC_LBRC , MAC_RBRC , CIRC      , DE_EXLM  , DE_LABK , DE_RABK , DE_EQL  , DE_AMPR , _______ , _______ ,           _______ , _______,
  _______ , MAC_BSL , DE_SLSH , MAC_LCBR , MAC_RCBR , DE_ASTR   , DE_QUES  , DE_LPRN , DE_RPRN , DE_SCLN , DE_COLN , MAC_AT  , _______ ,                     _______,
  _______ , _______ , DE_HASH , DE_DLR   , MAC_PIPE , MAC_TILDE , BACKTICK , DE_PLUS , DE_PERC , DE_DQUO , DE_QUOT , _______ ,           _______ , _______ , _______,
  _______ , _______ , _______ ,                                  _______                       ,           _______ , _______ , _______ , _______ , _______ , _______
),

//    ┌────────────┬────────┬──────┬────┬────────┬────┬────┬────────┬────┬────┬───────────┬────────────┬───────────────┬────────────┬──────┬─────────┐
//    │    esc     │   f1   │  f2  │ f3 │   f4   │ f5 │ f6 │   f7   │ f8 │ f9 │    f10    │    f11     │      f12      │ TG(GAMING) │ del  │ RGB_MOD │
//    ├────────────┼────────┼──────┼────┼────────┼────┼────┼────────┼────┼────┼───────────┼────────────┼───────────────┼────────────┴──────┼─────────┤
//    │     `      │   1    │  2   │ 3  │   4    │ 5  │ 6  │   7    │ 8  │ 9  │     0     │     -      │       =       │       bspc        │  pgup   │
//    ├────────────┼────────┼──────┼────┼────────┼────┼────┼────────┼────┼────┼───────────┼────────────┼───────────────┼───────────────────┼─────────┤
//    │    tab     │   q    │  w   │ e  │   r    │ t  │ y  │   u    │ i  │ o  │     p     │     [      │       ]       │        ent        │  pgdn   │
//    ├────────────┼────────┼──────┼────┼────────┼────┼────┼────────┼────┼────┼───────────┼────────────┼───────────────┼───────────────────┼─────────┤
//    │ MO(WIN_L3) │ HOME_A │  s   │ d  │ HOME_F │ g  │ h  │ HOME_J │ k  │ l  │ HOME_SCLN │     '      │ LT(WIN_L3, \) │                   │  home   │
//    ├────────────┼────────┼──────┼────┼────────┼────┼────┼────────┼────┼────┼───────────┼────────────┼───────────────┴────────────┬──────┼─────────┤
//    │    lsft    │  iso\  │  z   │ x  │   c    │ v  │ b  │   n    │ m  │ ,  │     .     │     /      │            rsft            │  up  │   end   │
//    ├────────────┼────────┼──────┼────┼────────┴────┴────┴────────┴────┼────┼───────────┼────────────┼───────────────┬────────────┼──────┼─────────┤
//    │    lctl    │  lgui  │ lalt │    │        LT(UTIL_L4, spc)        │    │   ralt    │ MO(WIN_FN) │     rctl      │    left    │ down │  rght   │
//    └────────────┴────────┴──────┘    └────────────────────────────────┘    └───────────┴────────────┴───────────────┴────────────┴──────┴─────────┘
[WIN_BASE] = LAYOUT_iso_85(
  KC_ESC     , KC_F1   , KC_F2   , KC_F3 , KC_F4  , KC_F5 , KC_F6 , KC_F7  , KC_F8 , KC_F9   , KC_F10    , KC_F11     , KC_F12              , TG(GAMING) , KC_DEL  , RGB_MOD,
  KC_GRV     , KC_1    , KC_2    , KC_3  , KC_4   , KC_5  , KC_6  , KC_7   , KC_8  , KC_9    , KC_0      , KC_MINS    , KC_EQL              ,              KC_BSPC , KC_PGUP,
  KC_TAB     , KC_Q    , KC_W    , KC_E  , KC_R   , KC_T  , KC_Y  , KC_U   , KC_I  , KC_O    , KC_P      , KC_LBRC    , KC_RBRC             ,               KC_ENT , KC_PGDN,
  MO(WIN_L3) , HOME_A  , KC_S    , KC_D  , HOME_F , KC_G  , KC_H  , HOME_J , KC_K  , KC_L    , HOME_SCLN , KC_QUOT    , LT(WIN_L3, KC_BSLS) ,                        KC_HOME,
  KC_LSFT    , KC_NUBS , KC_Z    , KC_X  , KC_C   , KC_V  , KC_B  , KC_N   , KC_M  , KC_COMM , KC_DOT    , KC_SLSH    ,                          KC_RSFT , KC_UP   , KC_END ,
  KC_LCTL    , KC_LGUI , KC_LALT ,                   LT(UTIL_L4, KC_SPC)           ,           KC_RALT   , MO(WIN_FN) , KC_RCTL             , KC_LEFT    , KC_DOWN , KC_RGHT
),

//    ┌─────────┬──────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬──────┬──────┬──────┬──────┬──────┬─────┬─────┬─────────┐
//    │         │   bRID   │  bRIU   │  tASK   │  fILE   │ RGB_VAD │ RGB_VAI │  mprv   │ mply │ mnxt │ mute │ vold │ volu │     │     │ RGB_TOG │
//    ├─────────┼──────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼──────┼──────┼──────┼──────┼──────┼─────┴─────┼─────────┤
//    │         │ BT_HST1  │ BT_HST2 │ BT_HST3 │         │         │         │         │      │      │      │      │      │           │         │
//    ├─────────┼──────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼──────┼──────┼──────┼──────┼──────┼───────────┼─────────┤
//    │ RGB_TOG │ RGB_MOD  │ RGB_VAI │ RGB_HUI │ RGB_SAI │ RGB_SPI │         │         │      │      │      │      │      │           │         │
//    ├─────────┼──────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼──────┼──────┼──────┼──────┼──────┼───────────┼─────────┤
//    │         │ RGB_RMOD │ RGB_VAD │ RGB_HUD │ RGB_SAD │ RGB_SPD │         │         │      │      │      │      │      │           │         │
//    ├─────────┼──────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼──────┼──────┼──────┼──────┼──────┴─────┬─────┼─────────┤
//    │         │          │         │         │         │         │ BAT_LVL │ NK_TOGG │      │      │      │      │            │     │         │
//    ├─────────┼──────────┼─────────┼─────────┼─────────┴─────────┴─────────┴─────────┴──────┼──────┼──────┼──────┼──────┬─────┼─────┼─────────┤
//    │         │          │         │         │                                              │      │      │      │      │     │     │         │
//    └─────────┴──────────┴─────────┘         └──────────────────────────────────────────────┘      └──────┴──────┴──────┴─────┴─────┴─────────┘
[WIN_FN] = LAYOUT_iso_85(
  _______ , KC_BRID  , KC_BRIU , KC_TASK , KC_FILE , RGB_VAD , RGB_VAI , KC_MPRV , KC_MPLY , KC_MNXT , KC_MUTE , KC_VOLD , KC_VOLU , _______ , _______ , RGB_TOG,
  _______ , BT_HST1  , BT_HST2 , BT_HST3 , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,           _______ , _______,
  RGB_TOG , RGB_MOD  , RGB_VAI , RGB_HUI , RGB_SAI , RGB_SPI , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,           _______ , _______,
  _______ , RGB_RMOD , RGB_VAD , RGB_HUD , RGB_SAD , RGB_SPD , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,                     _______,
  _______ , _______  , _______ , _______ , _______ , _______ , BAT_LVL , NK_TOGG , _______ , _______ , _______ , _______ ,           _______ , _______ , _______,
  _______ , _______  , _______ ,                               _______                     ,           _______ , _______ , _______ , _______ , _______ , _______
),

//    ┌─────┬─────────┬─────────┬─────────┬─────────┬─────────┬──────────┬─────────┬─────────┬─────────┬─────────┬───────┬─────┬─────┬─────┬─────┐
//    │     │         │         │         │         │         │          │         │         │         │         │       │     │     │     │     │
//    ├─────┼─────────┼─────────┼─────────┼─────────┼─────────┼──────────┼─────────┼─────────┼─────────┼─────────┼───────┼─────┼─────┴─────┼─────┤
//    │     │         │         │         │         │         │          │         │         │         │         │       │     │           │     │
//    ├─────┼─────────┼─────────┼─────────┼─────────┼─────────┼──────────┼─────────┼─────────┼─────────┼─────────┼───────┼─────┼───────────┼─────┤
//    │     │         │ DE_UNDS │ DE_LBRC │ DE_RBRC │  CIRC   │ DE_EXLM  │ DE_LABK │ DE_RABK │ DE_EQL  │ DE_AMPR │       │     │           │     │
//    ├─────┼─────────┼─────────┼─────────┼─────────┼─────────┼──────────┼─────────┼─────────┼─────────┼─────────┼───────┼─────┼───────────┼─────┤
//    │     │ DE_BSLS │ DE_SLSH │ DE_LCBR │ DE_RCBR │ DE_ASTR │ DE_QUES  │ DE_LPRN │ DE_RPRN │ DE_SCLN │ DE_COLN │ DE_AT │     │           │     │
//    ├─────┼─────────┼─────────┼─────────┼─────────┼─────────┼──────────┼─────────┼─────────┼─────────┼─────────┼───────┼─────┴─────┬─────┼─────┤
//    │     │         │ DE_HASH │ DE_DLR  │ DE_PIPE │ DE_TILD │ BACKTICK │ DE_PLUS │ DE_PERC │ DE_DQUO │ DE_QUOT │       │           │     │     │
//    ├─────┼─────────┼─────────┼─────────┼─────────┴─────────┴──────────┴─────────┴─────────┼─────────┼─────────┼───────┼─────┬─────┼─────┼─────┤
//    │     │         │         │         │                                                  │         │         │       │     │     │     │     │
//    └─────┴─────────┴─────────┘         └──────────────────────────────────────────────────┘         └─────────┴───────┴─────┴─────┴─────┴─────┘
[WIN_L3] = LAYOUT_iso_85(
  _______ , _______ , _______ , _______ , _______ , _______ , _______  , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______,
  _______ , _______ , _______ , _______ , _______ , _______ , _______  , _______ , _______ , _______ , _______ , _______ , _______ ,           _______ , _______,
  _______ , _______ , DE_UNDS , DE_LBRC , DE_RBRC , CIRC    , DE_EXLM  , DE_LABK , DE_RABK , DE_EQL  , DE_AMPR , _______ , _______ ,           _______ , _______,
  _______ , DE_BSLS , DE_SLSH , DE_LCBR , DE_RCBR , DE_ASTR , DE_QUES  , DE_LPRN , DE_RPRN , DE_SCLN , DE_COLN , DE_AT   , _______ ,                     _______,
  _______ , _______ , DE_HASH , DE_DLR  , DE_PIPE , DE_TILD , BACKTICK , DE_PLUS , DE_PERC , DE_DQUO , DE_QUOT , _______ ,           _______ , _______ , _______,
  _______ , _______ , _______ ,                               _______                      ,           _______ , _______ , _______ , _______ , _______ , _______
),

//    ┌─────┬─────┬─────┬─────┬─────┬─────┬──────┬──────┬─────┬──────┬─────┬─────┬─────┬─────┬─────┬─────┐
//    │     │     │     │     │     │     │      │      │     │      │     │     │     │     │     │     │
//    ├─────┼─────┼─────┼─────┼─────┼─────┼──────┼──────┼─────┼──────┼─────┼─────┼─────┼─────┴─────┼─────┤
//    │     │     │     │     │     │     │      │      │     │      │     │     │     │           │     │
//    ├─────┼─────┼─────┼─────┼─────┼─────┼──────┼──────┼─────┼──────┼─────┼─────┼─────┼───────────┼─────┤
//    │     │     │  7  │  8  │  9  │     │      │      │     │      │     │     │     │           │     │
//    ├─────┼─────┼─────┼─────┼─────┼─────┼──────┼──────┼─────┼──────┼─────┼─────┼─────┼───────────┼─────┤
//    │     │     │  4  │  5  │  6  │     │ left │ down │ up  │ rght │     │     │     │           │     │
//    ├─────┼─────┼─────┼─────┼─────┼─────┼──────┼──────┼─────┼──────┼─────┼─────┼─────┴─────┬─────┼─────┤
//    │     │     │     │  1  │  2  │  3  │  0   │      │     │      │     │     │           │     │     │
//    ├─────┼─────┼─────┼─────┼─────┴─────┴──────┴──────┴─────┼──────┼─────┼─────┼─────┬─────┼─────┼─────┤
//    │     │     │     │     │                               │      │     │     │     │     │     │     │
//    └─────┴─────┴─────┘     └───────────────────────────────┘      └─────┴─────┴─────┴─────┴─────┴─────┘
[UTIL_L4] = LAYOUT_iso_85(
  _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______  , _______ , _______ , _______ , _______ , _______ , _______,
  _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______  , _______ , _______ , _______ ,           _______ , _______,
  _______ , _______ , KC_7    , KC_8    , KC_9    , _______ , _______ , _______ , _______ , _______  , _______ , _______ , _______ ,           _______ , _______,
  _______ , _______ , KC_4    , KC_5    , KC_6    , _______ , KC_LEFT , KC_DOWN , KC_UP   , KC_RIGHT , _______ , _______ , _______ ,                     _______,
  _______ , _______ , _______ , KC_1    , KC_2    , KC_3    , KC_0    , _______ , _______ , _______  , _______ , _______ ,           _______ , _______ , _______,
  _______ , _______ , _______ ,                               _______                     ,            _______ , _______ , _______ , _______ , _______ , _______
),

//    ┌──────┬──────┬──────┬────┬────┬────┬────┬────┬────┬────┬──────┬─────┬──────┬────────────┬──────┬─────────┐
//    │ esc  │  f1  │  f2  │ f3 │ f4 │ f5 │ f6 │ f7 │ f8 │ f9 │ f10  │ f11 │ f12  │ TG(GAMING) │ del  │ RGB_MOD │
//    ├──────┼──────┼──────┼────┼────┼────┼────┼────┼────┼────┼──────┼─────┼──────┼────────────┴──────┼─────────┤
//    │  `   │  1   │  2   │ 3  │ 4  │ 5  │ 6  │ 7  │ 8  │ 9  │  0   │  -  │  =   │       bspc        │  pgup   │
//    ├──────┼──────┼──────┼────┼────┼────┼────┼────┼────┼────┼──────┼─────┼──────┼───────────────────┼─────────┤
//    │ tab  │  q   │  w   │ e  │ r  │ t  │ y  │ u  │ i  │ o  │  p   │  [  │  ]   │        ent        │  pgdn   │
//    ├──────┼──────┼──────┼────┼────┼────┼────┼────┼────┼────┼──────┼─────┼──────┼───────────────────┼─────────┤
//    │ caps │  a   │  s   │ d  │ f  │ g  │ h  │ j  │ k  │ l  │  ;   │  '  │  \   │                   │  home   │
//    ├──────┼──────┼──────┼────┼────┼────┼────┼────┼────┼────┼──────┼─────┼──────┴────────────┬──────┼─────────┤
//    │ lsft │ iso\ │  z   │ x  │ c  │ v  │ b  │ n  │ m  │ ,  │  .   │  /  │       rsft        │  up  │   end   │
//    ├──────┼──────┼──────┼────┼────┴────┴────┴────┴────┼────┼──────┼─────┼──────┬────────────┼──────┼─────────┤
//    │ lctl │ lgui │ lalt │    │          spc           │    │ ralt │     │ rctl │    left    │ down │  rght   │
//    └──────┴──────┴──────┘    └────────────────────────┘    └──────┴─────┴──────┴────────────┴──────┴─────────┘
[GAMING] = LAYOUT_iso_85(
  KC_ESC  , KC_F1   , KC_F2   , KC_F3 , KC_F4 , KC_F5 , KC_F6 , KC_F7 , KC_F8 , KC_F9   , KC_F10  , KC_F11  , KC_F12  , TG(GAMING) , KC_DEL  , RGB_MOD,
  KC_GRV  , KC_1    , KC_2    , KC_3  , KC_4  , KC_5  , KC_6  , KC_7  , KC_8  , KC_9    , KC_0    , KC_MINS , KC_EQL  ,              KC_BSPC , KC_PGUP,
  KC_TAB  , KC_Q    , KC_W    , KC_E  , KC_R  , KC_T  , KC_Y  , KC_U  , KC_I  , KC_O    , KC_P    , KC_LBRC , KC_RBRC ,               KC_ENT , KC_PGDN,
  KC_CAPS , KC_A    , KC_S    , KC_D  , KC_F  , KC_G  , KC_H  , KC_J  , KC_K  , KC_L    , KC_SCLN , KC_QUOT , KC_BSLS ,                        KC_HOME,
  KC_LSFT , KC_NUBS , KC_Z    , KC_X  , KC_C  , KC_V  , KC_B  , KC_N  , KC_M  , KC_COMM , KC_DOT  , KC_SLSH ,              KC_RSFT , KC_UP   , KC_END ,
  KC_LCTL , KC_LGUI , KC_LALT ,                        KC_SPC                 ,           KC_RALT , _______ , KC_RCTL , KC_LEFT    , KC_DOWN , KC_RGHT
)
};

