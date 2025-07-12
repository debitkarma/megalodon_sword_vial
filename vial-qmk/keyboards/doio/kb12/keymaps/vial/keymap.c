/* Copyright 2022 DOIO
 * Copyright 2022 DOIO2022 <https://github.com/DOIO2022>
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


#include QMK_KEYBOARD_H

// commenting out because we're using use numbers
// because vial requires that for encoder maps
/*enum layer_names {
    _LAY0,
    _LAY1,
    _LAY2,
    _LAY3,
    _LAY4,
    _LAY5
};*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
		TO(1), KC_F1,   KC_F2,   KC_F3,   KC_F4,      KC_F5,   KC_F6,   KC_F7,   KC_F8,      KC_F9,   KC_F10,  KC_F11,  KC_F12),
  [1] = LAYOUT(
		TO(2), KC_KB_VOLUME_UP, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, QK_BOOT),
  [2] = LAYOUT(
		TO(3), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
  [3] = LAYOUT(
		TO(4), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
  [4] = LAYOUT(
		TO(5), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
  [5] = LAYOUT(
		TO(0), RGB_TOG, RGB_MOD, RGB_SPI, RGB_SPD,    RGB_SAI, RGB_SAD, RGB_HUI, RGB_HUD,    RGB_VAI, RGB_VAD, KC_TRNS, KC_TRNS)

};

#ifdef ENCODER_MAP_ENABLE
// const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = { ENCODER_CCW_CW(TO(5), TO(1)) },
    [1] = { ENCODER_CCW_CW(TO(0), TO(2)) },
    [2] = { ENCODER_CCW_CW(TO(1), TO(3)) },
    [3] = { ENCODER_CCW_CW(TO(2), TO(4)) },
    [4] = { ENCODER_CCW_CW(TO(3), TO(5)) },
    [5] = { ENCODER_CCW_CW(TO(4), TO(0)) },
};
#endif

// Set solid color on
void keyboard_post_init_user(void) {
    // Setting mode to solid color
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);

    // Setting default color immediately
    // HSV 192, 255, 255 == RGB 87 00 FF
    // rgb_matrix_sethsv_noeeprom(192, 255, 255);
    rgb_matrix_sethsv_noeeprom(0xC1, 0xFF, 0xFF);


    // below line taken from docs at:
    // https://docs.qmk.fm/features/rgb_matrix#callbacks
    // See Indicators without RGB Matrix Effect
    // It turns off colors, and we don't want that
    // But it's useful for testing
    // rgb_matrix_sethsv_noeeprom(HSV_OFF);
};

// RGB underglow for layer state
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case 5:
        // rgb_matrix_set_color_all (0xD6,  0xFF, 0xF9);
        rgb_matrix_sethsv_noeeprom(0x79, 0x29, 0xFF);
        break;
    case 4:
        // rgb_matrix_set_color_all (0xEC,  0x83, 0xEA);
        rgb_matrix_sethsv_noeeprom(0xD5, 0x70, 0xED);
        break;
    case 3:
        // rgb_matrix_set_color_all (0x1D,  0xDE, 0xBE); // #1D DE BE
        rgb_matrix_sethsv_noeeprom(0x78, 0xDE, 0xDE);
        break;
    case 2:
        // rgb_matrix_set_color_all (0x0C,  0xFF, 0x00);
        rgb_matrix_sethsv_noeeprom(0x53, 0xFF, 0xFF);
        break;
    case 1:
        // rgb_matrix_set_color_all (0xFF,  0xF1, 0x10);
        rgb_matrix_sethsv_noeeprom(0x28, 0xF0, 0xFF);
        break;
    default: //  the default layer (which is 0)
        rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
        // rgb_matrix_set_color_all (0x87,  0x00, 0xFF);
        rgb_matrix_sethsv_noeeprom(0xC1, 0xFF, 0xFF);

	    // below shows you how to use animations per layer
        // rgb_matrix_mode(RGB_MATRIX_CYCLE_ALL);
        break;
    }
  return state;
};
