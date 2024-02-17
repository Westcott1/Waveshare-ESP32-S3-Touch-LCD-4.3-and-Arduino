bool GFXinitOK = false;

void setup() {
  Serial.begin(115200);
  // Serial.setDebugOutput(true);
  while (!Serial)
    ;
  Serial.println("\n-- Init --");

  TouchInit();
  delay(200);
  ExpanderInit();
  GFXinitOK = GFXinit();
  if (GFXinitOK) {
    Serial.println("GFX display initialised");
  }
}

void loop() {
#ifdef CANVAS
  GFXflush();
#endif

  TouchRead();

  delay(5);
}
