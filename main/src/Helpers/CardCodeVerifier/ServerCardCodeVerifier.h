#ifndef VERIFIER_H
#define VERIFIER_H

#include <Arduino.h>
#include "ICardCodeVerifier.h"

class ServerCardCodeVerifier: public ICardCodeVerifier {
public:
  ServerCardCodeVerifier() {};
  bool checkCard(byte *code, byte *codeSize) override;
};

#endif