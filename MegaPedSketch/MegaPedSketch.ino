#include <Servo.h>
#include "intro.h"
#include "movement.h"
// Mega Biped Project by Ryan Matthews: ryan@megamatthews.com
// 2 leg 4 servo unit framed with 19 3D printed modular I braces and Arduino Uno protection box: http://www.instructables.com/id/Arduino-Protection-Box/
// Begin Arduino 1.0 IDE sketch:

String command = "";
void run_command(String command, void (*)());
///////////////////////////////////////////////
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
    String command_name = "no command seen, sleeping for 10 seconds";
    announce(command_name);
    delay(1000 * 1);
  }
  else if (command.equals("C")) {
    run_command("Center stance", center_stance);
  }
  else if (command.equals("brf")) {
    center_stance();
    run_command("Balance on right foot", balance_on_right_foot);
  }
  else if (command.equals("blf")) {
    center_stance();
    run_command("Balance on left foot", balance_on_left_foot);
  }
  else if (command.equals("U")) {
    run_command("Stepping forward", step_forward);
  }
  else if (command.equals("D")) {
    run_command("Stepping backward", step_backward);
  }
  else if (command.equals("L")) {
    run_command("Turning Left", turn_left);
  }
  else if (command.equals("R")) {
    run_command("Turning right", turn_right);
  }
  else if (command.startsWith("left_hip."))
  {
    Serial.write("left_hip.\n");
    command.remove(0, 9);
    write_angle( command );
    left_hip.write(command.toInt());
  }
  else if (command.startsWith(RIGHT_HIP))
  {
    announce(RIGHT_HIP);
    Serial.write("size[");
    Serial.print(sizeof(RIGHT_HIP));
    Serial.write("]\n");
    command.remove(0, 10);
    write_angle(command);
    right_hip.write(command.toInt());
  }
  else if (command.startsWith("left_ankle."))
  {
    announce("left_ankle.");
    command.remove(0, 11);
    write_angle(command);
    left_ankle.write(command.toInt());
  }
  else if (command.startsWith("right_ankle."))
  {
    announce("right_ankle.");
    command.remove(0, 12);
    write_angle(command);
    right_ankle.write(command.toInt());
  }
  //// Left ankle direct commands:
  else {
    Serial.write("the command[");
    print_string_object(command);
    Serial.write("]didn't seem to match\n");
    Serial.write("resetting command\n");
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
