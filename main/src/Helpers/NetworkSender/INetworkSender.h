#ifndef I_NETWORK_H
#define I_NETWORK_H

#include <Arduino.h>

class INetworkSender {
public:
  virtual char* getQueryPrefix();
  virtual void send(const char *path, const char *code);
  virtual ~INetworkSender() = default;
};

#endif