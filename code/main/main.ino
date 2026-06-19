#include "list"
#include "robot.hpp"

AbstractRobot robot;

void fakeMain(){
  // put your main code here, to run repeatedly:
  // functions:
  // 1. forward
  // 2. backward
  // 3. right
  // 4. left
  // 5. stop

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

