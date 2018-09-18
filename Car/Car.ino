#include "RF24.h" // NRF24L01 library created by TMRh20 https://github.com/TMRh20/RF24

// Seting up some radio pins
RF24 radio(9, 10);
// This pipe variable needs to be the same on the controller and car to communicate
const uint64_t pipe = 0xE6E6E6E6E6E6;

// V A R I A B L E S
int movement[6];

int left = 0;
int right = 0;
int forward = 0;
int back = 0;
int servoUp = 0;
int servoDown = 0;

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
    Serial.begin(9600); // Serial print speed
    Serial.println("Startup");

    // Setting pin mode
    pinMode(LEFT_ENABLE, OUTPUT);
    pinMode(LEFT_FORWARD, OUTPUT);
    pinMode(LEFT_BACKWARD, OUTPUT);
    pinMode(RIGHT_ENABLE, OUTPUT);
    pinMode(RIGHT_FORWARD, OUTPUT);
    pinMode(RIGHT_BACKWARD, OUTPUT);
    pinMode(SERVO_PIN, OUTPUT);

   // Checking if the radio starts
   if (!radio.begin()) {
      Serial.println("Begin false!!");
    } else {
      Serial.println("Stash");
    }
    radio.setChannel(95);
    radio.openReadingPipe(1, pipe); // Get NRF24L01 ready to receive
    radio.startListening(); // Listen to see if information received


}

void loop(void) {
    currentTime = millis(); // saves current time
    
    while (radio.available()) { // Starts communication
    radio.read(&movement, sizeof(movement)); // Saves the received data in movement
      lastCall = millis(); // Updates the time of last communication
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

    // Checks if car lost communication with controller
    if (currentTime-lastCall > 1000){
      left = 0;
      right = 0;
      forward = 0;
      back = 0;
      servoDown = 0;
      servoUp = 0;
    }
    
    if(forward == 1 && (left == 1 || right == 1)){
      //Serial.println("forward X");
      digitalWrite(RIGHT_FORWARD, HIGH);
      digitalWrite(RIGHT_BACKWARD, LOW);
      analogWrite(RIGHT_ENABLE, 255 - right * 15);
      digitalWrite(LEFT_FORWARD, HIGH);
      digitalWrite(LEFT_BACKWARD, LOW);
      analogWrite(LEFT_ENABLE, 255 - left * 15);
    }
    else if(forward == 1){
      //Serial.println("forward");
      digitalWrite(RIGHT_FORWARD, HIGH);
      digitalWrite(RIGHT_BACKWARD, LOW);
      analogWrite(RIGHT_ENABLE, 255);
      digitalWrite(LEFT_FORWARD, HIGH);
      digitalWrite(LEFT_BACKWARD, LOW);
      analogWrite(LEFT_ENABLE, 255);
    }
    else if(back == 1){ 
      Serial.println("back");
      digitalWrite(RIGHT_FORWARD, LOW);
      digitalWrite(RIGHT_BACKWARD, HIGH);
      analogWrite(RIGHT_ENABLE, 255);
      digitalWrite(LEFT_FORWARD, LOW);
      digitalWrite(LEFT_BACKWARD, HIGH);
      analogWrite(LEFT_ENABLE, 255);
    }
     else if(left == 1){ 
      Serial.println("left");
      digitalWrite(RIGHT_FORWARD, HIGH);
      digitalWrite(RIGHT_BACKWARD, LOW);
      analogWrite(RIGHT_ENABLE, 255);
      digitalWrite(LEFT_FORWARD, LOW);
      digitalWrite(LEFT_BACKWARD, HIGH);
      analogWrite(LEFT_ENABLE, 255);
    }
     else if(right == 1){ 
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


