# Vial for the Megalodon Sword

This is a Vial keymap and configuration for the Megalodon Sword (DOIO KB12-01), along with extended notes and stuff.

## Background (if you're curious)

### Purpose

An internet friend, [FirstOriginalOGSteve2](https://twitch.tv/FirstOriginalOGSteve2), saw my code for my [bdn9_3rotaryenc](https://github.com/debitkarma/bdn9_3rotaryenc/) and asked about getting the per-layer backlight feature working on this particular keyboard, but also keeping it Vial-compatible. My original code was QMK-only, so I went down a bit of a rabbit-hole.

### The Keyboard

[KeebMonkey's Megalodon Sword](https://www.keebmonkey.com/products/12-key-1-knob-mechanical-keyboard?srsltid=AfmBOoouv-jazdiGQoc-JSIS7wCL2wX7Y-nmBmSMB24Gm1zREFwvWbL9), also known by the manufacturer's more generic name of DOIO KB12, is essentially a 12 key F-row with a rotary encoder on the left side.

I can't say too much, since I don't own one myself, but the appeal of this seems to be:

* It's compact, and great as an addition to your smaller keyboard.
* The rotary encoder has very satisfying detents and has a very nice feel.
* There's per-key RGB
* It can run QMK, Via, and Vial!

The board is based on an STM32F103. I assume there's 64k available, but the default firmware is ~54kb, so we kept it to that or less. It uses the stm32duino bootloader.

### The Request

FirstOriginalOGSteve2's main requirements for a customer fw for this keyb were as follows:

* It should show which layer it's on via different backlight colors
* It should (ideally) work with the Vial application (he's using the official AppImage on Linux Mint).
* The dial doesn't matter much in terms of reprogramming - he's using it to quickly change layers dynamically.
* As much info should be made available in order to keep him as independent as possible - a very much appreciated, entirely understandable, and eminently sane request.

## Changes from the Regular Vial Config

This was an interesting journey. Being familiar with QMK, a lot of the assumptions I initially made turned out to not be true. I had to peel back layers, since Vial is sort of built atop Via (or had some kind of compatibility? I still don't know), and that is built on top of QMK, which is itself modeled on TMK.

Below, I'll explain the changes I made from the [same config in the Official Vial Repository](https://github.com/vial-kb/vial-qmk/tree/vial/keyboards/doio/kb12). I don't care enough to dive into the history of where those files came from, and how they gained the compatibility they have, and who worked on it all. I bet it'd make for an interesting exercise, but I don't have the time or the attention span.

Finally, let's look at the different changes we made to the default Vial stuff.

### keyboard.json

### rules.mk

### config.h

### keymap.c


## Important Takeaways

### Setup

Use the official Vial guide to get set up.

* We used `uv tool install qmk` to install the qmk command/toolbox/etc.
* We used `qmk doctor` to test things, and then we had to compile qmk submodules, too.
* We did a `git clone` of the official vial-qmk repository.
* We setup `qmk`'s home directory to be the new `vial-qmk` folder (that came from the git clone process)
* We tried to fix errors that came up as we compiled the default firmware with the instructions below.
* ***WE DID NOT FLASH THE RESULTING DEFAULT FIRMWARE!***

### Keymap Naming

Normally, you need to use `qmk`'s tool to create a new keymap, or it won't be added to the index (you can check if qmk can "see" your keyboards and keymaps with `qmk list-keyboards` and `qmk list-keymaps`). You need to use `qmk new-keyboard` or `qmk new-keymap`. ***HOWEVER*** This is not true for Via, apparently?

But in Vial, all of that is moot anyway - you *have* to use the keymap named `vial` and you can't use another one, or it won't compile properly. Ask me how I know this...

### Vial with QMK

You can create a `keymap.c` and `rules.mk` for your keyboard and compile the firmware, and then that'll be baked into the keyboard. Then, when you use Vial, it will change many of those settings.

If you reset the keyboard, it'll go back to your compiled firmware.

### EEPROM

I have no idea why, but trying to change layer lighting with saving changes to the EEPROM doesn't work for me. The per-key lighting works using QMK's `rgb_matrix` construct, NOT `backlight` or `rgblight`.

I tried to use `rgb_matrix_setrgb()` but it wouldn't work, and I'm clearly missing something about how this all works because IDK WHY. I ended up using `rgb_matrix_sethsv_noeeprom()`. This is less than ideal because you can't drop in and use regular HTML hex color codes, you have to convert to HSV - and then convert *those* values from (degrees (0-360), percent (0-100), percent (0-100)) to hex values for all three (0-255). Another pain, but something I can write a simple tool to do.

If anyone can confirm how to change things so `rgb_matrix_setrgb()` works, or if there's a `rgb_matrix_setrgb_noeeprom()` function somewhere, please let me know.

### THIS IS UNFINISHED

This config is... like 98% of the way there.
* Colors change with the layers.
* All lights are set to the same color so you can tell easily which layer yoy're on.
* Vial works to set all the keys and stuff.

What does NOT work:
* Can't change/set rotary encoder functions for rotation via Vial.
  * Rotary encoder button still works per usual!
* Can't reference RGB values in the firmware files.

### UDEV Rules, Compiling, and Flashing

We ran into some early issues with udev rules because we had to use QMK's to flash the firmware, but then switch to Vial's in order to get Vial working. We realized that the app wasn't actually the same version of Official Vial. At some point in our process, our firmware stopped working with this non-official version so the keyboard wouldn't be recognized by it.

However, the Official app sees the keyboard just fine, and Vial's magic serial number is present (which you can check with `sudo lsusb -v`). And, the official app works just fine with [QMK's udev rules](https://github.com/qmk/qmk_firmware/blob/master/util/udev/50-qmk.rules) AND [Vial's udev rules](https://get.vial.today/manual/linux-udev.html) in place at the same time.

To compile, run `make doio/kb12:vial`. Easy. If this doesn't work, different commands probably won't help you and you need to go back to the files or check codebase versions or something.

To flash, the make method did NOT work for us. We ended up having to resort to putting the keyboard in its bootloader mode via boot magic (hold down the dial button as you plug the keyboard in). What *did* work was `qmk flash -b doio_kb12_vial.bin` (when in your `vial-qmk` older, or `path/to/compiled/binfile otherwise`).

### External Resources

* [Official Vial Repository](https://github.com/vial-kb/vial-qmk/tree/vial/keyboards/doio/kb12)
* [First time use guide for Vial](https://get.vial.today/manual/first-use.html)
* [Vial's guide to porting, which shows some important caveats](https://get.vial.today/docs/porting-to-vial.html)
* [Vial's rotary encoder docs](https://get.vial.today/docs/encoders.html)
* [QMK's rotary encoder docs](https://docs.qmk.fm/features/encoders#encoders)
* **[Officially compiled Vial firmware for this keyboard!!](https://okin.gitlab.io/vial-qmk-firmwares/#doio_kb12)**
* [Vial Official App download link](https://get.vial.today/download/)
* [Via's Specification, which shows some important caveats](https://caniusevia.com/docs/specification/)
* [Via's JSON for this keyboard, for reference](https://github.com/the-via/keyboards/blob/master/v3/doio/kb12/kb12-01.json)
* [QMK Reference Schema for keyboard.json (formerly info.json)](https://github.com/qmk/qmk_firmware/blob/master/data/schemas/keyboard.jsonschema)
* [KeebMonkey's JSON file (for Via/l) and Default FW bin file on their wiki](https://wiki.keebmonkey.com/en/guides/doiofirmware)
* [QMK's udev rules file](https://github.com/qmk/qmk_firmware/blob/master/util/udev/50-qmk.rules)
