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

double Robot::getSonicDist(){ // Contains code from the big DJ Orser

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

  // Remeber using for loops? This is that except the loop never stops
  // If we want any kind of real time data reading (which we will), a loop is the best option

  // With this challenge, the methods you may have used before work differently, some have been removed, and one has been added
  // The new method getSonicDist() has become available (You can see the definition above this function)
  // This method will return a distance in cm the ultra sonic sensor on the robot is from and object, in our case a wall
  
  // TODO: block out wall follower
  //  - Use trig to move towards a wall then follow it?
  //    - Do middle schoolers understand trig? 😭
  //    - Is the sonic sensor acurate at angles?
  //  - Maybe it can follow a box around, like if distance becomes greater than x, turn 90 degree right and continue forward till we read a wall
  //    - It would only work going one direction around the box
  //  - If we had 2 we could use above concept to a maze follower (provided it only contained 90 turns)
  //    - Kinda complicated 

  // This makes accelerate work
  if (isAccelerating)
  {
    updateAccel(millis());
  }

  getSonicDist();
  delay(500)
}


