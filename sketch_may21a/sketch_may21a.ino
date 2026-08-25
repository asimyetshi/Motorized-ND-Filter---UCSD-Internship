// Define the pin connections

const int irSensorPin = 7;   // IR sensor OUT pin connected to digital pin 7

const int ledPin = 2;        // LED connected to digital pin 2

void setup() {

  pinMode(irSensorPin, INPUT);

  pinMode(ledPin, OUTPUT);

  Serial.begin(9600);

}

void loop() {

  int sensorValue = digitalRead(irSensorPin);

  // Most IR line sensors output LOW on black

  // and HIGH on white

  if (sensorValue == HIGH) {

    // Black line detected

    digitalWrite(ledPin, HIGH);

    Serial.println("Black line detected!");

  } 

  else {

    // White surface detected

    digitalWrite(ledPin, LOW);

    Serial.println("White surface.");

  }

  delay(100);

}