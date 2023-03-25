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
    if (digitalRead(GPIO_INPUT))
        Serial.println("ON");
    else
        Serial.println("OFF");
    delay(1000);
}
