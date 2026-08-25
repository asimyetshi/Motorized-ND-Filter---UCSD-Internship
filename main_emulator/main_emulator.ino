int state = 0;
int movePin = 2;
int homePin = 3;
int ready = 5;

void change(){
  if (state == 0){
    state = 1;
  }
}

void setup() {
  pinMode(movePin, INPUT_PULLUP);
  pinMode(homePin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(movePin), change, RISING);
  attachInterrupt(digitalPinToInterrupt(homePin), change, RISING);
}

void loop() {
  
  if (state != 0){
    delay(1000);
    digitalWrite(ready, HIGH);
    delay(10);
    digitalWrite(ready, LOW);
    state = 0;

  }
}
