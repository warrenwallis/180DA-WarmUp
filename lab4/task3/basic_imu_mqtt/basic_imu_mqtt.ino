#include <WiFi.h>
#include <PubSubClient.h>
#include "arduino_secrets.h"
#include <Adafruit_BNO08x.h>

// For SPI mode, we need a CS pin
#define BNO08X_CS 10
#define BNO08X_INT 9

// For SPI mode, we also need a RESET 
//#define BNO08X_RESET 5
// but not for I2C or UART
#define BNO08X_RESET -1

Adafruit_BNO08x  bno08x(BNO08X_RESET);
sh2_SensorValue_t sensorValue;

// WiFi
const char *ssid = SECRET_SSID; // Enter your WiFi name
const char *password = SECRET_PASS;  // Enter WiFi password

// MQTT Broker
// const char *mqtt_broker = "broker.emqx.io";
// const char *topic = "ece180d/test";
// const char *mqtt_username = "emqx";
// const char *mqtt_password = "public";
// const int mqtt_port = 1883;

// MQTT Broker
const char *mqtt_broker = "mqtt.eclipseprojects.io";
const char *topic = "ece180d/warren";
// const char *mqtt_username = "emqx";
// const char *mqtt_password = "public";
const int mqtt_port = 1883;

int counter = 0;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
 // Set software serial baud to 115200;
	Serial.begin(115200);
	while (!Serial) delay(10); // delay until serial is connected
	// connecting to a WiFi network
	
	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED) {
			delay(500);
			Serial.println("Connecting to WiFi..");
	}
	Serial.println("Connected to the WiFi network");
	//connecting to a mqtt broker
	client.setServer(mqtt_broker, mqtt_port);
	client.setCallback(callback);
	while (!client.connected()) {
			String client_id = "esp32-client-";
			client_id += String(WiFi.macAddress());
			Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());
			if (client.connect(client_id.c_str())) { //, mqtt_username, mqtt_password)) {
					Serial.println("mqtt broker connected");
			} else {
					Serial.print("failed with state ");
					Serial.print(client.state());
					delay(2000);
			}
	}
	// publish and subscribe
	client.publish(topic, "Hi I'm ESP32");
	//client.subscribe(topic);

	// give power to IMU
	pinMode(TFT_I2C_POWER, OUTPUT);
	digitalWrite(TFT_I2C_POWER, HIGH);
	// Try to initialize!
	if (!bno08x.begin_I2C()) {
	//if (!bno08x.begin_UART(&Serial1)) {  // Requires a device with > 300 byte UART buffer!
	//if (!bno08x.begin_SPI(BNO08X_CS, BNO08X_INT)) {
		Serial.println("Failed to find BNO08x chip");
		while (1) { delay(10); }
	}
	Serial.println("BNO08x Found!");
	setReports();
}

void callback(char *topic, byte *payload, unsigned int length) {
	Serial.print("Message arrived in topic: ");
	Serial.println(topic);
	Serial.print("Message:");
	for (int i = 0; i < length; i++) {
		Serial.print((char) payload[i]);
	}
	Serial.println();
	Serial.println("-----------------------");
}

// Here is where you define the sensor outputs you want to receive
void setReports(void) {
  Serial.println("Setting desired reports");
  if (! bno08x.enableReport(SH2_GAME_ROTATION_VECTOR)) {
    Serial.println("Could not enable game vector");
  }
}

void loop()
{
  counter += 1;
	if (! bno08x.getSensorEvent(&sensorValue)) {
    return;
  }
  String output = "", current = "";
	if (counter % 500 == 0) {
	  switch (sensorValue.sensorId) {
      case SH2_GAME_ROTATION_VECTOR:
        current = "Game Rotation Vector - r: ";
        output += current;
        Serial.print(current);
        current = sensorValue.un.gameRotationVector.real;
        output += current;
        Serial.print(current);
        current = " i: ";
        output += current;
        Serial.print(current);
        current = sensorValue.un.gameRotationVector.i;
        output += current;
        Serial.print(current);
        current = " j: ";
        output += current;
        Serial.print(current);
        current = sensorValue.un.gameRotationVector.j;
        output += current;
        Serial.print(current);
        current = " k: ";
        output += current;
        Serial.print(current);
        current = sensorValue.un.gameRotationVector.k;
        output += current;
        Serial.println(current);
        client.publish(topic, output.c_str());
        break;
    }  
	}
}
