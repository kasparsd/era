#include <Arduino.h>

#define MY_DEBUG
#define MY_RS485
#define MY_RS485_DE_PIN D0
#define MY_RS485_BAUD_RATE 9600
#define MY_RS485_HWSERIAL Serial

// Use the Wemos D1 LED for status.
#define MY_DEFAULT_RX_LED_PIN D4
#define MY_DEFAULT_TX_LED_PIN D4

#include <MySensors.h>

#define CHILD_ID 1

MyMessage msg(CHILD_ID, V_TRIPPED);

bool state = false;

void setup() {
}

void presentation() {
	// Send the sketch version information to the gateway and Controller
	sendSketchInfo("Motion Sensor", "1.0");

	// Register all sensors to gw (they will be created as child devices)
	present(CHILD_ID, S_MOTION);
}

void loop() {
	send(msg.set(state ? "1" : "0"));
	state = state ? false : true;
	delay(5000);
}
 