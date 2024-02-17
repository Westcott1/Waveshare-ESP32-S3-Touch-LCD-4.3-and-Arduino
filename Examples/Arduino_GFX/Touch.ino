#include <bb_captouch.h>

BBCapTouch bbct;

#define TOUCH_SDA 8
#define TOUCH_SCL 9
#define TOUCH_INT 4
#define TOUCH_RST 0

const char* szNames[] = { "Unknown", "FT6x36", "GT911", "CST820" };

void TouchInit() {
  Serial.println("Touch init...");
  // Init touch device
  bbct.init(TOUCH_SDA, TOUCH_SCL, TOUCH_RST, TOUCH_INT);
  int iType = bbct.sensorType();
  Serial.printf("Touch sensor type = %s\n", szNames[iType]);
}

void TouchRead() {
  TOUCHINFO ti;

  if (bbct.getSamples(&ti)) {  // if touch event happened
    BLblink();
    Serial.printf("Touch x: %d y: %d size: %d\n", ti.x[0], ti.y[0], ti.area[0]);
  }
}