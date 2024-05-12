#include "ServerCardCodeVerifier.h"

void ServerCardCodeVerifier::checkCard(byte *code, byte *codeSize) {
  char* codeStr = byteArrayToHexString(code);
  network->send(PSTR("/verifier/verifyCard"), codeStr);
}

char* ServerCardCodeVerifier::byteArrayToHexString(const byte* byteArray) {
  char* prefix = network->getQueryPrefix();
  size_t prefixLen = strlen(prefix);
  char* hexString = (char*)malloc((sizeof byteArray) * 4 + 1 + prefixLen);
  strncpy(hexString, prefix, prefixLen);
  for (int i = 0; i < (sizeof byteArray) * 2; i++) {
    sprintf(hexString + (2 * i) + prefixLen, "%02X", byteArray[i]);
  }
  return hexString;
}