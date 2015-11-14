#include <Servo.h>  

//servos
Servo myservo;
Servo myservoTwo;
int pos1 = 0;
int pos2 = 30;
long interval = 15;

//vibration motor
int vibrate = 4;

//touch sensor
const int fsrTummy = A4; 
int fsrTummyValue = 0;
const int fsrHead = A5;
int fsrHeadValue = 0;
int tickleState = LOW;

//accelerometer
const int xIn = A2;
const int yIn = A1;
const int zIn = A0;
int xValue = 0;
int yValue = 0;
int zValue = 0;
int slpPin = 2;
int yPrevious = 0;

//eyes
const int eyes = 6;

//mouth matrix
int outTop = 13;
int outBottom = 12;
int in1 = 11;
int in2 = 10;
int in3 = 9;
int in4 = 8;
int in5 = 7;

//time
unsigned long time;
long timePrevious = 0;
long timeDiff;
int t = 0; //iterator for servo delay
int motorSteps = 0;


void setup() {
   pinMode(eyes, OUTPUT);
   pinMode(slpPin, OUTPUT);
   digitalWrite(slpPin, HIGH);
   pinMode(vibrate, OUTPUT);
  
    //matrix
    pinMode(outTop, OUTPUT);
    pinMode(outBottom, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
    pinMode(in5, OUTPUT);
   
   //servos
   myservo.attach(3); 
   myservo.write(30);   
   myservoTwo.attach(5);
   myservoTwo.write(0);
   
   //plushie starts off with neutral expression
   neutral();
     
   Serial.begin(9600);
}

void loop() {

  timePrevious = time;
  yPrevious = yValue;
  
  
  //analog reads
  fsrTummyValue = analogRead(fsrTummy); 
  fsrHeadValue = analogRead(fsrHead); 
  xValue = analogRead(xIn);
  yValue = analogRead(yIn);
  zValue = analogRead(zIn); 
  
  //eyes are on always
  digitalWrite(eyes, HIGH);
  
  if (fsrTummyValue > 50) {
    tickleState = !tickleState;
    time = millis();
    
    int timeDiff = (time-timePrevious);
    
    //checking interval
    if ( timeDiff < 1000) {
      tickleState = HIGH;
      for(int i = 0; i < 3; i++) {
        laugh();
      }
    }
    else {
      tickleState = LOW;
      neutral();
    }          
  }
  delay(100);
  
  //head pat
  if (fsrHeadValue > 50) {  
    happy();
  }
  
  //turning plushie upside down/shake
  if (xValue > 750) {
    sad();
  }
  if (xValue < 600) {
    neutral();
  }
  
  //shake
  if (yPrevious - yValue > 300){
    sad();    
  }
   
  else {
    neutral();
    digitalWrite(vibrate, LOW);
  }
 
}//end loop



void neutral(){ 
  digitalWrite(in1, HIGH);// turn the LED on (HIGH is the voltage level)
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, HIGH);
  digitalWrite(in5, HIGH);
  digitalWrite(outTop, LOW);
  digitalWrite(outBottom, HIGH);
}

void sad(){
  for (int i = 0; i < 2000; i++) {   
    //vibrate!!!     
    digitalWrite(vibrate, HIGH);
    
    digitalWrite(in1, HIGH);// turn the LED on (HIGH is the voltage level)
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    digitalWrite(in5, HIGH);
    digitalWrite(outTop, LOW);
    digitalWrite(outBottom, HIGH);
    delay(1);
   
    digitalWrite(in1, LOW);// turn the LED on (HIGH is the voltage level)
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, HIGH);
    digitalWrite(in5, LOW);
    digitalWrite(outTop, HIGH);
    digitalWrite(outBottom, LOW);
    delay(1); 
     
  }
}

void happy (){
  for (int i = 0; i < 3000; i++) {  
    digitalWrite(in1, HIGH);  
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    digitalWrite(in5, HIGH);
    digitalWrite(outTop, HIGH);
    digitalWrite(outBottom, LOW);
    delay(1); 
    
    digitalWrite(in1, LOW); 
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, HIGH);
    digitalWrite(in5, LOW);
    digitalWrite(outTop, LOW);
    digitalWrite(outBottom, HIGH);
    delay(1);
  }
}

void laugh(){
  t = 0;
  motorSteps = 0;
  
  for (int i = 0; i < 30; i++) {
    while(motorSteps < 30) {        
      pos1 = 0 + motorSteps; // servo1 from 30 to 0 degrees
      pos2 = 30 - motorSteps; // servo2 from 0 to 30 degrees
    
      if(t == 0){
        myservo.write(pos1);
        myservoTwo.write(pos2);
        motorSteps = motorSteps +1; 
      }
    
      t = (t+1) % 10;

      digitalWrite(in1, HIGH);  
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
      digitalWrite(in5, HIGH);
      digitalWrite(outTop, HIGH);
      digitalWrite(outBottom, LOW);
      delay(1); 
      
      digitalWrite(in1, LOW); 
      digitalWrite(in2, HIGH);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, HIGH);
      digitalWrite(in5, LOW);
      digitalWrite(outTop, LOW);
      digitalWrite(outBottom, HIGH);
      delay(1);
    }  
  }
}


