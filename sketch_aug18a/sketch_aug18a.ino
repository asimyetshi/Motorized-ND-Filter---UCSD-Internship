#include <Stepper.h>
//State
volatile int state = 0;
//Pin Variables
int movePin = 3;
int step = 5;
int dir = 4;
//Delay (ms)
int del = 10;
//Tracking variable
volatile int curPos = 0;
volatile int curSteps = 0;
//Order of steps. 34 on 3rd and 6th flips. Sums to 200
const int stepArray[6] = {33,33,34,33,33,34}; 

Stepper stepMan = Stepper(200, step, dir);

//move
void move() 
{
  Serial.println("Interrupt Received");
  if (state == 0)
  {
    state = 1;
  }
}

void setup() 
{
  //Initializing Serial object
  //Serial.begin(115200);
  //Setting speed for stepper
  stepMan.setSpeed(15);
  //Assigning digital pins
  pinMode(dir,OUTPUT);
  pinMode(step, OUTPUT);
  //Assigning interrupt pins
  pinMode(movePin, INPUT_PULLUP);
  //Set readers to standby and look for rising edge
  attachInterrupt(digitalPinToInterrupt(movePin), move, RISING);
}

void loop() {
  //Flipped to move
  if(state == 1)
  {
    //Mandatory flips for stepper1
    stepMan.step(stepArray[curPos]);
    curSteps = (curSteps + stepArray[curPos]) % 200;
    curPos = (curPos + 1) % 6;
    state = 0;
  }
}
