#include "MCP23S17_ESP32.h"

Adafruit_MCP23S17_ESP32::Adafruit_MCP23S17_ESP32() {}

const uint8_t Adafruit_MCP23S17_ESP32::button_pins[4] = {8,9,10,11};

bool Adafruit_MCP23S17_ESP32::begin() {
    SPI.begin(18, 19, 23, 5);

    bool ret = begin_SPI(5, &SPI, 0b000);

    writeRegister(0x0A, 0x00);

    for (uint8_t pin : button_pins) {
        pinMode(pin, INPUT_PULLUP);
    }

    return ret;
}

void Adafruit_MCP23S17_ESP32::writeRegister(uint8_t reg, uint8_t value) {
    digitalWrite(5, LOW); // aktywacja nasłuchiwania SPI
    SPI.transfer(0x40);   // OPCODE - adres urządzenia + write
    SPI.transfer(reg);    // Wybór rejestru
    SPI.transfer(value);  // Zapis wartości
    digitalWrite(5, HIGH); // Dezaktywacja MCP23S17 (CS HIGH)
}

uint8_t Adafruit_MCP23S17_ESP32::readRegister(uint8_t reg) {
    digitalWrite(5, LOW); // Aktywacja nasłuchiwania SPI
    SPI.transfer(0x41);   // OPCODE - adres urządzenia + read
    SPI.transfer(reg);    // Wybór rejestru
    uint8_t value = SPI.transfer(0x00); // Odczyt wartości
    digitalWrite(5, HIGH);
    return value;
}

int8_t Adafruit_MCP23S17_ESP32::getPressedButton() {
    for (uint8_t pin : button_pins) {
        if (digitalRead(pin) < 1) { // Przycisk wciśnięty (stan LOW)
            return pin;
        }
    }
    return -1; // Żaden przycisk nie jest wciśnięty
}

