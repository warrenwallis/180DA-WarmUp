#include <CAN.h>
#include <Adafruit_NeoPixel.h>

const long HOST_ID = 0x000;
const long PLAYERS_ID = 0x001;
const long CAN_BPS = 250000;
const int MESSAGE = 1;
const int WAIT_TIME = 3;
const int GPIO_INPUT = 0;
bool play = false;

Adafruit_NeoPixel strip(1, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

void setup() {
    Serial.begin(9600);

    strip.begin();
    strip.setBrightness(50);

    pinMode(GPIO_INPUT, INPUT);

    if (!CAN.begin(CAN_BPS)) {
        Serial.println("Starting CAN failed");
        while (true);
    }
}

void loop() {
    if (play) {
        if (digitalRead(GPIO_INPUT)) {
            CAN.beginPacket(PLAYERS_ID);
            CAN.write(MESSAGE);
            CAN.endPacket();
        }

        int packetSize = CAN.parsePacket();
        if (packetSize) {
            if (CAN.packetId() == 1) {
                int payload = 0;
                while (CAN.available()) {
                    payload = CAN.read();
                }

                if (payload == 2) {
                    strip.setPixelColor(0, strip.Color(255, 0, 0)); // set LED to red
                    strip.show();
                    Serial.println("Player 2 Wins!");
                }

                play = false;
                delay(3000);

                CAN.beginPacket(HOST_ID);
                CAN.write(MESSAGE);
                CAN.endPacket();
            }
            if (CAN.packetId() == HOST_ID) {
                strip.setPixelColor(0, strip.Color(0, 0, 0)); // set LED to off
                strip.show();
                play = false;
            }
        }
    }
    else { // player's are not available to play yet
        Serial.println("Get Ready!");
        for (int i = 0; i < WAIT_TIME; i++) {
            if (i % 2)
                strip.setPixelColor(0, strip.Color(255, 255, 0)); // set LED to yellow for standby
            else
                strip.setPixelColor(0, strip.Color(0, 0, 0)); // set LED to off for flashing sequence

            strip.show();
            delay(500);
        }

        CAN.beginPacket(HOST_ID);
        CAN.write(MESSAGE);
        CAN.endPacket();

        play = true;
        Serial.println("Go!");
        strip.setPixelColor(0, strip.Color(0, 255, 0)); // set LED to green to alert players game has started
        strip.show();
    }
}
