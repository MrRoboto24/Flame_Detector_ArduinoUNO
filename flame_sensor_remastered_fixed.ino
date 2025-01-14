// Libraries:
#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

//Configuration:
SoftwareSerial BTSerial(10,11); // // Sets up software serial on pins 10 (RX) and 11 (TX).
Servo myServo;  
LiquidCrystal_I2C  lcd(0x27, 16, 2); // Sets the LCD address.
int red_LED_PIN = 8;
int green_LED_PIN = 9;
int buzzer = 4;
const int flameSensorPin = 2;
int servoPin = 6; 

// The program starts with the given setup:

void setup() {
 
  pinMode(flameSensorPin, INPUT);  // Sets flame sensor to input mode.
  pinMode(red_LED_PIN, OUTPUT);  // Sets LED lights to output mode.
  pinMode(green_LED_PIN, OUTPUT);
  pinMode(buzzer, OUTPUT);  // Sets buzzer(siren) to output mode.
  lcd.init(); // Initiallizes the LCD screen.
  lcd.backlight(); // Turns on backlight in the LCD screen.
  myServo.attach(servoPin);  // Attaches the servo motor to pin 6.
  myServo.write(0); // Starts the Servo Moter(water pump).
  
  // Starts the serial communication at a baud rate of 9600:
  Serial.begin(9600); 
  BTSerial.begin(9600);
}
 
// Every second the program loops through the following actions: 
int count = 0;
int currentPosition = 1;
void loop() {
  
  int flameState = digitalRead(flameSensorPin);  // Updates of the situation from the flame sensor. 

// IN CASE FIRE IS DETECTED:

if (flameState == LOW) {  // LOW means that fire is detected.
  count++;
  BTSerial.println("Alert! Flame detected."); // Updates the situation via bluetooth every second.
  Serial.println("Fire detected."); // Prints "Fire detected." in serial screen if fire is detected.
  
  // Displays text ("FIRE DETECTED CALLING:199") in the LCD Screen: 
  lcd.setCursor(1,0);
  lcd.print("FIRE DETECTED!");
  lcd.setCursor(2,1);
  lcd.print("CALLING:199");
  delay(1000);
  lcd.clear();
  delay(200);
  
  // Turns ON/OFF the LED Lights:
  digitalWrite(red_LED_PIN,HIGH);
  digitalWrite(green_LED_PIN, LOW);
  
  // Enables the Buzzer siren:
  tone(buzzer,1000);
  delay(100);
  tone(buzzer, 400);
  delay(50);
  
  // Enables the Servo Moter(water pump):
  if(count == 1){
  myServo.attach(6);
  myServo.write(180);
  currentPosition = 180; 
  delay(500);
  myServo.detach();     
  }
}
 
// IN CASE FIRE IS NOT DETECTED:
  
else {

 BTSerial.println("No Flame Detected.");  // Updates the situation via bluetooth every second.
 Serial.println("Fire not detected.");  // Prints "Fire not detected." in serial screen if fire is NOT detected.
  
 // Displays text ("FIRE NOT DETECTED") in the LCD Screen:
 lcd.setCursor(0,0);
 lcd.print("    FIRE NOT    ");
 lcd.setCursor(4,1);
 lcd.print("DETECTED");
 delay(1000);
 lcd.clear();
 delay(200);
 
// Turns ON/OFF the LED Lights:
 digitalWrite(green_LED_PIN, HIGH);
 digitalWrite(red_LED_PIN,LOW);

 // Disables the Buzzer siren:
 noTone(buzzer);
 if(count >= 0){
  if (currentPosition != 0){
  myServo.attach(6);
  myServo.write(0);
  currentPosition = 0; 
  delay(500); 
  myServo.detach();
  }
 }
count = 0;
 // Disables the Servo Moter(water pump):
  
 delay(50);
}

  delay(50);
}