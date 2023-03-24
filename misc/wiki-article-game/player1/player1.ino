#include <CAN.h>

// Code for player 1

void setup() {
    Serial.begin(9600);

    if (!CAN.begin(250000)) {
        Serial.println("Starting CAN failed");
        while (true);
    }
}

void loop() {

}