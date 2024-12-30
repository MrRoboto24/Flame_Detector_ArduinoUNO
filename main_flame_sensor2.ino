//ONLY SERVO!!!
// Libraries:
#include <Wire.h>
#include <Servo.h>

//Configuration:
Servo myServo;  
const int flameSensorPin = A0;
int servoPin = 7; 

// The program starts with the given setup:

void setup() {
  Serial.begin(9600);
  pinMode(flameSensorPin, INPUT);  // Sets flame sensor to input mode.
  myServo.attach(servoPin);  // Attaches the servo motor to pin 7.
  myServo.write(0); // Starts the Servo Moter(water pump).
}
 
// Every second the program loops through the following actions: 

void loop() {
  int flameState = analogRead(flameSensorPin);  // Updates of the situation from the flame sensor. 

if (flameState < 400) {  // LOW means that fire is detected.MEGALITERO NOUMERO Pio efkola entopizei fotia,
  Serial.println("Fire detected.");
  myServo.write(150);
  delay(1900);      
}
 
else {
  Serial.println("Fire not detected.");
  myServo.write(0); 
  delay(1900);
  }

  delay(50);
}