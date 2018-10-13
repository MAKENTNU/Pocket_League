#include <RF24.h>

// Seting up the radio
RF24 radio(9, 10);
// This pipe vaiable needs to be the same on the controller and car to communicate
const uint64_t pipe = 0xE6E6E6E6E6E6; 

// V A R I A B L E S
int sendArray[6];

// P I N S

// Driving pins
int pinLeft = 2;
int pinRight = 3;
int pinUp = 7;
int pinDown = 5;

// Alternative pins
int pinTriggerDown = 4;
int pinTriggerUp = 6;


void setup(void){
    Serial.begin(9600); // Serial print speed
    Serial.println("Startup");

    // Setting pin mode
    pinMode(pinLeft, INPUT_PULLUP);
    pinMode(pinRight, INPUT_PULLUP);
    pinMode(pinUp, INPUT_PULLUP);
    pinMode(pinDown, INPUT_PULLUP);
    pinMode(pinTriggerDown, INPUT_PULLUP);
    pinMode(pinTriggerUp, INPUT_PULLUP);

    // Checking if the radio starts
    if (!radio.begin()) {
      Serial.println("Radio failed!");
    } else {
      Serial.println("Radio started");
    }
    radio.setChannel(95);
    radio.openWritingPipe(pipe); 
}

void loop(void) {
    sendArray[0] = 0;
    sendArray[1] = 0;
    sendArray[2] = 0;
    sendArray[3] = 0;
    sendArray[4] = 0;
    sendArray[5] = 0;
    if (!digitalRead(pinLeft)){
      sendArray[0] = 1;
    }
    if(!digitalRead(pinRight)){
      sendArray[1] = 1;
    }
    if(!digitalRead(pinUp)){
      sendArray[2] = 1;
    }
    if(!digitalRead(pinDown)){
      sendArray[3] = 1;
    }
    if(!digitalRead(pinTriggerDown)){
      sendArray[4] = 1;
    }
    if(!digitalRead(pinTriggerUp)){
      sendArray[5] = 1;
    }

    /*
    Serial.print(sendArray[0]);
    Serial.println(" left ");
    Serial.print(sendArray[1]);
    Serial.println(" right ");
    Serial.print(sendArray[2]);
    Serial.println(" Up ");
    Serial.print(sendArray[3]);
    Serial.println(" down ");
    Serial.print(sendArray[4]);
    Serial.println(" pinTriggerDown ");
    Serial.print(sendArray[5]);
    Serial.println(" pinTriggerUp ");
    */

    radio.write(&sendArray, sizeof(sendArray));
    //delay(150);

}
