#include "list"
#include "robot.hpp"
#include "arduino.h"

AbstractRobot robot;

// Store your number from step 4 in the variable here, 
// Using the equals sign "=" and then your number:
const float TURN_90;

void fakeMain()
{
  // Lets turn the robot 90 degrees!

  // Feel free at this point to explore the different Methods the robot has
  // These include:
  //  - backward
  //  - right
  //  - left
  //  - stop

  // The Right and Left Methods are kind of inconvenient because they turn based on seconds
  // How are we supposed to know what amount of time will turn 90 degrees?
  // This also makes some inconsistencies:
  // Given the same amount of time, turning at full speed will have a different effect than turning at a slower speed

  // Instructions:
  // 1. Try turning the robot with the right or left methods and pick a random time
  //    - Keep the speed at full for now (255)
  // 2. Run the code on the robot and see how far the robot turns
  // 3. Keep tuning the time you put in to be close to a 90 degree turn
  // 4. Store the time you find best in the varibale at the top
  //    - A good time to learn about Constants and naming conventions like camelCase and snake_case
  // 5. Write code that will move the robot forward, turn left 90 degrees, forward again, and then right 90 degrees
  //    - Use your Variable!
  
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
  robot.robot.setInstructIndex(0);
  
}

void loop()
{
  robot.robot.update();
}
