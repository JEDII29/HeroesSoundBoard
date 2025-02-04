#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_MCP23X17.h>
#include "DFRobotDFPlayerMini.h"

void writeMCP23S17Register(uint8_t reg, uint8_t value) {
    digitalWrite(5, LOW); // Aktywacja MCP23S17 (CS LOW)
    SPI.transfer(0x40);   // OPCODE: MCP23S17 (A2,A1,A0 = 0) + WRITE (0x40)
    SPI.transfer(reg);    // Wybór rejestru
    SPI.transfer(value);  // Zapis wartości
    digitalWrite(5, HIGH); // Dezaktywacja MCP23S17 (CS HIGH)
}

uint8_t readMCP23S17Register(uint8_t reg) {
    digitalWrite(5, LOW); // Aktywacja MCP23S17 (CS LOW)
    SPI.transfer(0x41);   // OPCODE: MCP23S17 (A2,A1,A0 = 0) + READ (0x41)
    SPI.transfer(reg);    // Wybór rejestru
    uint8_t value = SPI.transfer(0x00); 
    digitalWrite(5, HIGH);
    return value;
}

void debugMCP23S17() {
    Serial.print("IODIRA: ");
    Serial.println(readMCP23S17Register(0x00), BIN);

    Serial.print("GPPUA: ");
    Serial.println(readMCP23S17Register(0x0C), BIN);

    Serial.print("OLATA: ");
    Serial.println(readMCP23S17Register(0x14), BIN);

    Serial.print("GPIOA: ");
    Serial.println(readMCP23S17Register(0x12), BIN);
}

Adafruit_MCP23X17 mcp;
HardwareSerial mySerial(2);
DFRobotDFPlayerMini dfPlayer;
bool flag = false;
void setup() {
    Serial.begin(115200);
    mySerial.begin(9600, SERIAL_8N1, 16, 17);
    SPI.begin(18, 19, 23, 5);

    if (!mcp.begin_SPI(5, &SPI, 0b000)) {
        Serial.println("Błąd: MCP23S17 nie został wykryty!");
        while (1);
    }
    writeMCP23S17Register(0x0A, 0x00);
    Serial.println("MCP23S17 wykryty!");

    Serial.println("Debugowanie MCP23S17...");
    debugMCP23S17();
    
    for (int i = 0; i <= 15; i++) {

        mcp.pinMode(i, INPUT_PULLUP);
    }

    Serial.println("Inicjalizacja DFPlayer...");

    if (!dfPlayer.begin(mySerial)) { 
        Serial.println("Błąd komunikacji z DFPlayer!");
        while (true);
    }
    Serial.println("DFPlayer Mini gotowy!");
    dfPlayer.volume(15);
}

void loop() {
    if (Serial.available()) {
            String command = Serial.readStringUntil('\n');
            command.trim();

            if (command == "play") {
                Serial.println("Odtwarzanie...");
                dfPlayer.start();
            } 
            else if (command == "stop") {
                Serial.println("Zatrzymanie...");
                dfPlayer.pause();
            } 
            else if (command == "up") {
                int vol = dfPlayer.readVolume();
                if (vol < 30) dfPlayer.volume(vol + 1);
                Serial.print("Głośność: "); Serial.println(dfPlayer.readVolume());
            } 
            else if (command == "down") {
                int vol = dfPlayer.readVolume();
                if (vol > 0) dfPlayer.volume(vol - 1);
                Serial.print("Głośność: "); Serial.println(dfPlayer.readVolume());
            } 
            else {
                Serial.println("Nieznana komenda! Użyj: play, stop, up, down");
            }
    }
    
        uint8_t pin1 = mcp.digitalRead(8);
        uint8_t pin2 = mcp.digitalRead(9);
        uint8_t pin3 = mcp.digitalRead(10);
        uint8_t pin4 = mcp.digitalRead(11);
        if(flag == false)
        {
            if(pin1 == 0 )
                dfPlayer.play();
            if(pin2 == 0)
                dfPlayer.stop();
            if(pin3 == 0)
                dfPlayer.next();
            if(pin4 == 0)
                dfPlayer.previous();
            
            flag = true;
        }
        if(pin1 == 1 && pin2 == 1 && pin3 == 1 && pin4 == 1)
            flag = false;
    
    delay(500);
}