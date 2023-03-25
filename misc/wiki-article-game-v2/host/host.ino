#include <CAN.h>
#include <Adafruit_NeoPixel.h>

const long HOST_ID = 0x000;
const long PLAYERS_ID = 0x001;
const long CAN_BPS = 250000;
const int MESSAGE = 1;
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
    if (digitalRead(GPIO_INPUT))
        Serial.println("ON");
    else
        Serial.println("OFF");
    delay(1000);
}