#ifndef FINGER_VERIFIER_H
#define FINGER_VERIFIER_H

#include <Arduino.h>
#include "IFingerVerifier.h"

class ServerFingerVerifier: public IFingerVerifier {
private:
  void dumpByteArray(uint8_t *buffer);
public:
  ServerFingerVerifier() {};
  bool checkFinger(uint8_t *code) override;
};

#endif