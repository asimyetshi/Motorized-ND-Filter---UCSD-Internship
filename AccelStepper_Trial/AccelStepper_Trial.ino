#include <AccelStepper.h>

//Tracking Variables
volatile int state = 0;
volatile int curPos = 0;
volatile int curSteps = 0;
const int posArray[6] = {33, 66, 100, 133, 166, 200};
//Pin Variables
//Interrupts
const int movePin = 2;
const int homePin = 3;
//Outputs
int step = 5;
int dir = 4;
//Delay - TBD

//LED pins
int ready = 0;
int ongoing = 0;

AccelSteper stepper = AccelStepper(AccelStepper::DRIVER, step, dir);

void setup()
{
  //Serial object initialized to test if inputs are recieved
  // Serial.begin(115200);
  //Set pin modes (output or input_pullup)
  pinMode(step, OUTPUT);
  pinMode(dir, OUTPUT);
  //Interrupt pins set
  pinMode(homePin, INPUT_PULLUP);
  pinMode(movePin, INPUT_PULLUP);
  //Setting LED and NIDAQ pins to ouput
  pinMode(ready, OUTPUT);
  pinMode(ongoing, OUTPUT);
  //Set assign interrupt pins to designated ISRs
  //Move pin attached to move ISR detecting rising edge (i.e. 5v pulse)
  attachInterrupt(digitalPinToInterrupt(movePin), move, RISING);
  //Home pin attached to home ISR detecting rising edge (i.e. 5v pulse)
  attachInterrupt(digitalPinToInterrupt(homePin), homing, RISING);
  //Seting stepper 
}

//Define ISRs - move and home

//Move ISR---switches state to 1 (move condition in loop)
void move()
{
  //If (state == 0) i.e. on standby trigger state
  if(state == 0){
    state = 1;
  }
}

//Home ISR---switches state to 2 (homing condition in loop)
void home()
{
  //If (state == 0) i.e. on standby trigger state
  if(state == 0){
    state = 2;
  }
}


/*
Continuous loop during runtime.
Contains the movement and homing functions while also making sure continuous trials run smoothly
Note to self: make sure to add Serial.println("Signal received!") to check interrupt for 2 & 3
*/
void loop()
{
  //Step function
  if (state == 1)
  {
    //LED
    digitalWrite(ready, LOW)
    digitalWrite(ongoing, HIGH)
    // Not sure if we need to set direction or if library handles by itself
    // digitalWrite(dir, HIGH)

    //Note: the second motor needs to turn first because of experimental necessity

    
    /*
    If statement that triggers the second motor
    {
    Steps on second motor
    Update necessary tracking for stepper2
    Something that skips the rest of the if statement (maybe else statement outside or can reverse logic)
    }    
    Need to reset LED
    */
  }
  //Homing function
  if (state == 2)
  {
    //LED
    digitalWrite(ready, LOW)
    digitalWrite(ongoing, HIGH)
    /*
    Choose best direction (maybe library handles)
    Move to position 0
    Reset tracking
    */

  }
}
