//initializing the pin that we are using for LED
int ledPin1 = 13;
int ledPin2 = 12;
int ledPin3 = 11;
//The setup function runs once when you restart or power the board
void setup() {
  //initialize digital pin LED_BUILTIN as an output
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
}

//The loop function runs over and over again forever
void loop() {
  digitalWrite(ledPin1, HIGH);
  digitalWrite(ledPin2, HIGH);
  delay(1000);
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin3, HIGH);
  delay(1000);
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin1, HIGH);
  delay(333);
  digitalWrite(ledPin3, LOW);


}
