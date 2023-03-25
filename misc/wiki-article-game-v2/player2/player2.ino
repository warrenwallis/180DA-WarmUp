#include <CAN.h>
#include <Adafruit_NeoPixel.h>

const long HOST_ID = 0x000;
const long PLAYERS_ID = 0x001;
const long CAN_BPS = 250000;
const int MESSAGE = 2;
const int WAIT_TIME = 3;
const int GPIO_INPUT = 0;
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
    pinMode(GPIO_INPUT, INPUT);

    if (!CAN.begin(CAN_BPS)) {
        Serial.prinln("Starting CAN failed");
        while (true);
    }
}

void loop() {
    if (play) {
        if (digitalRead(GPIO_INPUT)) {
            CAN.beginPacket(PLAYERS_ID);
            CAN.Write(MESSAGE);
            CAN.endPacket();
        }

        int packetSize = CAN.parsePacket();
        if (packetSize) {
            if (CAN.packetId() == PLAYERS_ID) {
                int payload = 0;
                while (CAN.available()) {
                    payload = CAN.read();
                }

                if (payload == 1) {
                    strip.setPixelColor(0, strip.Color(255, 0, 0)); // set LED to red
                    strip.show();
                    Serial.println("Player 1 Wins!");
                }

                play = false;
                delay(3000);

                CAN.beginPacket(HOST_ID);
                CAN.Write(MESSAGE);
                CAN.endPacket();
            }
            if (CAN.packetID() == HOST_ID) {
                strip.setPixelColor(0, strip.Color(0, 0, 0)); // set LED to off
                strip.show()
                play = false;
            }
        }
    }
    else { // player's are not available to play yet
        int packetSize = CAN.parsePacket();
        if (packetSize && CAN.packetId() == HOST_ID) {
            int payload = 0;
            while (CAN.available()) {
                payload = CAN.read();
            }

            strip.setPixelColor(0, strip.Color(0, 255, 0)); // set LED to green
            strip.show()
            play = true;
        }
    }
}