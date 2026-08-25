const int moveEm = 5;
const int homeEm = 6;
const int delEm = 300; //Note: changed 1000-->300

/*
Commented because associated with NIDAQ integration
const int pause = 3;
const int delChange = 3000/2;
volatile int state = 0;
*/

//Test array for newly implemented homing feature
const int testArr[37] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
    10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
    30, 31, 32, 33, 34, 35, 36
};
//Tracking for test array
volatile int flips = 0;
volatile int cycle = 0;


void setup() {
  pinMode(moveEm, HIGH);
  pinMode(homeEm, HIGH);
  
  delay(10000);
  // pinMode(pause, INPUT_PULLUP); //Associated with NIDAQ integation

  // attachInterrupt(digitalPinToInterrupt(pause), changeDetect, CHANGE); //Associated with NIDAQ integation
}

// void changeDetect(){ //Associated with NIDAQ integation
//   if (state == 0){
//     state = 1;
//   }
// }

void loop() {
  
  // if(state == 1){ //Associated with NIDAQ integation
  //   delay(delChange);
  // }

  if(testArr[cycle] == flips){
    digitalWrite(homeEm, HIGH);
    delay(delEm); //Do I need this?
    digitalWrite(homeEm, LOW); 

    cycle = (cycle + 1) % 36;
    flips = 0;
  
  }

  digitalWrite(moveEm,HIGH); 
  delay(delEm);
  digitalWrite(moveEm,LOW);
  delay(delEm);
  
  flips += 1;
  // state = 0;
}
