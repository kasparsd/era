#pragma once

#include "esphome.h"

class ModbusRebelSwitch : public Component, public Switch {
  private:
    Modbus *modbus;

  public:
    ModbusRebelSwitch(Modbus *modbus) {
      this->modbus = modbus;
    }

    void write_state(bool state) override {
      std::vector<uint8_t> payload;

      payload.push_back(state);

      // TODO: Ensure that UART is silent for X ms before sending.
      modbus->send(
        3, // uint8_t address
        0x05, // uint8_t function_code - WRITE_SINGLE_COIL
        6, // uint16_t start_address
        1, // uint16_t number_of_entities
        payload.size(), // uint8_t payload_len = 0
        &payload[0] // const uint8_t *payload = nullptr
      );

      // Acknowledge new state by publishing it.
      publish_state(state);
    }
};
