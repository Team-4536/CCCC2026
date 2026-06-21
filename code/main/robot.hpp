#ifndef robot_h
#define robot_h

class Motor;
class Robot;
class AbstractRobot;
class Instruction;

enum Instruct {
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
  Instruct func;
  Instruction();
  Instruction(Instruct func, int arg, float seconds);
  Instruction(Instruct func, float seconds = 0);
  void run(Robot* robot);
  float getTime();

private:
  
  int arg = -1;
  float seconds = 0;
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
  void addInstruction(Instruct func, int arg, float seconds);
  void addInstruction(Instruct func, float seconds = -1);
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
  void simpleAccel(float seconds, int setpoint);
    
};

#endif