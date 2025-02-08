#ifndef DFPLAYERMINI_ESP32
#define DFPLAYERMINI_ESP32

#include <DFRobotDFPlayerMini.h>

class DFPlayerMini_ESP32 : public DFRobotDFPlayerMini {
  public:
    DFPlayerMini_ESP32();
    bool begin();
    String getMessage();
  private:
    HardwareSerial mySerial;
};

#endif // DFPLAYERMINI_ESP32