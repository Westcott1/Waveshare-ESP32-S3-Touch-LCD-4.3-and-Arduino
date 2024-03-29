### Waveshare ESP32-S3-Touch-LCD-4.3 using the Arduino IDE

https://www.waveshare.com/wiki/ESP32-S3-Touch-LCD-4.3

NEW - I've added an example using Arduino_GFX.

TODO - Add an example using Arduino_GFX and LVGL.

Thanks to VollWombat for all his help.

The WaveShare demo software download contains an Arduino branch with code for each of the examples. The most useful is lvg_porting.
https://www.waveshare.com/wiki/ESP32-S3-Touch-LCD-4.3#Demo

This repository will hopefully grow as I find out how to use all of the board's features.

Also hopefully, it will prove useful to anyone else with this board.

Despite much Googling, no examples turned up, so I'm having to start nearly from scratch.

First, to get the basic graphics going I discovered the wonders of Moononournation's Arduino_GFX library.
https://github.com/moononournation/Arduino_GFX

Waveshare have thoughtfully given the GPIO pin mapping for their panel, so I put them into the panel constructors -
```
#define GFX_DEV_DEVICE WAVESHARE_ESP32_S3_TFT_4_3
//define GFX_BL 2

Arduino_ESP32RGBPanel *rgbpanel = new Arduino_ESP32RGBPanel(
    5 /* DE */,
    3 /* VSYNC */,
    46 /* HSYNC */,
    7 /* PCLK */,

  1 /* R0 */,
  2 /* R1 */,
  42 /* R2 */,
  41 /* R3 */,
  40 /* R4 */,

  39 /* G0 */,
  0 /* G1 */,
  45 /* G2 */,
  48 /* G3 */,
  47 /* G4 */,
  21 /* G5 */,

  14 /* B0 */,
  38 /* B1 */,
  18 /* B2 */,
  17 /* B3 */,
  10 /* B4 */,

    0 /* hsync_polarity */, 40 /* hsync_front_porch */, 48 /* hsync_pulse_width */, 88 /* hsync_back_porch */,
    0 /* vsync_polarity */, 13 /* vsync_front_porch */, 3 /* vsync_pulse_width */, 32 /* vsync_back_porch */,
    1 /* pclk_active_neg */, 16000000 /* prefer_speed */
);

Arduino_RGB_Display *gfx = new Arduino_RGB_Display(
    800 /* width */,
    480 /* height */, 
    rgbpanel, 
    0 /* rotation */, 
    true /* auto_flush */
);
```
Much to my surprise the example code ran!

Touch is controlled by a GT911, and works well with the bb_captouch library.

SDA=8, SCL=9, IRQ=4

The expansion pin chip can be accessed with ESP_IOExpander_Library.h.
Part of the  s3-4.3-libraries download from the Wageshare wiki page
https://files.waveshare.com/wiki/ESP32-S3-Touch-LCD-4.3/Esp32-s3-touch-lcd-lib.zip 
