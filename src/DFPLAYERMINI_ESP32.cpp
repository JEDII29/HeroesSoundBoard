#include "DFPlayerMini_ESP32.h"

DFPlayerMini_ESP32::DFPlayerMini_ESP32() : mySerial(2) {}

bool DFPlayerMini_ESP32::begin() {
    mySerial.begin(9600);
    delay(1000);

    bool ret = DFRobotDFPlayerMini::begin(mySerial);

    volume(15);

    return ret;
}

String DFPlayerMini_ESP32::getMessage() {
    uint8_t type = readType();
    uint16_t value = read();
    String ret = "";

    switch(type) {
        case TimeOut:
            return "Time Out!";
        case WrongStack:
            return "Stack Wrong!";
        case DFPlayerCardInserted:
            return "Card Inserted!";
        case DFPlayerCardRemoved:
            return "Card Removed!";
        case DFPlayerCardOnline:
            return "Card Online!";
        case DFPlayerUSBInserted:
            return "USB Inserted!";
        case DFPlayerUSBRemoved:
            return "USB Removed!";
        case DFPlayerPlayFinished:
            return "Number: " + String(value) + " Finished!";
        case DFPlayerError:
            ret = "DFPlayerError: ";
            switch (value) {
                case Busy:
                    ret += "Card not found";
                    break;
                case Sleeping:
                    ret += "Sleeping";
                    break;
                case SerialWrongStack:
                    ret += "Get Wrong Stack";
                    break;
                case CheckSumNotMatch:
                    ret += "Check Sum Not Match";
                    break;
                case FileIndexOut:
                    ret += "File Index Out of Bound";
                    break;
                case FileMismatch:
                    ret += "Cannot Find File";
                    break;
                case Advertise:
                    ret += "In Advertise";
                    break;
                default:
                    ret += "Unknown";
                    break;
            }
            return ret;
        default:
            return "Unknown error";
            break;
    }
}