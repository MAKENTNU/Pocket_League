#include "RF24.h" // NRF24L01 library created by TMRh20 https://github.com/TMRh20/RF24
#include <Servo.h>

Servo myservo;

/* Arduino / Radio code*/
RF24 radio(9, 10);
const uint64_t pipe = 0xE6E6E6E6E6E6;

// V A R I A B L E S
int movement[6];

int left = 0;
int right = 0;
int forward = 0;
int back = 0;
int servoUp = 0;
int servoDown = 0;

int iter = 0;
int pos = 0;

long int currentTime = 0;
long int lastCall = 0;

// P I N S
int LEFT_ENABLE = 3;
int LEFT_FORWARD = 4;
int LEFT_BACKWARD = 5;
int RIGHT_ENABLE = 6;
int RIGHT_FORWARD = 8;
int RIGHT_BACKWARD = 7;
int SERVO_PIN = 2;

void setup(void) {
    Serial.begin(9600);
    Serial.println("Startup");
    
   if (!radio.begin()) {
      Serial.println("Begin false!!");
    } else {
      Serial.println("Stash");
    }
    radio.setChannel(95);
    radio.openReadingPipe(1, pipe); // Get NRF24L01 ready to receive
    radio.startListening(); // Listen to see if information received

    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);

    myservo.attach(SERVO_PIN);
    
}
void(* resetFunc) (void) = 0; //declare reset function at address 0

void loop(void) {

  currentTime = millis();
  
    while (radio.available()) {
    radio.read(&movement, sizeof(movement));
      lastCall = millis();
        //for(int i = 0;i<sizeof(movement);i++){
        //   Serial.print(movement[i]);
        //}
    }
    
    left = movement[0];
    right = movement[1];
    forward = movement[2];
    back = movement[3];
    
    servoDown = movement[4];
    servoUp = movement[5];
    
    if (currentTime-lastCall > 1000){
      left = 0;
      right = 0;
      forward = 0;
      back = 0;
      servoDown = 0;
      servoUp = 0;
      if (currentTime-lastCall > 4000){
        resetFunc(); //call reset 
      }
    }
    
    if (servoDown == 10){
      Serial.println("servo down");
      myservo.attach(SERVO_PIN);
      pos = 10;
      myservo.write(pos); 
    }
    else if(servoUp == 10){
      Serial.println("servo up");
      myservo.attach(SERVO_PIN);
      pos = 170;
      myservo.write(pos); 
    }
    else{
      myservo.detach();
    }
    
    if(forward == 10 && (left == 10 || right == 10)){
      //Serial.println("forward X");
      digitalWrite(RIGHT_FORWARD, HIGH);
      digitalWrite(RIGHT_BACKWARD, LOW);
      analogWrite(RIGHT_ENABLE, 255 - right * 15);
      digitalWrite(LEFT_FORWARD, HIGH);
      digitalWrite(LEFT_BACKWARD, LOW);
      analogWrite(LEFT_ENABLE, 255 - left * 15);
    }
    else if(forward == 10){
      //Serial.println("forward");
      digitalWrite(RIGHT_FORWARD, HIGH);
      digitalWrite(RIGHT_BACKWARD, LOW);
      analogWrite(RIGHT_ENABLE, 255);
      digitalWrite(LEFT_FORWARD, HIGH);
      digitalWrite(LEFT_BACKWARD, LOW);
      analogWrite(LEFT_ENABLE, 255);
    }
    else if(back == 10){ 
      Serial.println("back");
      digitalWrite(RIGHT_FORWARD, LOW);
      digitalWrite(RIGHT_BACKWARD, HIGH);
      analogWrite(RIGHT_ENABLE, 255);
      digitalWrite(LEFT_FORWARD, LOW);
      digitalWrite(LEFT_BACKWARD, HIGH);
      analogWrite(LEFT_ENABLE, 255);
    }
     else if(left == 10){ 
      Serial.println("left");
      digitalWrite(RIGHT_FORWARD, HIGH);
      digitalWrite(RIGHT_BACKWARD, LOW);
      analogWrite(RIGHT_ENABLE, 255);
      digitalWrite(LEFT_FORWARD, LOW);
      digitalWrite(LEFT_BACKWARD, HIGH);
      analogWrite(LEFT_ENABLE, 255);
    }
     else if(right == 10){ 
      Serial.println("right");
      digitalWrite(RIGHT_FORWARD, LOW);
      digitalWrite(RIGHT_BACKWARD, HIGH);
      analogWrite(RIGHT_ENABLE, 255);
      digitalWrite(LEFT_FORWARD, HIGH);
      digitalWrite(LEFT_BACKWARD, LOW);
      analogWrite(LEFT_ENABLE, 255);
    }
     else { 
      digitalWrite(RIGHT_FORWARD, LOW);
      digitalWrite(RIGHT_BACKWARD, LOW);
      analogWrite(RIGHT_ENABLE, 0);
      digitalWrite(LEFT_FORWARD, LOW);
      digitalWrite(LEFT_BACKWARD, LOW);
      analogWrite(LEFT_ENABLE, 0);
    }
}

void servo(){
   for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}


