#include <CAN.h>

const long HOST_ID = 0x000;
const long PLAYERS_ID = 0x001;
const long CAN_BPS = 250000
const int NUM_PLAYERS = 2;
const int WAIT_TIME= 5;
bool play = false;

void setup() {
    Serial.Begin(9600);
    Serial.println("Welcome, to \'CAN You Press Fast Enough\'");

}

void loop() {
    if (play) {
        int packetSize = CAN.parsePacket();
        if (packetSize && CAN.packetId() == 1) {
            int payload = 0;
            while (CAN.available()) {
                payload = CAN.read();
            }

            Serial.print("Winner is: Player ");
            Serial.println(payload);

            play = false;
        }
    }
    else { // player's are not available to play yet
        Serial.println("Get Ready!")
        delay(1000);
        for (int i = 0; i < WAIT_TIME; i++) {
            Serial.print(i);
            Serial.print(" ");
        }

        CAN.beginPacket(HOST_ID);
        CAN.Write(1);
        CAN.endPacket();

        play = true;
        Serial.println("Go!")
    }

    
}