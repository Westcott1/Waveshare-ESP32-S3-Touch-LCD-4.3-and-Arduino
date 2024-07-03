#include <ESP_IOExpander_Library.h>
#include "Wire.h"

ESP_IOExpander *expander;

// Extender Pin define
#define TP_RST 1
#define LCD_BL 2
#define LCD_RST 3
#define SD_CS 4
#define USB_SEL 5

// I2C Pin define
#define I2C_MASTER_NUM 0
#define I2C_MASTER_SDA_IO 8
#define I2C_MASTER_SCL_IO 9

void ExpanderInit() {
  Serial.println("IO expander init...");
  Wire.begin(I2C_MASTER_SDA_IO, I2C_MASTER_SCL_IO);
  expander = new ESP_IOExpander_CH422G((i2c_port_t)I2C_MASTER_NUM, ESP_IO_EXPANDER_I2C_CH422G_ADDRESS_000);
  expander->init();
  expander->begin();
  expander->multiPinMode(TP_RST | LCD_BL | LCD_RST | SD_CS | USB_SEL, OUTPUT);
  BLblink();
//  expander->multiPinMode(LCD_BL | USB_SEL, OUTPUT);
//  expander->pinMode( LCD_BL, OUTPUT);
//  expander->digitalWrite(USB_SEL, LOW);
//  expander->multiDigitalWrite(TP_RST | LCD_BL | LCD_RST | SD_CS | USB_SEL, HIGH);
//  expander->multiDigitalWrite(TP_RST | LCD_BL | LCD_RST | SD_CS | USB_SEL, LOW);
}

void BLset(byte state){
    expander->digitalWrite(LCD_BL, state);
}

void BLblink(){
  //Turn off backlight
  BLset(LOW);
  delay(100);
  BLset(HIGH);
  delay(100);
}