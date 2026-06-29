#include "list"
#include "robot.hpp"
#include "arduino.h"

Robot robot;

const int right_enable_pin = 6;
const int right_dir_pin = 7;
const int left_enable_pin = 8;
const int left_dir_pin = 9;
const int ECHO_PIN = -1;
const int TRIGGER_PIN = -1;
const uint LED_Pin = 27;

void setup()
{
  pinMode(right_enable_pin, OUTPUT);
  pinMode(right_dir_pin, OUTPUT);
  pinMode(left_enable_pin, OUTPUT);
  pinMode(left_dir_pin, OUTPUT);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_Pin, OUTPUT);
  robot = Robot(right_enable_pin, right_dir_pin, left_enable_pin, left_dir_pin, ECHO_PIN, TRIGGER_PIN);
  
}

void loop()
{
  // For this project, we will be working inside of robot.update() mainly
  robot.update();
}
