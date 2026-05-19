#include <Arduino.h>
#include <iostream>

class Motors {
  private: //by making it hard coded its easier to not change the pins 
    int leftMoter, rightMoter; // creates varibles called leftMoter and pin 2 
  public: //all code in here can be accessed within other functions and main()
    Motors(int p1, int p2) : leftMoter(p1), rightMoter(p2) {} //asigns the moters into the pins in the bred board 


    // this code bellow tells the micocontroller which direction the electricity should flow so the board can push power out the pins to control motors.
    void init() { //void just means it doesnt return anything
      pinMode(leftMoter, OUTPUT); // this jsut says that the left moter will output voltage 
      pinMode(rightMoter, OUTPUT); // pinmode is a built in control that tells the microcontroler what to do 
    }

    void Speed(int speed) {
      int pulses = 120; //TODO corect the numbers bellow 
      int pulsesPerRevolution = 20;
      double seconds = 1.0; 
      revolutions = double(pulses) / pulsesPerRevolution
      speed = revolutions / seconds * 60.0 
    }

    void stop() {
      digitalWrite(leftMoter, LOW);
      digitalWrite(rightMoter, LOW);
    }
};

Motors leftMotor(9, 10);
Motors rightMotor(5, 6);

void setup() { //runs when powered on and never again
  Serial.begin(9600); // the bits per second the board is tranferring data 
  leftMotor.init(); // start up comand so the motors can get instructions 
  rightMotor.init();
}

void loop() {//digitalWrite() sets a pin to a binary HIGH (5V/3.3V) or LOW (0V). analogWrite() uses PWM (Pulse Width Modulation) to simulate analog voltages (0-255) 
        analogWrite(leftMoter, speed);
        analogWrite(rightMoter, speed);
        
      } else {
        digitalWrite(leftMoter, LOW);
        digitalWrite(rightMoter, LOW);
      }
   // runs repeadly through the code 
}

//driving forward and backward 
int main() {
    bool drive = false;
    bool dontDrive = false;
    bool reverse = false;

    char command;
    cout << "Enter command (d = forward, r = reverse, s = stop): " << endl;
    cin >> command;

    if (command == 'd') {
        //move motors forward
        drive = true;
        cout << "moving forward" << endl; 
             
    }
    else if (command == 'r') {
        // move motors backwards
        reverse = true; 
        cout << "moving backwards" << endl;
    }
    else if (command == 's') {
        // turn motors off 
        dontDrive = true;
        cout << "not moving" << endl;
    }
    
    return 0;
}


