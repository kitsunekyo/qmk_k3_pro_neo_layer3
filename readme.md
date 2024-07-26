# Neo Layer 3 QMK Keymap for Keychron K3 Pro

The ergonomics of the neo keyboard layout are great. The installation story on multiple OS not so much. 
This QMK keymap implements a variation of neo layer 3, to have easy access to special characters for software development.

Reference the official guide on [https://docs.qmk.fm/](https://docs.qmk.fm/).

## Building Firmware for K3 Pro

Keychron isnt great when it comes to QMK support. While they love to market their keyboards as QMK supported, you have to manually build the firmware from their fork.

To add to the confusion, their fork is not using the `master` branch but (depending on your keyboard) either `bluetooth_playground` or `wireless_playground`. From what I've read, `bluetooth_` is for K Pro and Q Pro Bluetooth, and `wireless_` for Max Series. [see github issue...](https://github.com/Keychron/qmk_firmware/issues/217#issuecomment-1899558528)

I installed the prerequisites and ran this

```bash
git clone https://github.com/Keychron/qmk_firmware.git
cd qmk_firmware
git checkout bluetooth_playground
make git-submodule
```

After that, I could continue with the guide [https://docs.qmk.fm/newbs_building_firmware](https://docs.qmk.fm/newbs_building_firmware)
