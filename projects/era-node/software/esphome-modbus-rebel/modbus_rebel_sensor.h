#pragma once

#include "esphome.h"
#include <OneButton.h>

class ModbusRebelSensor : public Component, public Sensor {
  private:
    Modbus *modbus;
    OneButton button;

    void send_state(uint8_t state) {
      std::vector<uint8_t> payload;

      payload.push_back(state);

      modbus->send(
        3, // uint8_t address
        0x06, // uint8_t function_code - WRITE_SINGLE_REGISTER
        6, // uint16_t start_address
        1, // uint16_t number_of_entities
        payload.size(), // uint8_t payload_len = 0
        &payload[0] // const uint8_t *payload = nullptr
      );

      publish_state(state);
    }

  public:
    ModbusRebelSensor(Modbus *modbus, uint8_t button_pin) {
      this->modbus = modbus;
      this->button = OneButton(button_pin, true, true);
    }

    static void onSingleClick(void *ptr) {
      ModbusRebelSensor *thingPtr = (ModbusRebelSensor *)ptr;
      thingPtr->send_state(1);
    }

    static void onDoubleClick(void *ptr) {
      ModbusRebelSensor *thingPtr = (ModbusRebelSensor *)ptr;
      thingPtr->send_state(33);
    }

    void setup() override {
      this->button.attachDuringLongPress(onDoubleClick, this);
      this->button.attachClick(onSingleClick, this);
    }

    void loop() override {
      this->button.tick();
    }
};
