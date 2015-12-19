#include "arduino.h"


Servo left_hip; // create servo object to control left hip
Servo left_ankle; // create servo object to control left ankle
Servo right_hip; // create servo object to control right hip
Servo right_ankle; // create servo object to control right ankle
int cur_pos_right_ankle = 90;
int cur_pos_left_ankle  = 90;
int cur_pos_right_hip   = 90;
int cur_pos_left_hip    = 90;


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

void move_right_hip(int position) {
  if (position > cur_pos_right_hip) {
    increment_joint(right_hip, cur_pos_right_hip, position);
  } else {
    decrement_joint(right_hip, cur_pos_right_hip, position);
  }
  cur_pos_right_hip = position;
}

void move_left_hip(int position) {
  if (position > cur_pos_left_hip) {
    increment_joint(left_hip, cur_pos_left_hip, position);
  } else {
    decrement_joint(left_hip, cur_pos_left_hip, position);
  }
  cur_pos_left_hip = position;
}

void move_left_ankle(int position) {
  if (position > cur_pos_left_ankle) {
    increment_joint(left_ankle, cur_pos_left_ankle, position);
  } else {
    decrement_joint(left_ankle, cur_pos_left_ankle, position);
  }
  cur_pos_left_ankle = position;
}

void move_right_ankle(int position) {
  if (position > cur_pos_right_ankle) {
    increment_joint(right_ankle, cur_pos_right_ankle, position);
  } else {
    decrement_joint(right_ankle, cur_pos_right_ankle, position);
  }
  cur_pos_right_ankle = position;
}

void center_stance() {
  move_left_hip(90);
  move_left_ankle(90);
  move_right_hip(90);
  move_right_ankle(90);
}

void balance_on_right_foot() {
  delay(800); //entry pause for next step
  //move_left_ankle(5); //pitch left ankle to the right boosting lean
  move_left_ankle(60);
  delay(400);
  move_right_ankle(85);
  move_left_ankle(30);
  move_right_ankle(75);
  move_left_ankle(15);
  move_right_ankle(60);

  //move_right_ankle(65); //pitch right ankle to the right - now your propped on right ankle balanced
}

void balance_on_left_foot() {
  delay(800); //entry pause for next step
  //move_right_ankle(175); //pitch right ankle to the left boosting lean
  move_right_ankle(120);
  delay(400);
  //move_left_ankle(115); //pitch left ankle to the left - now your propped on left ankle balanced1
  move_left_ankle(95);
  move_right_ankle(150);
  move_left_ankle(105);
  move_right_ankle(160);
  move_left_ankle(123);

}

void step_forward() {
  center_stance();
  balance_on_right_foot();
  delay(400);
  move_left_hip(90); //reset left hip (incase we had previously stepped with it)
  move_left_ankle(60); //slow return of left ankle
  delay(400);
  move_left_ankle(90); //full reset of left ankle
  delay(400);

  move_right_hip(112); //rotate right hip and make left foot step forward
  delay(200);
  move_right_ankle(90);
  delay(800); //exit pause for next step
  center_stance(); //full joint reset:

  // Take right step forward:
  balance_on_left_foot();
  delay(400);
  move_right_ankle(90);
  move_left_hip(67); //rotate left hip and make right foot step forward
  delay(200);
  move_left_ankle(90);
  delay(800); //exit pause for next step
  center_stance(); //full joint reset:


}

void step_backward() {
  center_stance();
  
  delay(800); //entry pause for next step
  balance_on_right_foot();
  delay(400);
  move_left_ankle(90);
  delay(400);
  move_right_hip(75);
  delay(200);
  move_right_ankle(90);
  delay(800); //exit pause for next step
  center_stance(); //full joint reset:
  /////////////////////////////
  // Take right step backwards:
  
  balance_on_left_foot();
  move_left_ankle(115);
  delay(400);
  move_right_ankle(90); //full reset of right ankle
  delay(400);
  move_left_hip(100);
  move_left_ankle(90);
  delay(800); //exit pause for next step
  center_stance();
}

void turn_left() {
  center_stance();
  for (int x = 0; x <= 2; x++) {
    balance_on_right_foot();
    delay(400);
    move_left_ankle(90); //full reset of left ankle
    delay(400);
    move_right_hip(112);
    move_right_ankle(90);
    center_stance();
  }
}

void turn_right() {
  for (int x = 0; x <= 2; x++) {
    balance_on_left_foot();
    delay(400);
    move_left_ankle(90); //full reset of right ankle
    delay(400);
    move_right_hip(68);
    move_left_ankle(90);
    center_stance();
  }
}
