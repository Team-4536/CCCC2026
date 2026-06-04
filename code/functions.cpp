#include "robot.h"
#include "arduino.h"

Robot::Robot(){

}
Robot::Robot(int rmfp, int rmbp, int lmfp, int lmbp){
  rightMotorForwardPin = rmfp;
  rightMotorBackwardPin = rmbp;
  leftMotorForwardPin = lmfp;
  leftMotorBackwardPin = lmbp;
}
void Robot::forward(float seconds, int speed) {
  digitalWrite(this->rightMotorBackwardPin, LOW);
  analogWrite(this->rightMotorForwardPin, speed);
  digitalWrite(this->leftMotorBackwardPin, LOW);
  analogWrite(this->leftMotorForwardPin, speed);
  digitalWrite(27, HIGH);
  delay(1000*seconds);
  digitalWrite(27, LOW);
}

void Robot::backward(float seconds, int speed) {
  digitalWrite(this->rightMotorForwardPin, LOW);
  analogWrite(this->rightMotorBackwardPin, speed);
  digitalWrite(this->leftMotorForwardPin, LOW);
  analogWrite(this->leftMotorBackwardPin, speed);
  delay(1000*seconds);
}

void Robot::right(float seconds, int speed) {
  digitalWrite(this->rightMotorBackwardPin, LOW);
  analogWrite(this->rightMotorForwardPin, speed);
  digitalWrite(this->leftMotorForwardPin, LOW);
  analogWrite(this->leftMotorBackwardPin, 0);
  digitalWrite(27, HIGH);
  delay(1000*seconds);
  digitalWrite(27, LOW);
}

void Robot::left(float seconds, int speed) {
  digitalWrite(this->rightMotorForwardPin, LOW);
  analogWrite(this->rightMotorBackwardPin, 0);
  digitalWrite(this->leftMotorBackwardPin, LOW);
  analogWrite(this->leftMotorForwardPin, speed);
  delay(1000*seconds);
}

// Connor's stuff is below

void Robot::stop(float seconds) {
  digitalWrite(this->rightMotorBackwardPin, LOW);
  analogWrite(this->rightMotorForwardPin, 0);
  digitalWrite(this->leftMotorBackwardPin, LOW);
  analogWrite(this->leftMotorForwardPin, 0);
  delay(1000*seconds);
  
}

void Robot::simpleAccel(int setpoint, double seconds, double startTime){
  accelStartTime = startTime;
  accelTime = seconds;
  this->setpoint = setpoint;
}

void Robot::updateAccel(double currSeconds){
  double mult = (currSeconds - accelStartTime) / accelTime;
  //speed = setpoint * mult;

}


