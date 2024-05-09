#include "ServerCardCodeVerifier.h"

void ServerCardCodeVerifier::checkCard(byte *code, byte *codeSize) {
  char* codeStr = byteArrayToHexString(code);
  network->send(PSTR("/verifier/verifyCard"), codeStr);
  free(codeStr);
}

char* ServerCardCodeVerifier::byteArrayToHexString(const byte* byteArray) {
    char* hexString = (char*)malloc((sizeof byteArray) * 4 + 1);
    for (int i = 0; i < (sizeof byteArray) * 2; i++) {
      sprintf(hexString + 2 * i, "%02X", byteArray[i]);
    }
    return hexString;
}