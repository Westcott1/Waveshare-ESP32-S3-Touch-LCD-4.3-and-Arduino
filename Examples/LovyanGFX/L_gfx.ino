#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include "Pins.h"

LGFX gfx;

void LgfxInit() {
  Serial.println("Lgfx init...");

  gfx.init();

  BLset(HIGH);
  //  gfx.setBrightness(200);
  //  gfx.setRotation(2);

  gfx.fillScreen(0x003030);
  gfx.fillRect(0, 0, 800, 70, 0x000028);
  gfx.setTextColor(TFT_WHITE);
  gfx.setTextSize(4);
  gfx.setCursor(250, 20);
  gfx.println(title);

  gfx.setTextColor(TFT_GREEN);
  gfx.setTextSize(3);
}

// Only if GFX does the touch handling
void LgfxDoTouch() {
  int32_t x, y;
  if (gfx.getTouch(&x, &y)) {
    Serial.printf("X:%d Y:%d\n", x, y);
    gfx.fillCircle(x, y, 15, TFT_WHITE);
  }
}
