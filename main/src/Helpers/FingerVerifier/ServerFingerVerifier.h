#ifndef FINGER_VERIFIER_H
#define FINGER_VERIFIER_H

#include <Arduino.h>
#include "IFingerVerifier.h"
#include "../NetworkSender/INetworkSender.h"

class ServerFingerVerifier: public IFingerVerifier {
private:
  INetworkSender* network;
  char* byteArrayToHexString(const byte* byteArray);
  char* dumpByteArray(uint8_t *buffer);
public:
  ServerFingerVerifier(INetworkSender* network) { this->network = network; };
  void checkFinger(uint8_t *code) override;
};

#endif