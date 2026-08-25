#include <Stepper.h>

//Tracking Variables
volatile int state = 0; //State "flips" functions
volatile int curPos1 = 0; //Position of the 1st motor
volatile int curPos2 = 0; //Position of the 2nd motor
volatile int curSteps1 = 0; //Tracking steps for first motor. 200 for a full revolution
volatile int curSteps2 = 0; //Tracking steps for second motor. 200 for a full revolution
const int stepArray[6] = {33,33,34,33,33,34}; //Order of steps. 34 on 3rd and 6th flips. Sums to 200

//Pin Variables
int homePin = 2;
int movePin = 3;
int step1 = 9;
int dir1 = 10;
// int step1 = 5;
// int dir1 = 6;
int step2 = 5;
int dir2 = 6;
// int step2 = 9;
// int dir2 = 10;
int ongPin = 8;
int readPin = 7;

//Delay
int del = 10;
int delLed = 50;

// Creating two instances of the stepper class to represent the two 
// motors we are using
Stepper stepper1 = Stepper(200, step1, dir1);
Stepper stepper2 = Stepper(200, step2, dir2);

//ISRs for flippings states

//move
void move() 
{
  if (state == 0)
  {
    state = 1;
  }
}

//home
void home()
{
  if (state == 0)
  {
    state = 2;
  }
}


void setup() 
{
  //Setting the speed of the stepper motors
  stepper1.setSpeed(15);
  stepper2.setSpeed(15);
  //Digital pins that will send electrical output to drivers
  pinMode(step1, OUTPUT);
  pinMode(dir1, OUTPUT);
  pinMode(step2, OUTPUT);
  pinMode(dir2, OUTPUT);
  //Digital pins that will read electrical output from button to switch states
  pinMode(homePin, INPUT_PULLUP);
  pinMode(movePin, INPUT_PULLUP);
  //Set readers to standby and look for rising edge
  attachInterrupt(digitalPinToInterrupt(movePin), move, RISING);
  attachInterrupt(digitalPinToInterrupt(homePin), home, RISING);
}


void loop() 
{
  //Flipped to move
  if(state == 1)
  {
    //Stepper 2 needs to turn first but only if stepper 1 is on last flip
    if((curPos1 + 1) % 6 == 0)
    {
      stepper2.step(stepArray[curPos2]);
    }

    //Stepper2 tracking updated
    curSteps2 = stepArray[curPos2] % 200;
    curPos2 = (curPos2 + 1) % 6;

    //Mandatory flips for stepper1
    stepper1.step(stepArray[curPos1]);

    //Stepper1 tracking updated
    curSteps1 = stepArray[curPos1] % 200;
    curPos1 = (curPos1 + 1) % 6;
  }

  //Flipped to home
  if(state == 2)
  {
    //Conditions for both steppers to make sure most efficient direction is chosen
    if(curPos2 < 3)
    {
      curSteps2 *= -1;
    }
    if(curPos1 < 3)
    {
      curSteps1 *= -1;
    }

    //Steppers move back to original position
    stepper2.step(curSteps2);
    stepper1.step(curSteps1);

    //All tracking reset
    curSteps1 = 0;
    curPos1 = 0;
    curSteps2 = 0;
    curPos2 = 0;
  }
  //State changed back to 0
  //System stand by waiting for interrupt
  state = 0;
}
