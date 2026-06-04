#ifndef robot_h
#define robot_h

// enum Direction {
//   NONE = -1,
//   FORWARD = 0,
//   BACLWARD = 1,
//   LEFT = 2,
//   RIGHT = 3,
// }

class Robot{
  public:
  Robot();
  Robot(int rmfp, int rmbp, int lmfp, int lmbp);
  void forward(float seconds,int speed);
  void backward(float seconds, int speed);
  void right(float seconds, int speed);
  void left(float seconds, int speed);
  void stop(float seconds);
  void simpleAccel(int setpoint, double seconds, double startTime);
  void updateAccel(double currSeconds);
  private:
  int rightMotorForwardPin;
  int rightMotorBackwardPin;
  int leftMotorForwardPin;
  int leftMotorBackwardPin;
  double accelStartTime = 0;
  double accelTime = 0;
  int setpoint = 0;
  bool accelerate = false;
  // enum Direction currDir = NONE;

};




#endif