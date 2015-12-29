#include <Servo.h>
#include "intro.h"
#include "movement.h"
// Mega Biped Project by Ryan Matthews: ryan@megamatthews.com
// 2 leg 4 servo unit framed with 19 3D printed modular I braces and Arduino 
//Uno protection box: http://www.instructables.com/id/Arduino-Protection-Box/
// Begin Arduino 1.0 IDE sketch:

String command = "";
void run_command(String command, void (*)());

void setup()
{
  attach_servos();

  Serial.begin(9600); //115200 for bluetooth / 9600 for USB
  //Display serial menu to user:
  Serial.write(WELCOME_TEXT);
}

// Setup multiple serial character support
void check_for_input() {
  while (Serial.available() > 0) {
    char inChar = Serial.read();
    command += inChar;
  }
}
///////////////////////////////////////////////


void announce(String announce) {
  print_string_object(announce);
  Serial.write("\n");
}

void run_command(String command, void (*command_function)()) {
  announce(command);
  (*command_function)();
  announce("end" + command);
}

void write_angle(String angle) {
  announce("moving to " + angle);
}

void loop() {
  // Test commands:
  check_for_input();
  if (command.equals("")) {
    announce(F("no command seen, sleeping for 1 second"));
    delay(1000 * 1);
  } else if (command.equals("C")) {
    run_command(F("Center stance"), center_stance);
  } else if (command.equals("brf")) {
    center_stance();
    run_command(F("Balance on right foot"), balance_on_right_foot);
  } else if (command.equals("blf")) {
    center_stance();
    run_command(F("Balance on left foot"), balance_on_left_foot);
  } else if (command.equals("U")) {
    run_command(F("Stepping forward"), step_forward);
  } else if (command.equals("D")) {
    run_command(F("Stepping backward"), step_backward);
  } else if (command.equals("L")) {
    run_command(F("Turning Left"), turn_left);
  } else if (command.equals("R")) {
    run_command(F("Turning right"), turn_right);
  } else if (command.startsWith(F("left_hip."))) {
    announce(F("left_hip."));
    command.remove(0, 9);
    write_angle( command );
    move_left_hip(command.toInt());
  } else if (command.startsWith(F("right_hip."))) {
    announce(F("right_hip."));
    command.remove(0, 10);
    write_angle(command);
    move_right_hip(command.toInt());
  } else if (command.startsWith(F("left_ankle."))) {
    announce(F("left_ankle."));
    command.remove(0, 11);
    move_left_ankle(command.toInt());
    move_left_ankle(command.toInt());
  } else if (command.startsWith(F("right_ankle."))) {
    announce(F("right_ankle."));
    command.remove(0, 12);
    write_angle(command);
    move_right_ankle(command.toInt());
  } else { 
    Serial.write("the command[");
    print_string_object(command);
    announce(F("]didn't seem to match"));
    announce(F("resetting command"));
    command = "";
  }
  command = "";
  // End serial commands allowing individual joint manipulation*
}

void print_string_object(String print_me) {
  char* buf = (char*) malloc(sizeof(char) * print_me.length() + 1);
  print_me.toCharArray(buf, print_me.length() + 1);
  Serial.println(buf);
  free(buf);
}
