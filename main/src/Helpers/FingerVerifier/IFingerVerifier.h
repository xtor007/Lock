#ifndef I_FINGER_VERIFIER_H
#define I_FINGER_VERIFIER_H

#include <Arduino.h>

class IFingerVerifier {
public:
  virtual void checkFinger(int index);
  virtual ~IFingerVerifier() = default;
};

#endif