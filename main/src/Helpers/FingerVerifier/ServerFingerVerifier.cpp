#include "ServerFingerVerifier.h"
#include "../../InputDevices/FingerReader/FingerReaderConstants.h"

bool ServerFingerVerifier::checkFinger(uint8_t *code) {
    // dumpByteArray(code);
    return true;
}

// void ServerFingerVerifier::dumpByteArray(uint8_t *buffer) {
//     for (int i = 0; i < FingerReaderConstants::fingerCodeSize; ++i) {
//         char tmp[16];
//         char format[128];
//         sprintf(format, "%%.%dX", 2);
//         sprintf(tmp, format, buffer[i]);
//         Serial.print(tmp);
//     }
//     Serial.println();
// }