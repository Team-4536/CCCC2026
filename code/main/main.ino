#include "list"
#include "robot.hpp"
#include "arduino.h"

AbstractRobot robot;

void fakeMain()
{
  // put your main code here, instructions for the robot:
  // functions:
  // 1. forward : takes a time in seconds and a speed
  // 2. backward : takes a time in seconds and a speed
  // 3. right : takes a time in seconds and a speed
  // 4. left : takes a time in seconds and a speed
  // 5. stop : takes no arguments
  // 6. accelerate : takes a time in seconds and a speed to accelerate to
  robot.accelerate(5, 255);
  robot.forward(5, 255);
  robot.stop();
  robot.wait(3);
  robot.backward(5, 255);
  robot.right(2, 255);
  robot.left(2, 255);
  robot.robot.setInstructIndex(0);
}

const int right_enable_pin = 6;
const int right_dir_pin = 7;
const int left_enable_pin = 8;
const int left_dir_pin = 9;
const uint LED_Pin = 27;

void setup()
{
  pinMode(right_enable_pin, OUTPUT);
  pinMode(right_dir_pin, OUTPUT);
  pinMode(left_enable_pin, OUTPUT);
  pinMode(left_dir_pin, OUTPUT);
  pinMode(LED_Pin, OUTPUT);
  robot = AbstractRobot(right_enable_pin, right_dir_pin, left_enable_pin, left_dir_pin);
  fakeMain();
  
}

void loop()
{
  robot.robot.update();
}
