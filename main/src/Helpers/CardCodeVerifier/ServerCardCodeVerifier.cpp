#include "ServerCardCodeVerifier.h"

bool ServerCardCodeVerifier::checkCard(byte *code, byte *codeSize) { // TODO: ask server
  dumpByteArray(code, codeSize);
  byte standartKey[] = { 0x33, 0xF2, 0x2F, 0x11 };
  byte standartSize = 4;
  if (codeSize != standartSize) {
    return false;
  }
  for (byte i = 0; i < codeSize; i++) {
    if (code[i] != standartKey[i]) {
      return false;
    }
  }
  return true;
}

void ServerCardCodeVerifier::dumpByteArray(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
  Serial.println();
}