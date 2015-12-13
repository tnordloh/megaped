#include "arduino.h"


Servo left_hip; // create servo object to control left hip
Servo left_ankle; // create servo object to control left ankle
Servo right_hip; // create servo object to control right hip
Servo right_ankle; // create servo object to control right ankle


void center_stance() {
  left_hip.write(90);
  left_ankle.write(90);
  right_hip.write(90);
  right_ankle.write(90);
}

void attach_servos() {
  left_hip.attach(2); // attaches left hip servo to digital pin 2
  left_ankle.attach(3); // attaches left ankle servo to digital pin 3
  right_hip.attach(4); // attaches right hip servo to digital pin 4
  right_ankle.attach(5); // attaches right ankle servo to digital pin 5
}

void move_joint(Servo joint, int position) {
  joint.write(position);
}

void increment_joint(Servo joint, int start, int finish) {
  for (int i = start; i <= finish; i++) {
    move_joint(joint, i);
    delay(40);
  }
}

void decrement_joint(Servo joint, int start, int finish) {
  for (int i = start; i >= finish; --i) {
    move_joint(joint, i);
    delay(40);
  }
}

void balance_on_right_foot() {
  delay(800); //entry pause for next step
  left_ankle.write(5); //pitch left ankle to the right boosting lean
  delay(400);
  right_ankle.write(55); //pitch right ankle to the right - now your propped on right ankle balanced
}

void balance_on_left_foot() {
  delay(800); //entry pause for next step
  right_ankle.write(175); //pitch right ankle to the left boosting lean
  delay(400);
  left_ankle.write(130); //pitch left ankle to the left - now your propped on left ankle balanced1
}

void step_forward() {
  center_stance();
  balance_on_right_foot();
  delay(400);
  left_hip.write(90); //reset left hip (incase we had previously stepped with it)
  left_ankle.write(60); //slow return of left ankle
  delay(400);
  left_ankle.write(90); //full reset of left ankle
  delay(400);
  increment_joint(right_hip, 95, 105);
  right_hip.write(112); //rotate right hip and make left foot step forward
  delay(200);
  increment_joint(right_ankle, 65, 90);
  delay(800); //exit pause for next step
  center_stance(); //full joint reset:
  // Take right step forward:
  balance_on_left_foot();
  delay(400);
  right_hip.write(90); //reset right hip (incase we had previously stepped with it)
  right_ankle.write(120); //slow return of right ankle
  delay(400);
  right_ankle.write(90); //full reset of right ankle
  delay(400);
  decrement_joint(right_ankle, 85, 70);
  left_hip.write(67); //rotate left hip and make right foot step forward
  delay(200);
  decrement_joint(left_ankle, 115, 90);
  delay(800); //exit pause for next step
  center_stance(); //full joint reset:

}

void step_backward() {
  Serial.write("Stepping Backwards!\n");
  center_stance();
  delay(800); //entry pause for next step
  balance_on_right_foot();
  delay(400);
  left_hip.write(90); //reset left hip (incase we had previously stepped with it)
  left_ankle.write(60); //slow return of left ankle
  delay(400);
  left_ankle.write(90); //full reset of left ankle
  delay(400);
  decrement_joint(right_hip, 85, 70);
  right_hip.write(67); //rotate right hip and make left foot step forward
  delay(200);
  increment_joint(right_ankle, 65, 90);
  delay(800); //exit pause for next step
  center_stance(); //full joint reset:
  /////////////////////////////
  // Take right step backwards:
  balance_on_left_foot();
  delay(400);
  right_hip.write(90); //reset right hip (incase we had previously stepped with it)
  right_ankle.write(120); //slow return of right ankle
  delay(400);
  right_ankle.write(90); //full reset of right ankle
  delay(400);
  increment_joint(left_hip, 95, 112);
  delay(200);
  decrement_joint(left_ankle, 115, 90);
  delay(800); //exit pause for next step
  center_stance();
}

void turn_left() {
  center_stance();
  balance_on_right_foot();
  delay(400);
  right_ankle.write(55); //pitch right ankle to the right - now your propped on right ankle balanced
  delay(400);
  left_hip.write(90); //reset left hip (incase we had previously stepped with it)
  left_ankle.write(60); //slow return of left ankle
  delay(400);
  left_ankle.write(90); //full reset of left ankle
  delay(400);
  increment_joint(right_hip, 90, 112);
  increment_joint(right_ankle, 55, 90);
  delay(800); //exit pause for next step
  right_hip.write(90); //reset right hip
  delay(800); //entry pause for next step
  left_ankle.write(5); //pitch left ankle to the right boosting lean
  delay(400);
  right_ankle.write(55); //pitch right ankle to the right - now your propped on right ankle balanced
  delay(400);
  left_hip.write(90); //reset left hip (incase we had previously stepped with it)
  left_ankle.write(60); //slow return of left ankle
  delay(400);
  left_ankle.write(90); //full reset of left ankle
  delay(400);
  increment_joint(right_hip, 90, 112);
  delay(200);
  increment_joint(right_ankle, 55, 90);
  right_hip.write(90); //reset right hip
  delay(800); //exit pause for next step
  center_stance();
}

void turn_right() {
  Serial.write("Turning Right!\n");
  balance_on_right_foot();
  delay(400);
  right_hip.write(90); //reset right hip (incase we had previously stepped with it)
  right_ankle.write(120); //slow return of right ankle
  delay(400);
  right_ankle.write(90); //full reset of right ankle
  delay(400);
  decrement_joint(left_hip, 90, 67);
  delay(200);
  decrement_joint(left_ankle, 115, 90);
  //pass weight back to right foot - completed step
  delay(800); //exit pause for next step
  center_stance();
  balance_on_right_foot();
  delay(400);
  right_hip.write(90); //reset right hip (incase we had previously stepped with it)
  right_ankle.write(120); //slow return of right ankle
  delay(400);
  decrement_joint(right_ankle, 90, 67);
  delay(200);
  decrement_joint(left_ankle, 115, 90);
  delay(800); //exit pause for next step
  center_stance();
}
