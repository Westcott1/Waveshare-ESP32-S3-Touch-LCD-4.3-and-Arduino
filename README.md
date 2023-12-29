### Waveshare ESP32-S3-Touch-LCD-4.3 using the Arduino IDE

https://www.waveshare.com/wiki/ESP32-S3-Touch-LCD-4.3#Demo

I got one of these recently, but could find no sample Arduino code in the Waveshare Wiki.

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
    14 /* B0 */,
    38 /* B1 */,
    18 /* B2 */,
    17 /* B3 */,
    10 /* B4 */,
    39 /* G0 */,
    0 /* G1 */,
    45 /* G2 */,
    48 /* G3 */,
    47 /* G4 */,
    21 /* G5 */,
    1 /* R0 */,
    2 /* R1 */,
    42 /* R2 */,
    41 /* R3 */,
    40 /* R4 */,
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

I'm now trying to the the touch to work using the CST816S library.

SDA=8, SCL=9, IRQ=4

However, touch RST is expansion pin 1, I've not got the expansion pins to work yet.

They also say you can use one of the expansion pins as Backlight control.
