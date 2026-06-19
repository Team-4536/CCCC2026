#include <functional>
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

Instruction::Instruction(std::function<void(int)> func, int arg, float seconds)
{
  this->argFunc = func;
  this->arg = arg;
  this->seconds = seconds;
}

Instruction::Instruction(std::function<void()> func, float seconds)
{
  this->voidFunc = func;
  this->seconds = seconds;
}

void Instruction::run()
{
  if(arg == -1){
    this->voidFunc;
    return;
  }

  this->argFunc(arg);
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

void Robot::addInstruction(std::function<void(int)> func, int arg, float seconds)
{
  instructions[instructIndex] = Instruction(func, arg, seconds);
}

void Robot::addInstruction(std::function<void()> func, float seconds)
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
    instructions[instructIndex].run();
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
  digitalWrite(27, LOW);
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

// Connor's stuff is below 

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
}

void Robot::update()
{
  if(!funcRan){
    nextInstruction();
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
  robot.addInstruction(std::bind(&Robot::forward, robot, std::placeholders::_1), speed, seconds);
}

void AbstractRobot::backward(float seconds, int speed)
{
  robot.addInstruction(std::bind(&Robot::backward, robot, std::placeholders::_1), speed, seconds);
}

void AbstractRobot::right(float seconds, int speed)
{
  robot.addInstruction(std::bind(&Robot::right, robot, std::placeholders::_1), speed, seconds);
}

void AbstractRobot::left(float seconds, int speed)
{
  robot.addInstruction(std::bind(&Robot::left, robot, std::placeholders::_1), speed, seconds);
}

void AbstractRobot::stop()
{
  robot.addInstruction(std::bind(&Robot::stop, robot));
}

void AbstractRobot::simpleAccel(float seconds, int setpoint)
{
  robot.addInstruction(std::bind(&Robot::simpleAccel, robot, std::placeholders::_1), setpoint, seconds);
}
