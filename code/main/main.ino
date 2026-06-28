#include "list"
#include "robot.hpp"
#include "arduino.h"

AbstractRobot robot;

void fakeMain()
{
  // Lets move the robot forward!

  // First, you have to learn what an object is
  //  - This includes learning about Classes
  // Then, you have to learn what a function is and how to call methods
  //  - This includes learning about fucntion parameters / arguments
  
  // Instructions: Call the Method "forward" on the Robot
  // Specify a time for how long to run the robot for and how fast the robot should go

}

// Dont worry about this stuff for now :D

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
