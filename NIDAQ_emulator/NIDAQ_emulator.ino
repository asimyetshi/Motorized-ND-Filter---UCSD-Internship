// Version #1
const int moveEm = 5;
const int delEm = 1000;
const int pause = 3;
const int delChange = 3000/2;
volatile int state = 0;

void setup() {
  pinMode(moveEm, HIGH);
  pinMode(pause, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(pause), changeDetect, CHANGE);
}

void changeDetect(){
  if (state == 0){
    state = 1;
  }
  
}

void loop() {
  
  if(state == 1){
    delay(delChange);
  }

  digitalWrite(moveEm,HIGH); 
  delay(delEm);
  digitalWrite(moveEm,LOW);
  delay(delEm);

  state = 0;
}

// Version #2
// int moveSig = 5;
// int homeSig = 6;
// int del = 1000;

// void setup(){
//   pinMode(moveSig, OUTPUT);
//   pinMode(homeSig, OUTPUT);
// }

// void loop(){
//   digitalWrite(moveSig, HIGH);
//   delay(100);
//   digitalWrite(moveSig, LOW);
//   delay(del);
//   digitalWrite(homeSig, HIGH);
//   delay(100);
//   digitalWrite(homeSig, LOW);

// }
