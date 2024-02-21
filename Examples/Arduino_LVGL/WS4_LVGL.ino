#include <TimeAlarms.h>

#define TFT_HOR_RES   800
#define TFT_VER_RES   480

void setup() {
  Serial.begin(115200);
  // Serial.setDebugOutput(true);
  while (!Serial)
    ;
  Serial.println("\n-- Init --");

  TouchInit();
  delay(200);
  ExpanderInit();

  if (GFXinit()) {
    sleep(1);
    LVGLinit();
  }
}

void loop() {
  LvTimerHandler(); // let the GUI do its work 
#ifdef CANVAS
  GFXflush();
#endif
  Alarm.delay(5);
}
