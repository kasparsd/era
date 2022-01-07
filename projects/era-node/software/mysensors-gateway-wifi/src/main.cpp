#include <Arduino.h>

#define MY_DEBUG
#define MY_RS485
#define MY_RS485_DE_PIN D0
#define MY_RS485_BAUD_RATE 9600
#define MY_RS485_HWSERIAL Serial

#define MY_DEFAULT_ERR_LED_PIN D4 // Error led pin
#define MY_DEFAULT_RX_LED_PIN D4 // Receive led pin
#define MY_DEFAULT_TX_LED_PIN D4 // the PCB, on board LED

#define MY_GATEWAY_ESP8266
#define MY_WIFI_SSID "WIFINAME"
#define MY_WIFI_PASSWORD "WIFIPASSWORD"

#define MY_HOSTNAME "eragateway"
#define MY_PORT 5003

#define MY_SIGNAL_REPORT_ENABLED

#include <MySensors.h>

void setup() {
}

void presentation() {
	sendSketchInfo("Era Gateway", "1.0");
}

void loop() {
}
 