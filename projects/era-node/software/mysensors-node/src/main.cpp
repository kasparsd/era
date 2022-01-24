#include <Arduino.h>

// Debug output is printed on the RS485 bus too since they share the same UART port.
#define MY_DEBUG
#define MY_BAUD_RATE 9600
#define MY_DISABLED_SERIAL // Disable debug output to allow using UART0 for RS485.

// These must be hardcoded because MySensors version 2.3.2 has a bug
// that prevents the node ID assignment, see https://github.com/mysensors/MySensors/issues/1450
#define MY_NODE_ID 1
#define MY_PARENT_NODE_ID 0 // Don't attempt to find it.
#define MY_PARENT_NODE_IS_STATIC // If the controller doesn't support returning the parent node.

#define MY_RS485
#define MY_RS485_DE_PIN D0
#define MY_RS485_BAUD_RATE 9600
#define MY_RS485_HWSERIAL Serial
#define MY_RS485_SOH_COUNT 3 // Avoid collisions on the RS485 bus.

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
	wait(1000);
}
 