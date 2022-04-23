#include "esphome.h"

class MyCustomSwitch : public Component, public Switch {
  private:
    Modbus *modbusApi;

  public:
    MyCustomSwitch(Modbus *modbusComponent) : modbusApi(modbusComponent) {}

    void write_state(bool state) override {
      std::vector<uint8_t> payload;

      payload.push_back(state);

      // uint8_t address,
      // uint8_t function_code, 
      // uint16_t start_address, 
      // uint16_t number_of_entities,
      // uint8_t payload_len = 0,
      // const uint8_t *payload = nullptr
      modbusApi->send(3, 5, 6, 1, payload.size(), &payload[0]);

      // Acknowledge new state by publishing it.
      publish_state(state);
    }
};
