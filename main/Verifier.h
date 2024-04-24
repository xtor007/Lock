#ifndef VERIFIER_H
#define VERIFIER_H

#include <Arduino.h>

class Verifier {
private:
  void dumpByteArray(byte *buffer, byte bufferSize);
public:
  Verifier() {};
  bool checkCard(byte *code, byte *codeSize); // TODO: Ask server
};

#endif