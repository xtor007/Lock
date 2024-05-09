#ifndef VERIFIER_H
#define VERIFIER_H

#include <Arduino.h>
#include "ICardCodeVerifier.h"
#include "../NetworkSender/INetworkSender.h"

class ServerCardCodeVerifier: public ICardCodeVerifier {
private:
  INetworkSender* network;
  char* byteArrayToHexString(const byte* byteArray);
public:
  ServerCardCodeVerifier(INetworkSender* network) { this->network = network; };
  void checkCard(byte *code, byte *codeSize) override;
};

#endif