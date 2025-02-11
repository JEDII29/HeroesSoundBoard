
#include "DFPlayerMini_ESP32.h"
#include "MCP23S17_ESP32.h"

DFPlayerMini_ESP32 myMusicPlayer;
Adafruit_MCP23S17_ESP32 myExpander;

int8_t pressed = -1;
int8_t last_pressed = -1;

int8_t pin_track_offset = 7; //numer najnizszego pinu minus 1
bool pressedFlag = false;

void IRAM_ATTR handleMCPInterrupt() {
  pressedFlag = true;
}
void setup()
{
  Serial.begin(115200);

  if(!myMusicPlayer.begin()) {
    Serial.println("Unable to initialize Music Player!");
    while(1) delay(100);
  }
  Serial.println("Music Player online.");

  if(!myExpander.begin()) {
    Serial.println("Unable to initialize Expander!");
    while(1) delay(100);
  }
  Serial.println("Expander online.");
}

void loop()
{
  if (myMusicPlayer.available()) {
    Serial.println(myMusicPlayer.getMessage());
  }

  pressed = myExpander.getPressedButton();
  if (pressed > -1 && pressed != last_pressed) {
    myMusicPlayer.play(pressed-pin_track_offset);
    last_pressed = pressed;
  }
  
  delay(50);
}

