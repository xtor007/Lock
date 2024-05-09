#ifndef I_VERIFIER_H
#define I_VERIFIER_H

#include <Arduino.h>

class ICardCodeVerifier {
public:
  virtual void checkCard(byte *code, byte *codeSize);
  virtual ~ICardCodeVerifier() = default;
};

#endif