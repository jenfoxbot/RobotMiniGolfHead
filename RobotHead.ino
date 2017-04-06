/*Code written by  jenfoxbot <jenfoxbot@gmail.com> 
*Many thanks to the servo motor help from "Sweep" by BARRAGAN
*<http://barraganstudio.com> and modified by Scott Fitzgerald
*
* ----------------------------------------------------------------------------
 * "THE BEER/COFFEE-WARE LICENSE" (Revision 42):
 * <jenfoxbot@gmail.com> wrote this file.  As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer or a coffee in return.
 * ----------------------------------------------------------------------------

*/

#include <Servo.h>

//Set up servo motor variables
Servo myservo;  // create servo object to control a servo

int pos = 0;    // variable to store the servo position
int signal = 9; //servo pin number

double sigRound;
int sigSteps1;
int sigSteps2;
int sigDelay;
int lastSig;

//Set up IR sensor variables
#define LEDPin 12
#define SensorPin 10

//variables that will change
int sensorState = 0, lastState = 0;

unsigned long lastPost;

void setup() {
  Serial.begin(9600);
  myservo.attach(signal);  // attaches the servo on pin 9 to the servo object
  pinMode(LEDPin, OUTPUT);

  pinMode(SensorPin, INPUT);
  digitalWrite(SensorPin, HIGH); //turn on pullup resistor
}

void loop() {
  digitalWrite(A0, HIGH);  // OPTIONAL: to increase photoresistor signal, set pullup on analog pin 0
  
  
  lastSig = moveMotor(1, 1, 1);

 //Check status of IR sensor
 sensorState = digitalRead(SensorPin);

  if (sensorState == LOW){
    //turn LED on:
    digitalWrite(LEDPin, HIGH);
  }
  else{
    //turn LED off
    digitalWrite(LEDPin, LOW);
  } 

  if (sensorState && !lastState){
    Serial.println("Unbroken");
  }
  if (!sensorState && lastState){
    Serial.println("Broken");
  }

  lastState = sensorState;
}


int moveMotor(int sig, int sigSteps1, int sigSteps2){
  double sigRound;
  double lastSig;
 
  sigRound = sig/100;
 
  for (pos = 0; pos <= 180; pos += sigSteps1) { //degree steps given by photoresistor signal (e.g. 30 = 30 degree steps)
    myservo.write(pos);     //write servo to variable position pos
    delay(10);     // waits 10ms for the servo to reach the position
  }
  
  for (pos = 180; pos >= 0; pos -= sigSteps2) { 
    myservo.write(pos);              
    delay(10);    // waits 10ms for the servo to reach the position
  }
  lastSig = sigRound;  

  return sigRound;  
}

