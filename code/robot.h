#ifndef robot_h
#define robot_h

// enum Direction {
//   NONE = -1,
//   FORWARD = 0,
//   BACLWARD = 1,
//   LEFT = 2,
//   RIGHT = 3,
// }
#include <functional>

// MOTOR CLASS
class Motor
{
public:
  Motor(int backwardPin = -1, int forwardPin = -1);
  void stop();
  void forward(int speed);
  void backward(int speed);

private:
  int forwardPin;
  int backwardPin;
};

// INSTRUCTION CLASS
class Instruction
{
public:
  Instruction(std::function<void(float, int)> func, int arg, float seconds);
  void run();
  int getTime();

private:
  std::function<void(float, int)> func;
  int arg;
  float seconds;
}

// ROBOT CLASS
class Robot
{
public:
  Robot();
  Robot(int rmfp, int rmbp, int lmfp, int lmbp);
  void forward(float seconds, int speed);
  void backward(float seconds, int speed);
  void right(float seconds, int speed);
  void left(float seconds, int speed);
  void stop();
  void simpleAccel(float seconds, int setpoint);
  void updateAccel(double currSeconds);
  void addInstruction(function<void(float, int)> func, int arg, float seconds);

private:
  Motor rightMotor;
  Motor leftMotor;
  Instruction instructions[10];
  double funcStartTime = 0;
  double funcTime = 0;
  int setpoint = 0;
  bool accelerate = false;
  int instructIndex = 0;
  // enum Direction currDir = NONE;
};

// ABSTRACT ROBOT CLASS
class AbstractRobot // what CCCC will interact with
{
public:
  AbstractRobot();
  void forward(float seconds, int speed);
  void backward(float seconds, int speed);
  void right(float seconds, int speed);
  void left(float seconds, int speed);
  void stop();
  void simpleAccel(float seconds, int setpoint);

  priavte : Robot robot;
}

#endif