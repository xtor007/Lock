#ifndef NETWORK_SENDER_H
#define NETWORK_SENDER_H

#include <Arduino.h>
#include <EtherCard.h>

#include "INetworkSender.h"

class NetworkSender: public INetworkSender {
  void makeQuery(char*& query, char* code);
public:
  NetworkSender() {};

  void init();
  void send(const char *path, const char *code) override;

  static bool isRequestFinished;
  static bool isRequestSuccessed;

  static void responseDataWasProcessed() { isRequestSuccessed = false; };
  static void callback (byte status, word off, word len);
};

#endif