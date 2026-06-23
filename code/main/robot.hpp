#ifndef robot_h
#define robot_h

class Motor;
class Robot;
class AbstractRobot;
class Instruction;

enum Instruct
{
  STOP,
  WAIT,
  FORWARD,
  BACKWARD,
  LEFT,
  RIGHT,
  ACCELERATE,
};

// MOTOR CLASS
class Motor
{
public:
  Motor(int enablePin = -1, int dirPin = -1);
  void stop();
  void forward(int speed);
  void backward(int speed);

private:
  int dirPin;
  int enablePin;
};

// INSTRUCTION CLASS
class Instruction
{
public:
  Instruct func;
  int arg = -1;
  float seconds = 0;

  Instruction();
  Instruction(Instruct func, int arg, float seconds);
  Instruction(Instruct func, float seconds = 0);
  float getTime();

private:
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
  void accelerate(int setpoint);
  void updateAccel(double currSeconds);
  void addInstruction(Instruct func, int arg, float seconds);
  void addInstruction(Instruct func, float seconds = -1); // mainly for stop and wait
  void nextInstruction();
  void runInstruction(Instruction &instruction);
  void update();
  void setInstructIndex(int n);

private:
  Motor rightMotor;
  Motor leftMotor;
  static const int MAX_INSTRUCT = 10;
  Instruction instructions[MAX_INSTRUCT];
  double funcStartTime = 0;
  double funcTime = 0;
  int setpoint = 0;
  int currSpeed = 0;
  bool isAccelerating = false;
  int instructIndex = 0;
  int numInstructs = 0;
  bool funcRan = false;
  Instruct currFunc;
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
  void wait(float seconds);
  void accelerate(float seconds, int setpoint);
};

#endif