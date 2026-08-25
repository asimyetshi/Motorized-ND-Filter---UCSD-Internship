#include <AccelStepper.h>

//State Default
volatile int state = 0;
const long speed = 889;
// const int microLevel = 8;
// const long stepsPR = 200 * microLevel;
const long stepsPR = 1600;
//Digital Output Pins
const int stepPin1 = 5;
const int directionPin1 = 4;
const int stepPin2 = 6;
const int directionPin2 = 7;
//Digital Interrupt Pins
const int movePin = 2;
const int homePin = 3;
//Delay Amount with microstep listed on the side
// const int del = 3; //Microstep 8
//Tracking Variables
volatile int curPos1 = 0;
volatile int curPos2= 0;
int rotPos1; //Need to track rotational position because AccelStep does not reset after a full revolution
int rotPos2; //Need to track rotational position because AccelStep does not reset after a full revolution
// const long stepArray[6] = {33, 66, 100, 133, 166, 200};
const long stepArray[6] = {267, 534, 800, 1067, 1334, 1600};
//Declaring a AccelStepper object ~ stepper1 & stepper2 (soon)
AccelStepper stepper1 = AccelStepper(AccelStepper::DRIVER, stepPin1, directionPin1);
AccelStepper stepper2 = AccelStepper(AccelStepper::DRIVER, stepPin2, directionPin2);
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

// int rotCalc(AccelStepper stepper, int stepsPR = stepsPR){
//   int rotPos = stepper.currentPosition() % stepsPR;
//   return rotPos;
// }

void setup() {
  //Setting stepper speeds
  stepper1.setMaxSpeed(speed);
  stepper2.setMaxSpeed(speed);
  //Setting acceleration to 0 because default is 1
  // stepper1.setAcceleration(0);
  // stepper2.setAcceleration(0);
  //Setting pinModes
  pinMode(movePin, INPUT_PULLUP);
  pinMode(homePin, INPUT_PULLUP);
  //Assigning ISRs to interrupt pins
  attachInterrupt(digitalPinToInterrupt(movePin), move, RISING);
  attachInterrupt(digitalPinToInterrupt(homePin), home, RISING);
}

void loop() {
  
  if (state == 1){
    stepper1.setCurrentPosition(stepper1.currentPosition() % stepsPR);
    stepper2.setCurrentPosition(stepper2.currentPosition() % stepsPR);
    if((curPos1 + 1) % 6 == 0){
      stepper2.moveTo(stepArray[curPos2]);
      stepper2.setSpeed(speed);
      while(stepper2.distanceToGo() != 0){
        stepper2.runSpeedToPosition();
      }
      curPos2 = (curPos2 + 1) % 6;
    }
    stepper1.moveTo(stepArray[curPos1]);
    stepper1.setSpeed(speed);
    while(stepper1.distanceToGo() != 0){
      stepper1.runSpeedToPosition();
    }

    curPos1 = (curPos1 + 1) % 6;
    state = 0;
  }
  if (state == 2){
    // int steps2 = stepper2.currentPosition() % 1600;
    // int steps2 = rotCalc(stepper2);
    // if(rotCalc(stepper2) <= 800){
    //   steps2 *= -1;
    // }

    // int steps1 = stepper1.currentPosition() % 1600;
    // int steps1 = rotCalc(stepper1);
    // if(rotCalc(stepper1) <= 800){
    //   steps1 *= -1;
    // }
    int target1 = 0;
    int target2 = 0;
    if (stepper1.currentPosition() >= 800){
      target1 = 1600;
    }
    if (stepper2.currentPosition() >= 800){
      target2 = 1600;
    }
    
    stepper2.moveTo(target2);
    stepper2.setSpeed(speed);
    while(stepper2.distanceToGo() != 0){
      stepper2.runSpeedToPosition();
    }
    stepper1.moveTo(target1);
    stepper1.setSpeed(speed);
    while(stepper1.distanceToGo() != 0){
      stepper1.runSpeedToPosition();
    }
    stepper2.setCurrentPosition(0);
    stepper1.setCurrentPosition(0);
    state = 0;
    curPos1 = 0;
    rotPos1 = 0;
    curPos2 = 0;
    rotPos2 = 0;
  }
}