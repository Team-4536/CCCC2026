#include <iostream>
#include "robot.hpp"
#include "arduino.h"

// MOTOR CLASS

Motor::Motor(int enablePin, int dirPin)
{
  this->enablePin = enablePin;
  this->dirPin = dirPin;
}

void Motor::stop()
{
  digitalWrite(dirPin, LOW);
  analogWrite(enablePin, 0);
}
void Motor::forward(int speed)
{
  digitalWrite(dirPin, HIGH);
  analogWrite(enablePin, speed);  
}
void Motor::backward(int speed)
{
  digitalWrite(dirPin, LOW);
  analogWrite(enablePin, speed);
}

// ROBOT CLASS
Robot::Robot()
{
}

Robot::Robot(int rmep, int rmdp, int lmep, int lmdp, int echo, int trigger)
{
  rightMotor = Motor(rmep, rmdp);
  leftMotor = Motor(lmep, lmdp);
  echoPin = echo;
  triggerPin = trigger;
}

void Robot::forward(int speed)
{
  rightMotor.forward(speed);
  leftMotor.forward(speed);
  digitalWrite(27, HIGH);
}

void Robot::backward(int speed)
{
  rightMotor.backward(speed);
  leftMotor.backward(speed);
}

void Robot::right(int speed)
{
  rightMotor.forward(speed);
  leftMotor.stop();
}

void Robot::left(int speed)
{
  rightMotor.stop();
  leftMotor.forward(speed);
}

// Connor's stuff is everywhere >:3

void Robot::stop()
{
  rightMotor.stop();
  leftMotor.stop();
}

void Robot::accelerate(int setpoint)
{
  isAccelerating = true;
  this->setpoint = setpoint;
}

void Robot::updateAccel(double currSeconds)
{
  double mult = (currSeconds - funcStartTime) / funcTime;
  if(mult > 1){ 
    mult = 1;
    isAccelerating - false;
  }
  currSpeed = setpoint * mult;
  forward(currSpeed);
}

double Robot::getSonicDist(){

  // Send a HIGH Pulse to triggerPin that is 10us Long
  digitalWrite(triggerPin, LOW); // Trigger should already be low, just in case
  delayMicroseconds(2); // This is just like delay() but in microseconds
  digitalWrite(triggerPin, HIGH); // set HIGH
  delayMicroseconds(10); // wait 10us
  digitalWrite(triggerPin, LOW); // set LOW

  double duration = pulseIn(echoPin, HIGH); // Measure pulse width on echoPin

  double distance = duration / 58.0; // Calc distance duration / speed_of_sound (cm/us)

  Serial.print(distance);
  Serial.println("cm");

  return distance;
}

void Robot::update()
{
  // Lets make a wall following robot!

  // This space is a bit different than what you've been working in so far
  // Most software systems can be boiled down into two main sections: A setup and a loop
  // You've been dealing with the setup section so far, essentially planning out what the robot does
  // However now you will be working inside of the loop where you will update the robot in real time

  // Remeber using for loops? This is essentielly that except the loop never stops
  // If we want any kind of real time data reading (which we will), a loop is the best option
  

  // This makes accelerate work
  if (isAccelerating)
  {
    updateAccel(millis());
  }
}


