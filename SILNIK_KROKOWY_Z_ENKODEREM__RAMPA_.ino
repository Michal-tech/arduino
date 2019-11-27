
/*
silnik krokowy :
uzw nr1. 2,3
uzw nr2. 4,5
aktywator:
button1  6
enkoder:

 */

#include <Stepper.h>
int button1 = 6;
const int stepsPerRevolution = 200;  
Stepper myStepper(stepsPerRevolution, 2, 3, 4, 5);
int val;
int encoder0PinA = 7;
int encoder0PinB = 8;
int encoder0Pos = 0;
int encoder0PinALast = LOW;
int n = LOW;
int krok;
int predkosc;
void setup() {
 
  myStepper.setSpeed(100); 
  Serial.begin(9600);
  pinMode(button1,INPUT_PULLUP);
  pinMode (encoder0PinA, INPUT_PULLUP);
  pinMode (encoder0PinB, INPUT_PULLUP);
  
}

void loop() {
  if(encoder0Pos >= 95){
    predkosc = 20;
  }else{
    predkosc = 100;
  }
  if(encoder0Pos <= 100){
  if(digitalRead(button1) == false){
  myStepper.setSpeed(predkosc); 
  myStepper.step(1);
 // Serial.print(krok);
 // enkoder();
  
  }
  }else{
    
  }
  enkoder();
  /*
  Serial.println("counterclockwise");
  myStepper.step(-stepsPerRevolution);
  delay(500);
  */
}
void enkoder(){
     n = digitalRead(encoder0PinA);
  if ((encoder0PinALast == LOW) && (n == HIGH)) {
    if (digitalRead(encoder0PinB) == LOW) {
      encoder0Pos--;
    } else {
      encoder0Pos++;
    }
    Serial.print (encoder0Pos);
    Serial.print ("/");
  }
  encoder0PinALast = n;
}
