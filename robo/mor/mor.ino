int start_pin = 6;

void setup() {
  Serial.begin(9600);
  pinMode(start_pin, INPUT);
}

void loop() {
  // Your main code goes here.

  int start_state = digitalRead(start_pin);
  while(true)
  {
    Serial.print(digitalRead(start_pin));
    Serial.print('\n');
  }
  // bool show = false;
  // while (start_state == 0) {
  //   if (!show) {
  //     Serial.print("Waiting in init.\n");
  //     show = !show;
  //   }
  //   start_state = digitalRead(start_pin);
  //   delay(200);
  // }

  // start_state = digitalRead(start_pin);
  // if (start_state == 1)
  //   Serial.print("Robot started.\n");
  delay(200);
}
