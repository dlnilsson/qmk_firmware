#include QMK_KEYBOARD_H
#if __has_include("keymap.h")
#    include "keymap.h"
#endif



enum layer_names {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST
};

enum custom_keycodes {
  LOWER = SAFE_RANGE,
  RAISE,
  ADJUST,
  AA, // Custom keycode for leftCtrl + rightAlt + W
  AE,              // Custom keycode for leftCtrl + rightAlt + A
  OO               // Custom keycode for leftCtrl + rightAlt + O
};

// qmk compile -kb  omkbd/ergodash/rev1  -km dlnilsson
// user.keyboard=omkbd/ergodash/rev1
// qmk compile -kb omkbd/ergodash/rev1 -km default

#define EISU LALT(KC_GRV)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


  [_QWERTY] =  LAYOUT_3key_2us(
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_MINS, KC_EQL, KC_6, KC_7, KC_8, KC_9, KC_0, KC_HOME,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_LBRC, KC_RBRC, KC_Y, KC_U, KC_I, KC_O, KC_P, AA,
        KC_BACKSLASH, KC_A, KC_S, KC_D, KC_F, KC_G, KC_COLN, KC_QUOT, KC_H, KC_J, KC_K, KC_L, OO, AE,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_SCLN, KC_LCTL,
        KC_LCTL, KC_LEFT_ALT, KC_LEFT_ALT, KC_LGUI, LOWER, KC_SPC, KC_ENT, KC_BSPC, RAISE, KC_APP, KC_RCTL, KC_RALT, KC_NO
    ),



  [_LOWER] = LAYOUT_3key_2us(
        KC_ESC, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_LPRN, KC_RPRN, KC_NO, KC_NO, KC_PSLS, KC_PAST, KC_PMNS,KC_NO,
        KC_TRANSPARENT, KC_PAGE_UP, KC_NO, KC_UP, KC_NO, KC_PGUP, KC_EQL, KC_BSLS, KC_NO, KC_P7, KC_P8, KC_P9,KC_PPLS, KC_NO,
        KC_TRANSPARENT, KC_PAGE_DOWN, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_GRV, KC_EQL, KC_NO, KC_P4,KC_P5, KC_P6, KC_PCMM, KC_NO,
        KC_TRANSPARENT, KC_NO, KC_NO, KC_PSCR, KC_NO, KC_NO, KC_NO, KC_P1, KC_P2,KC_P3, KC_PEQL, KC_NO, KC_LCTL,
        KC_LCTL, KC_LEFT_ALT, KC_LEFT_ALT, KC_LGUI, LOWER, KC_SPC, KC_ENT, KC_DEL, KC_NO, KC_P0, KC_PDOT, KC_PENT, KC_NO
    ),


  [_RAISE] = LAYOUT_3key_2us(
        KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_CAPS_LOCK,
        KC_TRANSPARENT, KC_NO, KC_NO, KC_MPRV, KC_MNXT, KC_BACKSLASH, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_TRANSPARENT, KC_NO, KC_NO, KC_MSTP, KC_MPLY, KC_VOLU, KC_GRAVE, KC_GRAVE, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_TRANSPARENT, KC_NO, KC_NO, KC_NO, KC_NO, KC_VOLD, KC_NO, KC_NO, KC_NO, KC_NO,KC_NO, KC_NO, KC_NO,
        KC_LCTL, KC_LEFT_ALT, KC_LEFT_ALT, KC_LGUI, LOWER, KC_SPC, KC_ENT, KC_DEL, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
    )
};


#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {

};
#endif // defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)


#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case AA:
        if (record->event.pressed) {
            register_code(KC_RIGHT_ALT);  // Press right Alt
            register_code(KC_W);     // Press W
        } else {
            unregister_code(KC_W);   // Release W
            unregister_code(KC_RIGHT_ALT); // Release right Alt
        }
        return false; // Skip all further processing of this key
        break;
    case AE:
        if (record->event.pressed) {
            register_code(KC_RIGHT_ALT);  // Press right Alt
            register_code(KC_A);     // Press A
        } else {
            unregister_code(KC_A);   // Release A
            unregister_code(KC_RIGHT_ALT); // Release right Alt
        }
        return false; // Skip all further processing of this key
        break;
    case OO:
        if (record->event.pressed) {
            register_code(KC_RIGHT_ALT);  // Press right Alt
            register_code(KC_O);     // Press O
        } else {
            unregister_code(KC_O);   // Release O
            unregister_code(KC_RIGHT_ALT); // Release right Alt
        }
        return false; // Skip all further processing of this key
        break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}
