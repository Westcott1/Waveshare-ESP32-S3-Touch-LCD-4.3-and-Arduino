#include <TimeAlarms.h>

const char* title = "Hello World";

void setup() {
  Serial.begin(115200);
  while (!Serial)
    ;

  Serial.println("Initialising...");

  //  TouchInit();
  Alarm.delay(200);
  ExpanderInit();
  LgfxInit();
  Serial.println("Lgfx initialised");
}

void loop() {
  LgfxDoTouch();
  Alarm.delay(5);
}
