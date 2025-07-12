// Copyright 2023 Oleg Titov <oleg.titov@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Unique keyboard id
#define VIAL_KEYBOARD_UID {0x3D, 0x84, 0x24, 0x54, 0xAA, 0xE1, 0xA2, 0x09}

// Unlock with first and last keys
#define VIAL_UNLOCK_COMBO_ROWS { 0, 2 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 3 }

// Try setting magic vial serial: "vial:f64c2b3c:0000001"
// already done in vial-qmk/builddefs/build_vial.mk
// #define SERIAL_NUMBER {0x76, 0x69, 0x61, 0x6c, 0x3a, 0x66, 0x36, 0x34, 0x63, 0x32, 0x62, 0x33, 0x63, 0x3a, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x31}

// Define Encoders Pad, copied from keyboard.json
// #define ENCODERS_PAD_A { B5 }
// #define ENCODERS_PAD_B { B6 }
// #define ENCODER_RESOLUTION 1
