#ifndef NETWORK_SENDER_H
#define NETWORK_SENDER_H

#include <Arduino.h>
#include <EtherCard.h>

#include "INetworkSender.h"

class NetworkSender: public INetworkSender {
  char *queryPrefix;
public:
  NetworkSender(char *prefix) { this->queryPrefix = prefix; };

  void init();
  void send(const char *path, const char *code) override;
  char* getQueryPrefix() override { return queryPrefix; };

  static bool isRequestFinished;
  static bool isRequestSuccessed;
  static char *query;

  static void responseDataWasProcessed() { isRequestSuccessed = false; };
  static void callback (byte status, word off, word len);
};

#endif