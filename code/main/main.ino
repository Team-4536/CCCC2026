#include "list"
#include "robot.hpp"
#include "arduino.h"

void forward(float seconds, int speed);

void fakeMain()
{
  // Lets move the robot forward!

  // Lets learn what a function is
  //  - This includes learning about fucntion parameters / arguments
  
  // Instructions: Call the Function "forward"
  // Specify a time for how long to run the robot for and how fast the robot should go

}

// Dont worry about this stuff for now :D

AbstractRobot robot;

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

void forward(float seconds, int speed){
  robot.forward(seconds, speed);
}