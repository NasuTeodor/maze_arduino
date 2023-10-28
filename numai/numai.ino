#include "VL53L0X.h"
#include <Wire.h>

VL53L0X tof;
VL53L0X tof0;

int power_pin = 2;

void setup() {

  Serial.begin(9600);
  Wire.begin();
  tof.setTimeout(500);
  tof0.setTimeout(500);
  tof.startContinuous();
  tof0.startContinuous();

  // tof.setAddress(0x52);
  // tof0.setAddress(0x54);
  // tof.setAddress(0x52);
  // tof0.setAddress(0x68);
  while (!Serial)
    ;  // Leonardo: wait for serial monitor
  Serial.println("I2C Scanner");
}


void loop() {
  byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for (address = 1; address < 127; address++) {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.print(address, HEX);
      Serial.println("  !");

      nDevices++;
    } else if (error == 4) {
      Serial.print("Unknown error at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }*
  if (nDevices == 0)
    Serial.println("No I2C devices found");
  else
    Serial.println("done");

  Serial.println(tof.readRangeContinuousMillimeters());
  delay(5000);  // wait 5 seconds for next scan
}