#include "ServerFingerVerifier.h"
#include "../../InputDevices/FingerReader/FingerReaderConstants.h"

void ServerFingerVerifier::checkFinger(uint8_t *code) {
  size_t codeLength = sizeof(code);
  char* codeStr = dumpByteArray(code);
  network->send(PSTR("/verifier/verifyFinger"), codeStr);
  // free(codeStr);
}

char* ServerFingerVerifier::byteArrayToHexString(const byte* byteArray) {
  char* hexString = (char*)malloc((sizeof byteArray) * 2 + 1);
  for (int i = 0; i < (sizeof byteArray) * 2; i++) {
    sprintf(hexString + 2 * i, "%02X", byteArray[i]);
  }
  return hexString;
}

char* ServerFingerVerifier::dumpByteArray(uint8_t *buffer) {
  char* prefix = network->getQueryPrefix();
  size_t prefixLen = strlen(prefix);
  char* result = new char[FingerReaderConstants::fingerCodeSize * 2 + 1 + prefixLen];
  char* ptr = result;
  strncpy(ptr, prefix, prefixLen);
  ptr += prefixLen;
  for (int i = 0; i < FingerReaderConstants::fingerCodeSize; ++i) {
      sprintf(ptr, "%02X", buffer[i]);
      ptr += 2;
  }
  return result;
}