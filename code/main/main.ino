#include "list"
#include "robot.hpp"
#include "arduino.h"

void turn180();
void turn360();
void spinAround(int n);
AbstractRobot robot;

// Your number from level 3 here:
const float TURN_90;

void fakeMain()
{
  
  // Lets make the robot spin, but cooler 😎

  // You'll need the number from level 3 for the variable at the top

  // Custom functions and for loops have made your code super, but we can go even further beyond
  // I'm confident you could make the robot spin around any number of times using a for loop
  // but what if I wanted you to sping the robot around 5 times, and then move forward, and right after spin 7 times?
  // You could just right another for loop for it, but it becomes a bit of a hassle after awhile, so lets fix that

  // We are going to make a function that takes an Argument, in this case, the number of times we want out loop to run
  // If you remeber the for loop structure, the loop runs the amount of times the number we compare i to is
  //  - If we want to loop 5 times, we set the condition to i < 5
  // This is super convenient because we can sub in the 5 for any number we want and the loop will run that many times

  // Nows a good time to learn more about arguments and parameters, you'll use one when making the spinAround() function

  // Instructions: 
  //  1. Write code in the spinAround() function to make the robot turn 360 degrees, n amount of times
  //  2. Use the spinAround() function you made to make the robot spin around 5 times, move forward, and then spin around 7 times

}

void spinAround(int n){

  // Write a loop utilizng n

}

void turn360(){
  turn180();
  turn180();
}

void turn180(){
  robot.right(TURN_90, 255);
  robot.right(TURN_90, 255);
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
