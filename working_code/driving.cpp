#include <iostream>
using namespace std; 

class Motors {
  private: //by making it hard coded its easier to not change the pins 
    int leftMoter, rightMoter; // creates varibles called leftMoter and pin 2 
  public: //all code in here can be accessed within other functions and main()
    Motors(int p1, int p2) : leftMoter(p1), rightMoter(p2) {} //asigns the moters into the pins in the bred board 

    // this code bellow tells the micocontroller which direction the electricity should flow so the board can push power out the pins to control motors.
    void init() { //void just means it doesnt return anything
      // Arduino-specific code removed for standard C++ compilation
    }

    int speed; 

    void Speed(int speed) {
      int pulses = 120; //TODO corect the numbers bellow 
      int pulsesPerRevolution = 20;
      double seconds = 1.0; 
      double revolutions = double(pulses) / pulsesPerRevolution;
      this->speed = revolutions / seconds * 60.0;  // Use this-> to access member variable
    }

  
};

Motors motors[2] = {Motors(1, 0), Motors(2, 0)}; // left and right motors



//driving forward and backward 
class Commands {
  private:
    char cmdFwd = 'f';
    char cmdRev = 'r';
    char cmdStop = 's';
    bool drive = false;
    bool dontDrive = false;
    bool isReversing = false;

  public:
    void processCommand(char command) {
        if (command == cmdFwd) {
            //move motors forward
            drive = true;
            cout << "moving forward" << endl; 
            // Access motors speed
            cout << "Left motor speed: " << motors[0].speed << endl;
            cout << "Right motor speed: " << motors[1].speed << endl;
        }
        else if (command == cmdRev) {
            // move motors backwards
            isReversing = true;
            motors[0].reverse();
            motors[1].reverse();
            cout << "moving backwards" << endl;
            cout << "Left motor speed: " << motors[0].speed << endl;
            cout << "Right motor speed: " << motors[1].speed << endl;
        }
        else if (command == cmdStop) {
            // turn motors off 
            dontDrive = true;
            cout << "not moving" << endl;
        }
    }
    
    void reverseMotors() {
        // Reverse motor direction
        cout << "Motors reversing" << endl;
    }
};

int main() {
    Commands cmd;
    char command;
    
    cout << "Enter command (f = forward, r = reverse, s = stop): " << endl;
    cin >> command;
    
    cmd.processCommand(command);
    
    return 0;
}


