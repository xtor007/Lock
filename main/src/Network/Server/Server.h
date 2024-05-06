#ifndef SERVER_H
#define SERVER_H

#include <Arduino.h>
#include <EtherCard.h>

#include "ServerConstants.h"

class Server {
private:
  byte pin;

  char prevCode[ServerConstants::codeSize];

  void sendResponse();
  void sendFailuire();

  bool verifyRequest(word req);
  bool verifyCode(char *code);

public:
  Server(byte pin);
  void init();
  bool isRequestDone();
  ~Server() { delete[] prevCode; };
};

#endif