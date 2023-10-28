int current_start_pin_state = 0;
int current_stop_pin_state = 0;
bool robot_ready_state = false;
int start_pin = A0;
int kill_pin = A1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  // initial check

  int initial_start_pin_state = digitalRead(start_pin);
  int initial_kill_pin_state = digitalRead(kill_pin);
  // int current_start_pin_state = 0;

  if (initial_start_pin_state == 1) {

    // error, the start pin should be 0 when you power your robot

    // if start pin state was “1” at the initial check you have to ask the referee to press the

    // stop button and then power off and on your robot

    while (true) {

      // for safety reasons the robot is locked in this loop

      // you can flash a separate LED to let the user know

      // the only way to exit this loop is to do a power cycle
    }
  } else if (initial_start_pin_state == 0) {

    // correct state

    // the robot is ready to accept the start command

    robot_ready_state = true;
  }
  current_start_pin_state = 0;
  current_stop_pin_state = 0;

  while (current_start_pin_state == 0) {

    // keep the robot locked in a loop until the start command

    // is received

    current_start_pin_state = digitalRead(start_pin);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if (current_start_pin_state == 1 && robot_ready_state == true) {

    // the start command was received and the robot was in a ready state

    // this is where the robot will start to compete against the opponent

    // the if condition will not execute unless the robot is in a ready state.

    while (current_start_pin_state == 1) {

      // keep the robot locked in a loop until the stop command is received

      Serial.print("Este pronit");
      current_start_pin_state = digitalRead(start_pin);
      current_stop_pin_state = digitalRead(kill_pin);
    }

    // the program will continue only if the stop command is received

    if (current_start_pin_state == 0 || current_stop_pin_state == 1) {

      // the stop command was received

      // this is where the robot should stop all operations

      while(true){
        
      }
      // if (digitalRead(kill_pin)) {

      //   Serial.print("Se oprit");
      //   // current_kill_pin_state = digitalRead(kill_pin);
      //   // Serial.print(current_kill_pin_state);
      //   // for safety reasons the robot is locked in this loop

      //   // you can flash a separate LED to let the user know

      //   // the only way to exit this loop is to do a power cycle
      // }
    }
  }
}
