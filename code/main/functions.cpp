#include <iostream>
#include "robot.hpp"
#include "arduino.h"

// MOTOR CLASS

Motor::Motor(int forwardPin, int backwardPin)
{
  this->backwardPin = backwardPin;
  this->forwardPin = forwardPin;
}

void Motor::stop()
{
  digitalWrite(forwardPin, LOW);
  analogWrite(backwardPin, 0);
}
void Motor::forward(int speed)
{
  digitalWrite(backwardPin, LOW);
  analogWrite(forwardPin, speed);
}
void Motor::backward(int speed)
{
  digitalWrite(forwardPin, LOW);
  analogWrite(backwardPin, speed);
}

// INSTRUCTION CLASS
Instruction::Instruction(){
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

void Robot::runInstruction(Instruction& instruction)
{
  Instruct func = instruction.func;

  if(instruction.arg == -1){ // room for more instructions with no args
    switch(func){
      case STOP:
        stop();
        break;
      case WAIT:
        break;
    }
    return;
  }

  int arg = instruction.arg;

  switch(func){
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
      simpleAccel(arg);
      break;
  }
}

float Instruction::getTime()
{
  return seconds;
}

// ROBOT CLASS
Robot::Robot()
{
}

Robot::Robot(int rmfp, int rmbp, int lmfp, int lmbp)
{
  rightMotor = Motor(rmfp, rmbp);
  leftMotor = Motor(lmfp, lmbp);
}

void Robot::addInstruction(Instruct func, int arg, float seconds)
{
  if(numInstructs >= MAX_INSTRUCT){
    return;
  }
  instructions[instructIndex] = Instruction(func, arg, seconds);
  instructIndex++;
}

void Robot::addInstruction(Instruct func, float seconds)
{
  if(numInstructs >= MAX_INSTRUCT){
    return;
  }
  instructions[instructIndex] = Instruction(func, seconds);
  numInstructs++;
}

void Robot::nextInstruction()
{
  if (instructIndex < numInstructs)
  {
    runInstruction(instructions[instructIndex]);
    currFunc = instructions[instructIndex].func;
    funcStartTime = millis();
    funcTime = instructions[instructIndex].getTime();
    instructIndex++;
    funcRan = true;
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

void Robot::simpleAccel(int setpoint)
{
  accelerate = true;
  this->setpoint = setpoint;
}

void Robot::updateAccel(double currSeconds)
{
  double mult = (currSeconds - funcStartTime) / funcTime;
  currSpeed = setpoint * mult;
  forward(currSpeed);
}

void Robot::update()
{
  if(!funcRan){ // this and next if statement make a toggle
    nextInstruction();
  }

  if(funcRan){
    if(millis() - funcStartTime >= funcTime){
      funcRan = false;
      digitalWrite(27, LOW);
    }
  }

  if(accelerate)
  {
    updateAccel(millis());
  }
}

// ABSTRACT ROBOT CLASS

AbstractRobot::AbstractRobot()
{
  robot = Robot();
}
AbstractRobot::AbstractRobot(int rmfp, int rmbp, int lmfp, int lmbp)
{
  robot = Robot(rmfp, rmbp, lmfp, lmbp);
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

void AbstractRobot::simpleAccel(float seconds, int setpoint)
{
  robot.addInstruction(Instruct::ACCELERATE, setpoint, seconds);
}
