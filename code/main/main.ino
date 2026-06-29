#include "list"
#include "robot.hpp"
#include "arduino.h"

void turn180();
AbstractRobot robot;

// Your number from level 3 here:
//  -Oh no! looks like I forogt to type the varible, what would be good at storing a decimal?
const float TURN_90; // TODO change float to ??? to have them type it themselves

void fakeMain()
{
  // Lets make the robot spin around a BUNCH

  // You'll need your number from level 3 put into the variable at the top
  
  // The turn180() function wasn't a huge pain to make because you only had to copy and paste the right (or left) command twice
  // But what if I asked you to turn 5 million degrees? Or less extreme, make the robot spin around 5 times
  // You could make a custom function called "spinAround5Tims" and copy and paste the turn 90 degree command 20 times...
  // Or we could use a loop! Turn 90 degrees, 20 times
  //  - If you don't want to know all the nitty gritty of a for loop, skip ahead to the instructions at the bottom of fakeMain()

  // All loops start with the while loop, everthing in the brackets get repeated as long as the condition (called a Boolean) is true

  while(true){
    break; // I don't actually want to run this loop here so I break it early
  }

  // What we need to do though is check how many times we have looped or iterated through the code in the loop so here's how we do that

  int i = 0; // We'll make an int variable and name it i for iteration, it will track which loop we are on

  while(i < 5){ // This is our condition
    // do code
    i++; // This is shorthand notation for adding 1 to a variable
  }

  // This will run the loop 5 times and here's how:
  //  - Before every execution of code, the loop will check to see if the condition is true
  //  - Since i starts at 0 and 0 is les than 5, the condition passes and the code runs
  //  - Part of the code is to add 1 to the i variable, making it 1 after the first iteration
  //  - Then the loop will check the condition again, i is now 1 but 1 is still less than 5 so it will pass
  //  - This will continue and to track, i is 0: first loop, i is 1: second loop, i is 2: third loop, i is 3: fourth loop
  //  - When i is 4, the condition will still pass, running the code a 5th time. 
  //  - But now i is 5. 5 is not less than 5 so the loop stops running and our code ran a grand total of 5 times
  
  // Congratulations! you now know how a for loop works, so lets make one
  // A for loop has different sytax from what you might excpect but it works the same
  //  - All a for loop's syntax does differently is having the tracking variable be inside some parentheses


  // Instructions: Using the loop below, make the robot spin 360 degrees around 5 times

  int loops; // Set this to the amount of times you want your loop to run

  for(int i = 0; i < loops; i++){ 
    // Your code goes here
  }  
  
}

// Your function may have worked slightly differently and if it ain't broke: don't fix it
void turn180(){
  robot.right(TURN_90);
  robot.right(TURN_90);
};

// Dont worry about this stuff for now :D

const int right_enable_pin = 6;
const int right_dir_pin = 7;
const int left_enable_pin = 8;
const int left_dir_pin = 9;
const uint LED_Pin = 27;

void setup()
{
  pinMode(right_enable_pin, OUTPUT);
  pinMode(right_dir_pin, OUTPUT);
  pinMode(left_enable_pin, OUTPUT);
  pinMode(left_dir_pin, OUTPUT);
  pinMode(LED_Pin, OUTPUT);
  robot = AbstractRobot(right_enable_pin, right_dir_pin, left_enable_pin, left_dir_pin);
  fakeMain();
  robot.robot.setInstructIndex(0);
  
}

void loop()
{
  robot.robot.update();
}
