#include "list"
#include "robot.hpp"
#include "arduino.h"

AbstractRobot robot;

void fakeMain()
{
  // Lets make the robt accelerate!

  // You should have a basic understanding of what a function does, lets take it a step further

  // First, you have to learn what an object is
  //  - This includes learning about Classes
  // Use what you've learned about functions and notice the similarities in how to call methods

  // Instructions: Call the Method "accelerate" on the robot
  // then Call the now Method "forward" on the robot
  // try to figure out what arguments you have to give to the Methods
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
  robot.robot.setInstructIndex(0);
}

void loop()
{
  robot.robot.update();
}
