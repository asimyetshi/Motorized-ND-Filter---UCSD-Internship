//Tracking Variables
volatile int state = 0; //
volatile int curPos = 0; //Home Position is defined as one
volatile int curSteps = 0;
int counter = 0;
//Pin Variables
int homePin = 2;
int movePin = 3;
int step1 = 9;
int dir1 = 10;
int step2 = 5;
int dir2 = 6;
int ongPin = 7;
int readPin = 8;
//Delay
int del = 10;
int delLed = 50;

void setup() {
  pinMode(step1, OUTPUT);
  pinMode(dir1, OUTPUT);
  pinMode(step2, OUTPUT);
  pinMode(dir2, OUTPUT);
  pinMode(homePin, INPUT_PULLUP);
  pinMode(movePin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(movePin), move, RISING);
  attachInterrupt(digitalPinToInterrupt(homePin), homing, RISING);

  Serial.begin(115200);
  Serial.println("Hello");
}
//This switches on the moving function inside loop() if the pin detects a rising edge
void move() {
  // Serial.println("Interrupt received");
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

//Perpetual Segment
void loop() {
  //Step Function - should also update steps so we can make sure it lands on same values
  if (state == 1){
    digitalWrite(readPin, LOW);
    digitalWrite(ongPin, HIGH);
    //Direction A for reference; not sure if it is CW or CCW
    digitalWrite(dir1, HIGH);
    //Does 34 steps on 3rd and 6th lense to make sure that it fully loops (prevents drift)
    int steps = 33;
    if ((counter + 1) % 3 == 0) {
      steps = 34;
     }
    
    for(int i = 0; i < steps; i++){
      digitalWrite(step1, HIGH);
      delay(del);
      digitalWrite(step1, LOW);
      delay(del);
      curSteps += 1;
    }
    curPos += 1;
    state = 0;
    digitalWrite(ongPin, LOW);
    digitalWrite(readPin, HIGH);
    delay(delLed);
    digitalWrite(readPin, LOW);
  }
    
  
  //Homing Function
  if (state == 2){
    digitalWrite(readPin, LOW);
    digitalWrite(ongPin, HIGH);
    //Note: Direction A is HIGH Direction B is LOW
    int stepDir = 1;
    if(curPos <= 2){
      digitalWrite(dir1, LOW);
      stepDir = -1;
    }
    // for(int i = 0; i < 5 - curPos; i++){
    //     digitalWrite(step, HIGH);
    // }
    while(curSteps != 0)
    {
      digitalWrite(step1, HIGH);
      delay(del);
      digitalWrite(step1, LOW);
      delay(del);
      curSteps += stepDir;
      curSteps %= 200;
    }
    curPos = 0;
    state = 0;
    digitalWrite(ongPin, LOW);
    digitalWrite(readPin, HIGH);
    delay(delLed);
    digitalWrite(readPin, LOW);
    }
}