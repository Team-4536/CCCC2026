#include "list"
#include "robot.hpp"

AbstractRobot robot;

void fakeMain(){
  // put your main code here, instructions for the robot:
  // functions:
  // 1. forward : takes a time in seconds and a speed
  // 2. backward : takes a time in seconds and a speed
  // 3. right : takes a time in seconds and a speed
  // 4. left : takes a time in seconds and a speed
  // 5. stop : takes no arguments
  // 6. accelerate : takes a time in seconds and a speed to accelerate to
  robot.accelerate(1, 255);
  robot.right(1, 255);
  robot.left(1, 255);
  robot.stop();
}

const int right_motor_1 = 6;
const int right_motor_2 = 7;
const int left_motor_1 = 8;
const int left_motor_2 = 9;
const uint LED_Pin = 27;

void setup()
{
  pinMode(right_motor_1, OUTPUT);
  pinMode(right_motor_2, OUTPUT);
  pinMode(left_motor_1, OUTPUT);
  pinMode(left_motor_2, OUTPUT);
  pinMode(LED_Pin, OUTPUT);
  robot = AbstractRobot(right_motor_1, right_motor_2, left_motor_1, left_motor_2);
  fakeMain();
}

void loop()
{
  robot.robot.update();
}

