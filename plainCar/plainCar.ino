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
  
    while (radio.available()) { // Starts communication
    radio.read(&movement, sizeof(movement)); // Saves the received data in movement
    }
    
    left = movement[0];
    right = movement[1];
    forward = movement[2];
    back = movement[3];
    
    if(forward == 1){
      //Serial.println("forward X");
      digitalWrite(RIGHT_FORWARD, HIGH);
      digitalWrite(RIGHT_BACKWARD, LOW);
      analogWrite(RIGHT_ENABLE, 255);
      digitalWrite(LEFT_FORWARD, HIGH);
      digitalWrite(LEFT_BACKWARD, LOW);
      analogWrite(LEFT_ENABLE, 255);
    }
}


