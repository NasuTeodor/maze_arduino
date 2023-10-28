int start_pin = A0;
int kill_pin = A1;

bool isStarted() {
  if (digitalRead(start_pin) == 1)
    return true;
  return false;
}

//0 is for stop(kill pressed) 1 is for run(no kill press)
bool isKilled() {
  if (digitalRead(kill_pin) == 1)
    return true;
  return false;
}

bool opModeIsActive() {
  if (isStarted() && !isKilled())
    return true;
  return false;
}

bool isStopRequested() {
  if (isKilled())
    return true;
  return false;
}

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:

  int opModeisActive_state = opModeIsActive();
  int isStopRequested_state = isStopRequested();

  bool showInit = false;
  //init
  while (!opModeisActive_state && !isStopRequested_state) {
    if (!showInit) {
      Serial.print("Waiting in init.\n");
      showInit = true;
    }
    opModeisActive_state = opModeIsActive();
    isStopRequested_state = isStopRequested();
  }

  Serial.print("Begining execution.\n");

  if (isStopRequested())
    while (true) {
      //stop forever if killed
      Serial.print("Force Stop.");
    }
}

void loop() {
  // put your main code here, to run repeatedly:
}
