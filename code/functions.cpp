#include <functional>
#include "robot.h"
#include "arduino.h"

Motor::Motor(int forwardPin = -1, int backwardPin = -1)
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

Instruction::Instruction(function<void(float, int)> func, int arg, float seconds)
{
  this->func = func;
  this->arg = arg;
  this->seconds = seconds;
}

void Instruction::run()
{
  func(arg);
}

float Instruction::getTime()
{
  return seconds;
}

Robot::Robot()
{
}

Robot::Robot(int rmfp, int rmbp, int lmfp, int lmbp)
{
  rightMotor = Motor(rmfp, rmbp);
  leftMotor = Motor(lmfp, lmbp);
}

void addInstruction(function<void(float, int)> func, int arg, float seconds)
{
  instructions[instructIndex] = Instruction(func, arg, seconds);
}

void Robot::forward(float seconds, int speed)
{
  rightMotor.forward(speed);
  leftMotor.forward(speed);
  digitalWrite(27, HIGH);
  delay(1000 * seconds);
  digitalWrite(27, LOW);
}

void Robot::backward(float seconds, int speed)
{
  rightMotor.backward(speed);
  leftMotor.backward(speed);
  delay(1000 * seconds);
}

void Robot::right(float seconds, int speed)
{
  rightMotor.forward(speed);
  leftMotor.stop();

  digitalWrite(27, HIGH);
  delay(1000 * seconds);
  digitalWrite(27, LOW);
}

void Robot::left(float seconds, int speed)
{
  rightMotor.stop();
  leftMotor.forward(speed);
  delay(1000 * seconds);
}

// Connor's stuff is below

void Robot::stop()
{
  rightMotor.stop();
  leftMotor.stop();
}

void Robot::simpleAccel(float seconds, int setpoint)
{
  accelStartTime = startTime;
  accelTime = seconds;
  this->setpoint = setpoint;
}

void Robot::updateAccel(double currSeconds)
{
  double mult = (currSeconds - accelStartTime) / accelTime;
  // speed = setpoint * mult;
}

void Robot::update()
{
}

AbstractRobot::AbstractRobot()
{
  robot = Robot();
}

void AbstractRobot::forward(float seconds, int speed)
{
  robot.addInstruction(robot.forward, speed, seconds);
}

void AbstractRobot::backward(float seconds, int speed)
{
  robot.addInstruction(robot.backward, speed, seconds);
}

void AbstractRobot::right(float seconds, int speed)
{
  robot.addInstruction(robot.right, speed, seconds);
}

void AbstractRobot::left(float seconds, int speed)
{
  robot.addInstruction(robot.left, speed, seconds);
}

// Connor's stuff is below

void AbstractRobot::stop()
{
  robot.addInstruction(robot.stop, speed, seconds);
}

void AbstractRobot::simpleAccel(float seconds, int setpoint)
{
  robot.addInstruction(robot.simpleAccel, speed, seconds);
}
