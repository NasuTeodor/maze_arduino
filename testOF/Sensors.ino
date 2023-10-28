#include "Config.h"

#include <Adafruit_VL53L0X.h>
#include <vl53l0x_api.h>
#include <vl53l0x_api_calibration.h>
#include <vl53l0x_api_core.h>
#include <vl53l0x_api_ranging.h>
#include <vl53l0x_api_strings.h>
#include <vl53l0x_def.h>
#include <vl53l0x_device.h>
#include <vl53l0x_i2c_platform.h>
#include <vl53l0x_interrupt_threshold_settings.h>
#include <vl53l0x_platform.h>
#include <vl53l0x_platform_log.h>
#include <vl53l0x_tuning.h>
#include <vl53l0x_types.h>
#include <TinyMPU6050.h>

//store sensor objects
Adafruit_VL53L0X lox1;
Adafruit_VL53L0X lox2;
Adafruit_VL53L0X lox3;

MPU6050 mpu(Wire);

//store sensor measurements results
VL53L0X_RangingMeasurementData_t distanceMeasure1;
VL53L0X_RangingMeasurementData_t distanceMeasure2;
VL53L0X_RangingMeasurementData_t distanceMeasure3;

int headingMeasure;

void distanceSensorInit() {
  //init the sensors
  lox1 = Adafruit_VL53L0X();
  lox2 = Adafruit_VL53L0X();
  lox3 = Adafruit_VL53L0X();

  //init and configure the xshut pins
  pinMode(xshut1, OUTPUT);
  pinMode(xshut2, OUTPUT);
  pinMode(xshut3, OUTPUT);
  //shutdown the pins => reset sensors
  digitalWrite(xshut1, LOW);
  digitalWrite(xshut2, LOW);
  digitalWrite(xshut3, LOW);

  //begin routine
  //START LXO1
  digitalWrite(xshut1, HIGH);
  //set address to lox1
  if (!lox1.begin(addr1)) {
    return false;
  }
  delay(10);

  //START LXO2
  digitalWrite(xshut2, HIGH);
  digitalWrite(xshut3, LOW);
  //set address to lox2
  if (!lox1.begin(addr2)) {
    return false;
  }
  delay(10);

  //START LXO3
  digitalWrite(xshut3, HIGH);
  //set address to lox3
  if (!lox1.begin(addr3)) {
    return false;
  }
  delay(10);

  //teoretic au pornit toti senzorii bine
  return true;
}

void initGyroSensor() {
  mpu.Initialize();
  mpu.Calibrate();
  return true;
  //ceva e bun cred
}

void sensorsInit() {
  try {
    distanceSensorInit();
    initGyroSensor();
  } catch {
    Serial.print("nu vrea");
    return false;
  }
}
