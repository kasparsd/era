#include <Arduino.h>
#include <PJONThroughSerial.h>

PJONThroughSerial bus(45);

void setup() {
  Serial.begin(9600);

  bus.strategy.set_serial(&Serial);
  bus.strategy.set_enable_RS485_pin(D0);

  bus.set_acknowledge(false);
  bus.begin();
  
  bus.send_repeatedly(44, "B", 1, 1500000); // Send B to device 44 every 1.5s
}

void loop() {
  bus.update();
}
