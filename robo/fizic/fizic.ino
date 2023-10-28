#include <VL53L0X.h>

#include <Arduino.h>
#include <TinyMPU6050.h>

MPU6050 mpu(Wire);
VL53L0X tof;

int left_gnd = 2;
int left_vcc = 3;
// int left_vcc = A1;
int right_gnd = 5;
int right_vcc = 4;
// int right_vcc = A0;

double heading = 0;
double delta = 5;

double limit = 30;

int power_pin = 9;
int gnd_pin = 10;
int status = 12;

void imu_init() {
  Serial.println("Calibration started!");
  mpu.Initialize();
  mpu.Calibrate();
  Serial.println("Calibration complete!");
}

void tof_init() {
  tof.setTimeout(500);
  if (!tof.init()) {
    Serial.println("Failed to detect and initialize tof!");
    while (1) {}
  }
  tof.startContinuous();
}

void motor_init() {
  pinMode(left_vcc, OUTPUT);
  pinMode(left_gnd, OUTPUT);
  pinMode(right_vcc, OUTPUT);
  pinMode(right_gnd, OUTPUT);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();

  tof.setTimeout(500);
  if (!tof.init()) {
    Serial.println("Failed to detect and initialize tof!");
    while (1) {}
  }

  // Start continuous back-to-back mode (take readings as
  // fast as possible).  To use continuous timed mode
  // instead, provide a desired inter-measurement period in
  // ms (e.g. tof.startContinuous(100)).
  tof.startContinuous();
  // tof_init();
  imu_init();
  motor_init();
  heading = mpu.GetAngGyroZ();
  delay(100);
  Serial.println(heading);

  pinMode(power_pin, OUTPUT);
  pinMode(gnd_pin, INPUT);
  pinMode(status, INPUT);
  digitalWrite(power_pin, HIGH);
}

bool isStarted() {
  return (bool)digitalRead(status);
}

void loop() {
  // put your main code here, to run repeatedly:
  double target_heading = heading - 90;
  // while (true) {
  // while (!isStarted()) {
  // }
  while (getDistance() >= limit ) {
    drive_front();
    Serial.println(tof.readRangeContinuousMillimeters());
  }
  mpu.Execute();
  double error = abs(abs(target_heading) - abs(heading));
  Serial.println("Heading");
  while (true) {
    mpu.Execute();
    heading = mpu.GetAngGyroZ();
    error = abs(abs(target_heading) - abs(heading));
    if (error >= delta) {
      Serial.println(heading);
      drive_right();
    } else {
      drive_stop();
    }
  }
  // while (error >= delta) {
  //   mpu.Execute();
  //   Serial.println(heading);
  //   heading = mpu.GetAngGyroZ();
  //   error = abs(abs(target_heading) - abs(heading));
  //   drive_right();
  // }
  // drive_stop();
  // target_heading = 90;
  // while (error >= delta) {
  //   mpu.Execute();
  //   heading = mpu.GetAngGyroZ();
  //   error = abs(abs(target_heading) - abs(heading));
  //   drive_right();
  // }
  drive_stop();
  while (true) {
    //stop
  }
}

int getDistance() {
  if (tof.timeoutOccurred()) { return false; }
  return tof.readRangeContinuousMillimeters();
}

void drive_stop() {
  Serial.println("STOP");
  digitalWrite(left_vcc, LOW);
  digitalWrite(left_gnd, LOW);
  digitalWrite(right_vcc, LOW);
  digitalWrite(right_gnd, LOW);
}

void drive_right() {
  // analogWrite(left_gnd, 127);
  digitalWrite(left_vcc, LOW);
  digitalWrite(left_gnd, HIGH);
  digitalWrite(right_vcc, HIGH);
  digitalWrite(right_gnd, LOW);
  // analogWrite(right_vcc, 127);
}

void drive_back() {
  digitalWrite(left_vcc, LOW);
  digitalWrite(left_gnd, HIGH);
  // analogWrite(left_gnd, 127);
  digitalWrite(right_vcc, LOW);
  digitalWrite(right_gnd, HIGH);
  // analogWrite(right_gnd, 127);
}

void drive_front() {
  // analogWrite(left_gnd, 127);
  digitalWrite(left_vcc, LOW);
  digitalWrite(left_gnd, HIGH);
  digitalWrite(right_vcc, LOW);
  digitalWrite(right_gnd, HIGH);
  // analogWrite(right_vcc, 127);
}

void drive_left() {
  digitalWrite(left_vcc, HIGH);
  digitalWrite(left_gnd, LOW);
  digitalWrite(right_vcc, LOW);
  digitalWrite(right_gnd, HIGH);
}
