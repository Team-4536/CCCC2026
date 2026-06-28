#include "list"
#include "robot.hpp"
#include "arduino.h"

void turn180();
AbstractRobot robot;

// Your number from level 3 here:
const float unnamedVar;

void fakeMain()
{
  // Let's turn around 180 degrees!

  // You'll need the number you found from the previous level
  //    - Practice writing your own variable name!

  // To make the robot turn around 180 degrees we have a few options
  //  - We could try calling the right or left method and double the time we put int
  //    - Something like robot.right(yourVar * 2, 255);
  //  - OR we could call the right or left method twice

  // Lets do the second option with some modification
  // Calling a method twice should work, but repeating it is totally way to much work
  //  - Actually though, repeating lines in a big sytem can crowd and complicate code

  // So lets make your very own function!

  // Instructions:
  // 1. Navigate a few lines down to find Definiton of the turn180() function
  // 2. In the function, write code to turn the robot 180 degrees by calling right or left twice
  // 3. Use your new function below in to move forward, turn around, and move forward
  //  - Fun fact: You are writing code in fakeMain() which is also a function! (Function Inception if you will)
  
}

void turn180(){

};

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
  robot.robot.setInstructIndex(0);
  
}

void loop()
{
  robot.robot.update();
}
