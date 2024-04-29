#ifndef I_FINGER_VERIFIER_H
#define I_FINGER_VERIFIER_H

#include <Arduino.h>

class IFingerVerifier {
public:
  virtual bool checkFinger(uint8_t *code);
  virtual ~IFingerVerifier() = default;
};

#endif