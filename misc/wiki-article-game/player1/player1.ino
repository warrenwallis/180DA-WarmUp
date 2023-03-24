#include <CAN.h>

// Code for player 1

const long HOST_ID = 0x000;
const long PLAYERS_ID = 0x001;
const long CAN_BPS = 250000
const int NUM_PLAYERS = 2;
const int WAIT_TIME= 5;
bool play = false;

void setup() {
    Serial.Begin(9600);

    pinMode(PIN_CAN_STANDBY, OUTPUT);
    digitalWrite(PIN_CAN_STANDBY, false);
    pinMode(PIN_CAN_BOOSTEN, OUTPUT);
    digitalWrite(PIN_CAN_BOOSTEN, true);
    pinMode(0, INPUT);

    if (!CAN.begin(CAN_BPS)) {
        Serial.println("Starting CAN failed");
        while(true);
    }
}

void loop() {
    if (play) {
        
    }
    else { // player's are not available to play yet
        int packetSize = CAN.parsePacket();
        if (packetSize && CAN.packetId() == HOST_ID) {
            int payload = 0;
            while (CAN.available()) {
                payload = CAN.read();
            }

            if (payload == 1)
                play = true;
        }
    }

    
}