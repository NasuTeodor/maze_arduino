#include <VL53L0X.h>

#include <Wire.h>
#include "MPU6050.h"

#define G_GAIN 0.070  // [deg/s/LSB]
#define AA 0.97       // complementary filter constant
#define DT 0.02       // Loop time

int start_pin = 6;
int start_report = 2;

MPU6050 mpu;

byte buff[6];
int accRaw[3];
int magRaw[3];
int gyrRaw[3];
float rate_gyr_y = 0.0;  // [deg/s]
float rate_gyr_x = 0.0;  // [deg/s]
float rate_gyr_z = 0.0;  // [deg/s]
float gyroXangle = 0.0;
float gyroYangle = 0.0;
float gyroZangle = 0.0;
float AccYangle = 0.0;
float AccXangle = 0.0;
float CFangleX = 0.0;
float CFangleY = 0.0;

unsigned long startTime;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(start_pin, INPUT);
  pinMode(start_report, OUTPUT);
  delay(1000);



}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(start_report, digitalRead(start_pin));

  if (digitalRead(start_pin)) {

    while (!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G)) {
      Serial.print("Could not find a valid MPU6050 sensor, check wiring!");
      delay(100);
    }
    // Vector rawAccel = mpu.readRawAccel();
    Vector normAccel = mpu.readNormalizeAccel();

    // Serial.print(" Xraw = ");
    // Serial.print(rawAccel.XAxis);
    // Serial.print(" Yraw = ");
    // Serial.print(rawAccel.YAxis);
    // Serial.print(" Zraw = ");
    // Serial.println(rawAccel.ZAxis);

    // Serial.print(" Xnorm = ");
    // Serial.print(normAccel.XAxis);
    // Serial.print(" Ynorm = ");
    // Serial.print(normAccel.YAxis);
    // Serial.print(" Znorm = ");
    // Serial.println(normAccel.ZAxis);
  }
  delay(10);
  // Serial.print('\n');
}
