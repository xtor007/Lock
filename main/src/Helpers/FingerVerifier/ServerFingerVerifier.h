#ifndef FINGER_VERIFIER_H
#define FINGER_VERIFIER_H

#include <Arduino.h>
#include "IFingerVerifier.h"
#include "../NetworkSender/INetworkSender.h"

class ServerFingerVerifier: public IFingerVerifier {
private:
  INetworkSender* network;
public:
  ServerFingerVerifier(INetworkSender* network) { this->network = network; };
  void checkFinger(int index) override;
};

#endif