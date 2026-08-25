#include <AccelStepper.h>

//State Default
volatile int state = 0;
const long speed = 889;
const int microLevel = 8;
const long stepsPR = 200 * microLevel;
//Digital Output Pins
const int stepPin = 5;
const int directionPin = 4;
//Digital Interrupt Pins
const int movePin = 2;
const int homePin = 3;
//Delay Amount with microstep listed on the side
const int del = 3; //Microstep 8
//Tracking Variables
volatile int curPos = 0;
int rotPos; //Need to track rotational position because AccelStep does not reset after a full revolution
// const long stepArray[6] = {33, 66, 100, 133, 166, 200};
const long stepArray[6] = {267, 267, 266, 267, 267, 266};
//Declaring a AccelStepper object ~ stepper1 & stepper2 (soon)
AccelStepper stepper1 = AccelStepper(AccelStepper::DRIVER, stepPin, directionPin);

//Declaring ISR functions
void move() {
  if (state == 0){
    state = 1;
  }
}

void home() {
  if (state == 0){
    state = 2;
  }
}

int rotCalc(AccelStepper stepper, int stepsPR = stepsPR){
  rotPos = stepper.currentPosition() % stepsPR;
  return rotPos;
}

void setup() {
  //Setting stepper speeds
  stepper1.setMaxSpeed(speed);
  //Setting pinModes
  pinMode(movePin, INPUT_PULLUP);
  pinMode(homePin, INPUT_PULLUP);
  //Assigning ISRs to interrupt pins
  attachInterrupt(digitalPinToInterrupt(movePin), move, RISING);
  attachInterrupt(digitalPinToInterrupt(homePin), home, RISING);
}

void loop() {
  if (state == 1){
    stepper1.moveTo(stepper1.currentPosition() + stepArray[curPos]);
    stepper1.setSpeed(speed);
    while(stepper1.distanceToGo() != 0){
      stepper1.runSpeedToPosition();
    }
    // if(curPos + 1 == 6){
    //   stepper1.setCurrentPosition(0);
    //   stepper1.setSpeed(speed);}
    // }
    // else{
    curPos = (curPos + 1) % 6;
    // }
    state = 0;
  }
  if (state == 2){
    int steps = stepper1.currentPosition();
    if(rotCalc(stepper1) <= 800){
      steps *= -1;
    }
    stepper1.moveTo(stepper1.currentPosition()+steps);
    while(stepper1.distanceToGo() != 0){
      stepper1.setSpeed(speed);
      stepper1.runSpeedToPosition();
    }
    stepper1.setCurrentPosition(0);
    state = 0;
    curPos = 0;
    rotPos = 0;
  }
}

