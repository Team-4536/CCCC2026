#ifndef robot_h
#define robot_h

class Motor;
class Robot;

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

// ROBOT CLASS
class Robot
{
public:
  Robot();
  Robot(int rmfp, int rmbp, int lmfp, int lmbp, int echo, int trigger);
  void forward(int speed);
  void backward(int speed);
  void right(int speed);
  void left(int speed);
  void stop();
  void accelerate(int setpoint);
  void updateAccel(double currSeconds);
  void update();
  double getSonicDist();

private:
  Motor rightMotor;
  Motor leftMotor;
  int triggerPin;
  int echoPin;
  float funcStartTime;
  float funcTime;
  int setpoint = 0;
  int currSpeed = 0;
  bool isAccelerating = false;
  
};

#endif