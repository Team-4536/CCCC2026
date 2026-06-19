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
  Instruction();
  Instruction(std::function<void()> func, float seconds = -1);
  Instruction(std::function<void(int)> func, int arg, float seconds);
  void run();
  float getTime();

private:
  std::function<void(int)> argFunc;
  std::function<void()> voidFunc;
  int arg = -1;
  float seconds = -1;
};

// ROBOT CLASS
class Robot
{
public:
  Robot();
  Robot(int rmfp, int rmbp, int lmfp, int lmbp);
  void forward(int speed);
  void backward(int speed);
  void right(int speed);
  void left(int speed);
  void stop();
  void simpleAccel(int setpoint);
  void updateAccel(double currSeconds);
  void addInstruction(std::function<void(int)> func, int arg, float seconds);
  void addInstruction(std::function<void()> func, float seconds = -1);
  void nextInstruction();
  void update();

private:
  Motor rightMotor;
  Motor leftMotor;
  static const int MAX_INSTRUCT = 10;
  Instruction instructions[MAX_INSTRUCT];
  double funcStartTime = 0;
  double funcTime = 0;
  int setpoint = 0;
  int currSpeed = 0;
  bool accelerate = false;
  int instructIndex = 0;
  int numInstructs = 0;
  bool funcRan = false;
  // enum Direction currDir = NONE;
};

// ABSTRACT ROBOT CLASS
class AbstractRobot // what CCCC will interact with
{
public:
  Robot robot;

  AbstractRobot();
  AbstractRobot(int rmfp, int rmbp, int lmfp, int lmbp);
  void forward(float seconds, int speed);
  void backward(float seconds, int speed);
  void right(float seconds, int speed);
  void left(float seconds, int speed);
  void stop();
  void simpleAccel(float seconds, int setpoint);
    
};

#endif