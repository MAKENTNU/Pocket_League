#include "RF24.h"

// V A R I A B L E S
int sendArray[6];

int sendArray2[6];

// P I N S
int pinLeft = 2;
int pinRight = 3;
int pinUp = 7;
int pinDown = 5;
int pinTrigger = 4;
int pinTriggerUp = 6;

RF24 radio(9, 10); 

const uint64_t pipe = 0xE6E6E6E6E6E6; // Needs to be the same for communicating between 2 NRF24L01 

void setup(void){
    Serial.begin(9600);
    Serial.println("Startup");

    pinMode(pinLeft, INPUT_PULLUP);
    pinMode(pinRight, INPUT_PULLUP);
    pinMode(pinUp, INPUT_PULLUP);
    pinMode(pinDown, INPUT_PULLUP);
    pinMode(pinTrigger, INPUT_PULLUP);
    pinMode(pinTriggerUp, INPUT_PULLUP);

    if (!radio.begin()) {
      Serial.println("Begin false!!");
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
      sendArray[0] = 10;
    }
    if(!digitalRead(pinRight)){
      sendArray[1] = 10;
    }
    if(!digitalRead(pinUp)){
      sendArray[2] = 10;
    }
    if(!digitalRead(pinDown)){
      sendArray[3] = 10;
    }
    if(!digitalRead(pinTrigger)){
      sendArray[4] = 10;
    }
    if(!digitalRead(pinTriggerUp)){
      sendArray[5] = 10;
    }

    
    Serial.print(sendArray[0]);
    Serial.println(" left ");
    Serial.print(sendArray[1]);
    Serial.println(" right ");
    Serial.print(sendArray[2]);
    Serial.println(" Up ");
    Serial.print(sendArray[3]);
    Serial.println(" down ");
    Serial.print(sendArray[4]);
    Serial.println(" TRIGGER ");
    Serial.print(sendArray[5]);
    Serial.println(" pinTriggerUp ");
    

    radio.write(&sendArray, sizeof(sendArray));
    delay(750);

}
