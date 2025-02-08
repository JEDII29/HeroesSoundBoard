#ifndef MCP23S17_ESP32
#define MCP23S17_ESP32

#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_MCP23X17.h>

class Adafruit_MCP23S17_ESP32 : public Adafruit_MCP23X17 {
  public:
    Adafruit_MCP23S17_ESP32();
    bool begin();
    void writeRegister(uint8_t, uint8_t);
    uint8_t readRegister(uint8_t);
    int8_t getPressedButton();
  private:
    static const uint8_t button_pins[4];

};

#endif // MCP23S17_ESP32