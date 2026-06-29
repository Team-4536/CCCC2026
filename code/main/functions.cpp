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

// INSTRUCTION CLASS
Instruction::Instruction()
{
  std::cout << "NOOOO" << std::endl;
}

Instruction::Instruction(Instruct func, int arg, float seconds)
{
  this->func = func;
  this->arg = arg;
  this->seconds = seconds;
}

Instruction::Instruction(Instruct func, float seconds)
{
  this->func = func;
  this->seconds = seconds;
}

void Robot::runInstruction(Instruction &instruction)
{

  Instruct func = instruction.func;

  int arg = instruction.arg;

  switch (func)
  {
  case FORWARD:
    forward(arg);
    break;
  case BACKWARD:
    backward(arg);
    break;
  case LEFT:
    left(arg);
    break;
  case RIGHT:
    right(arg);
    break;
  case ACCELERATE:
    accelerate(arg);
    break;
  case STOP:
      stop();
      break;
  case WAIT:
    break;
  default:
    Serial.print("Switch is buns");
  }
}

float Instruction::getTime() // return the time in milliseconds
{
  return seconds * 1000; // convert to milliseconds because milis()
}

// ROBOT CLASS
Robot::Robot()
{
}

Robot::Robot(int rmep, int rmdp, int lmep, int lmdp)
{
  rightMotor = Motor(rmep, rmdp);
  leftMotor = Motor(lmep, lmdp);
}

void Robot::setInstructIndex(int n)
{
  instructIndex = n;
}

void Robot::addInstruction(Instruct func, int arg, float seconds)
{
  if (numInstructs >= MAX_INSTRUCT)
  {
    Serial.print("MAX Instructions reached");
    return;
  }
  instructions[instructIndex] = Instruction(func, arg, seconds);
  instructIndex++;
  numInstructs++;
}

void Robot::addInstruction(Instruct func, float seconds)
{
  if (numInstructs >= MAX_INSTRUCT)
  {
    Serial.print("MAX Instructions reached");
    return;
  }
  instructions[instructIndex] = Instruction(func, seconds);
  instructIndex++;
  numInstructs++;
}

void Robot::nextInstruction() // reset and run the next instruction
{
  if (instructIndex < numInstructs)
  {
    isAccelerating = false;
    runInstruction(instructions[instructIndex]);
    currFunc = instructions[instructIndex].func;
    funcStartTime = millis();
    funcTime = instructions[instructIndex].getTime();
    instructIndex++;
    funcRan = true;
  }
  else
  {
    stop();
  }
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
  if(mult > 1){ mult = 1;}
  currSpeed = setpoint * mult;
  forward(currSpeed);
}

void Robot::update()
{
  if (!funcRan)
  { // this and next if statement make a toggle
    nextInstruction();
  }

  if (funcRan)
  {
    if (millis() - funcStartTime >= funcTime)
    {
      funcRan = false;
      digitalWrite(27, LOW);
    }
  }

  if (isAccelerating)
  {
    updateAccel(millis());
  }
}

// ABSTRACT ROBOT CLASS

AbstractRobot::AbstractRobot()
{
  robot = Robot();
}
AbstractRobot::AbstractRobot(int rmep, int rmdp, int lmep, int lmdp)
{
  robot = Robot(rmep, rmdp, lmep, lmdp);
}

void AbstractRobot::forward(float seconds, int speed)
{
  robot.addInstruction(Instruct::FORWARD, speed, seconds);
}

void AbstractRobot::backward(float seconds, int speed)
{
  robot.addInstruction(Instruct::BACKWARD, speed, seconds);
}

void AbstractRobot::right(float seconds, int speed)
{
  robot.addInstruction(Instruct::RIGHT, speed, seconds);
}

void AbstractRobot::left(float seconds, int speed)
{
  robot.addInstruction(Instruct::LEFT, speed, seconds);
}

void AbstractRobot::stop()
{
  robot.addInstruction(Instruct::STOP);
}

void AbstractRobot::accelerate(float seconds, int setpoint)
{
  robot.addInstruction(Instruct::ACCELERATE, setpoint, seconds);
}

void AbstractRobot::wait(float seconds)
{
  robot.addInstruction(Instruct::WAIT, seconds);
}
