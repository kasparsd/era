/*
  ModbusRTU ESP8266/ESP32
  Simple slave example
  (c)2019 Alexander Emelianov (a.m.emelianov@gmail.com)
  https://github.com/emelianov/modbus-esp8266
  modified 13 May 2020
  by brainelectronics
  This code is licensed under the BSD New License. See LICENSE.txt for more info.
*/

#ifdef ESP8266
 #include <ESP8266WiFi.h>
#else	// ESP32
 #include <WiFi.h>
#endif

#define MODBUSRTU_DEBUG

#include <ModbusRTU.h>

#include <SoftwareSerial.h>

#define REG_STR_LEN 20

// Modbus holding registers
#define REG_WIFI_SSID 10
#define REG_WIFI_PASSWORD 30

#define COIL_WIFI_CONNECT 10

#define SLAVE_ID 1

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 1000;

SoftwareSerial SoftSerial(D1, D2); // RX, TX

ModbusRTU mb;

uint16_t cbSetHregWifiSsid(TRegister* reg, uint16_t val) {
  Serial.print("Write. Reg RAW#: ");
  Serial.print(reg->address.address);
  Serial.print(" Old: ");
  Serial.print(reg->value);
  Serial.print(" New: ");
  Serial.println(val);

  return val;
}

uint16_t cbSetCoilWifiConnect(TRegister* reg, uint16_t val) {
  char ssid_from_reg[REG_STR_LEN];
  char password_from_reg[REG_STR_LEN];

  for (uint8_t i = 0; i < REG_STR_LEN; i++) {
    ssid_from_reg[i] = mb.Hreg(REG_WIFI_SSID + i);
    password_from_reg[i] = mb.Hreg(REG_WIFI_PASSWORD + i);
  }

  Serial.printf( "Connecting to SSID '%s' with password '%s'", ssid_from_reg, password_from_reg );

  if (COIL_BOOL(val)) {
    Serial.println("Would attempt to connect");
  
    WiFi.begin(String(ssid_from_reg), String(password_from_reg));

    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }

    Serial.println("WiFi connected");  
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  } else if ( WiFi.isConnected() ) {
    Serial.println("Would attempt to disconnect");
    WiFi.disconnect();
  }

  return val;
}

uint8_t frame[] = "What?";
uint8_t frame_len = 6;

void setup() {
  // Serial for debugging.
  Serial.begin(9600, SERIAL_8N1);

  // Setup the Serial for RS485 communication.
  SoftSerial.begin(9600);

  mb.begin(&SoftSerial, D0);

  mb.slave(SLAVE_ID);

  // Register: WiFi SSID
  mb.addHreg(REG_WIFI_SSID, 0, REG_STR_LEN);
  mb.onSetHreg(REG_WIFI_SSID, cbSetHregWifiSsid, REG_STR_LEN);

  // Register: WiFi passphrase.
  mb.addHreg(REG_WIFI_PASSWORD, 0, REG_STR_LEN);

  // WiFi connect coil.
  mb.addCoil(COIL_WIFI_CONNECT, false);
  mb.onSetCoil(COIL_WIFI_CONNECT, cbSetCoilWifiConnect);
}

void loop() {
  mb.task();

  if ((millis() - lastDebounceTime) > debounceDelay) {
    Serial.println("Bouncing");
    mb.rawSend(0, frame, frame_len);
    Serial.println("Wrote");
    lastDebounceTime = millis();
  }
}