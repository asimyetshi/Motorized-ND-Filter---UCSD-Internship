//Tracking Variables
volatile int state = 0; //State "flips" functions
volatile int curPos = 0; //Position of the 1st motor
volatile int curPos2 = 0; //Position of the 2nd motor
volatile int curSteps = 0; //Tracking steps for first motor. 200 for a full revolution
volatile int curSteps2 = 0; //Tracking steps for second motor. 200 for a full revolution
const int stepArray[6] = {33,33,34,33,33,34}; //Order of steps. 34 on 3rd and 6th flips. Sums to 200
//Pin Variables
int homePin = 2;
int movePin = 3;
// int step1 = 9;
// int dir1 = 10;
int step1 = 5;
int dir1 = 6;
// int step2 = 5;
// int dir2 = 6;
int step2 = 9;
int dir2 = 10;
int ongPin = 8;
int readPin = 7;
//Delay
int del = 10;
int delLed = 50;


void setup() 
{
  Serial.begin(115200);
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
  attachInterrupt(digitalPinToInterrupt(homePin), homing, RISING);
}


//Define state switches

//This switches on the moving function inside loop() if the pin detects a rising edge
void move() {
  Serial.println("Interrupt received");
  if (state == 0){
    state = 1;
    // Serial.println("State Updated");
  }
}

//This switches on the homing function inside loop() if the pin detects a rising edge
void homing() {
  if (state == 0){
    state = 2;
  }
}


//Loop
void loop() 
{
  //Step Function - should also update steps so we can make sure it lands on same values
  if (state == 1)
  {
    //LED
    digitalWrite(readPin, LOW);
    digitalWrite(ongPin, HIGH);
    //Direction A for reference; not sure if it is CW or CCW
    digitalWrite(dir1, HIGH);

    //Note: The second motor turns first
    
    //If statement that triggers second motor
    if ((curPos + 1) % 6 == 0)
    {
      //The for loop responsible for stepping; updates steps and later position is updated
      for(int i = 0; i < stepArray[curPos2]; i++)
      {
        digitalWrite(step2, HIGH);
        delay(del);
        digitalWrite(step2, LOW);
        delay(del);
        curSteps2 = (curSteps2 + 1) % 200;
      }
      //Updates the position
      curPos2 = (curPos2 + 1) % 6;
    }
  
    //The for loop responsible for stepping; updates steps and later position is updated
    for(int i = 0; i < stepArray[curPos]; i++)
    {
      digitalWrite(step1, HIGH);
      delay(del);
      digitalWrite(step1, LOW);
      delay(del);
      curSteps = (curSteps + 1) % 200;
    }
    
    //Updates the position
    curPos = (curPos + 1) % 6;
    //Changes the state back to 0 to prevent infinite move loop
    state = 0;
    //Flashes ready LED
    digitalWrite(ongPin, LOW);
    digitalWrite(readPin, HIGH);
    delay(delLed);
    //Everything turned off
    digitalWrite(readPin, LOW);
  }
    
  
  //Homing Function
  if (state == 2)
  {
    //LED
    digitalWrite(readPin, LOW);
    digitalWrite(ongPin, HIGH);
    
    //Note: Direction A is HIGH Direction B is LOW
    
    int stepDir = 1; //Variable used to determine homing direction; 1st motor
    int stepDir2 = 1; //Variable used to determine homing direction; 2nd motor
    //If first motor has gone halfway or less --> it turns around
    if(curPos <= 2)
    {
      //Switches direction
      digitalWrite(dir1, LOW);
      //Subtracts from curSteps until it equals zero instead of adding until its equal to 200
      stepDir = -1;
    }
    
    //If first motor has gone halfway or less --> it turns around
    if(curPos2 <= 2)
    {
      //Switches direction
      digitalWrite(dir2, LOW);
      //Subtracts from curSteps until it equals zero instead of adding until its equal to 200
      stepDir2 = -1;
    }

    //Movement Loop for 1st Motor
    while(curSteps != 0)
    {
      digitalWrite(step1, HIGH);
      delay(del);
      digitalWrite(step1, LOW);
      delay(del);
      //Steps until it undos prior movement
      //Direction logic above assigns sign value which handles increment in accordance with direction (+/-)
      curSteps += stepDir;
      curSteps %= 200;
    }
    
    //Movement Loop for 2nd Motor
    while(curSteps2 != 0)
    {
      digitalWrite(step2, HIGH);
      delay(del);
      digitalWrite(step2, LOW);
      delay(del);
      //Steps until it undos prior movement
      //Direction logic above assigns sign value which handles increment in accordance with direction (+/-)
      curSteps2 += stepDir2;
      curSteps2 %= 200;
    }
    
    
    //Resets position counter and state
    curPos = 0;
    curPos2 = 0;
    state = 0;

    //Flashes Ready LED
    digitalWrite(ongPin, LOW);
    digitalWrite(readPin, HIGH);
    delay(delLed);

    //Everything off
    digitalWrite(readPin, LOW);
    }
}