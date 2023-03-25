#include <CAN.h>
#include <Adafruit_NeoPixel.h>

const long HOST_ID = 0x000;
const long PLAYERS_ID = 0x001;
const long CAN_BPS = 250000;
const int MESSAGE = 1;
const int WAIT_TIME= 3;
bool play = false;

Adafruit_Neopixel strip(1, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

void setup() {
    Serial.Begin(9600);

    strip.begin();
    strip.setBrightness(50);

    pinMode(PIN_CAN_STANDBY, OUTPUT);
    digitalWrite(PIN_CAN_STANDBY, false);
    pinMode(PIN_CAN_BOOSTEN, OUTPUT);
    digitalWrite(PIN_CAN_BOOSTEN, true);
    pinMode(0, INPUT);

    if (!CAN.begin(CAN_BPS)) {
        Serial.prinln("Starting CAN failed");
        while (true);
    }
}

void loop() {
    if (play) {
        int packetSize = CAN.parsePacket();
        if (packetSize && CAN.packetId() == 1) {
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
        }
    }
    else { // player's are not available to play yet
        Serial.println("Get Ready!")
        for (int i = 0; i < WAIT_TIME; i++) {
            if (i % 2)
                strip.setPixelColor(0, strip.Color(255, 255, 0)); // set LED to yellow for standby
            else
                strip.setPixelColor(0, strip.Color(0, 0, 0)); // set LED to off for flashing sequence

            strip.show();
            delay(500);
        }

        CAN.beginPacket(HOST_ID);
        CAN.Write(1);
        CAN.endPacket();

        play = true;
        Serial.println("Go!");
        strip.setPixelColor(0, strip.Color(0, 255, 0)); // set LED to green to alert players game has started
        strip.show();
    }
}