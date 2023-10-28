int start_pin = 6;
int kill_pin = 7;
// int start_pin = A0;
// int kill_pin = A1;


int A1A = 3;
int A1B = 2;


int B1A = 4;
int B1B = 5;

bool isStarted() {
  return digitalRead(start_pin) == HIGH;
}

bool isKilled() {
  return digitalRead(kill_pin) == LOW;
}

bool opModeIsActive() {
  // return isStarted() && !isKilled();
  return isStarted();
}

int initial_start_pin_state = 0;
bool robot_ready_state = false;


void setup() {



  Serial.begin(9600);
  // bool showInit = false;
  pinMode(start_pin, INPUT);
  pinMode(kill_pin, INPUT);
  pinMode(A1A, OUTPUT);
  pinMode(A1B, OUTPUT);
  pinMode(B1A, OUTPUT);
  pinMode(B1B, OUTPUT);

  pinMode(PD4, OUTPUT);


  initial_start_pin_state = digitalRead(start_pin);

  if (initial_start_pin_state == 1) {
    while (true) {
    }
  } else if (initial_start_pin_state == 0) {
    robot_ready_state = true;
  }

  //  int mode = true;
  //  while (true) {
  //
  //    digitalWrite(PD4, mode);
  //    mode = !mode;
  //    Serial.print("Start:");
  //    Serial.print(digitalRead(start_pin));
  //    Serial.print(' ');
  //    Serial.print("Kill:");
  //    Serial.print(digitalRead(kill_pin));
  //    Serial.print('\n');
  //    delay(300);
  //  }


  // while (!opModeIsActive()) {
  //   Serial.print(digitalRead(start_pin));
  //   Serial.print(" ");
  //   Serial.print(digitalRead(kill_pin));
  //   Serial.print('\n');
  //   if (!showInit) {
  //     Serial.print("Waiting in init.\n");
  //     showInit = true;
  //   }
  // }
  // Serial.print("Robot started");
}

int current_start_pin_state = 0;

void loop() {
  // Your main code goes here.
  while (current_start_pin_state == 0) {
    current_start_pin_state = digitalRead(start_pin);
    analogWrite(A1A, 0);
    analogWrite(A1B, 0);
    analogWrite(B1A, 0);
    analogWrite(B1B, 0);
  }
  if (current_start_pin_state == 1 && robot_ready_state == true) {



    while (current_start_pin_state == 1) {
      digitalWrite(A1A, LOW);
      digitalWrite(A1B, HIGH);
      digitalWrite(B1A, LOW);
      digitalWrite(B1B, HIGH);
      delay(500);
      digitalWrite(A1A, HIGH);
      digitalWrite(A1B, LOW);
      digitalWrite(B1A, HIGH);
      digitalWrite(B1B, LOW);
      delay(500);
      Serial.print("mama\n");
      current_start_pin_state = digitalRead(start_pin);
    }
    if (current_start_pin_state == 0) {
      analogWrite(A1A, 0);
      analogWrite(A1B, 0);
      analogWrite(B1A, 0);
      analogWrite(B1B, 0);
      while (true) {
      }
    }
  }
}