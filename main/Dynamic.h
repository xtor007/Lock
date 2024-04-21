#ifndef DYNAMIC_H
#define DYNAMIC_H

#include <Arduino.h>

class Dynamic {
private:
  byte pin;
public:
  Dynamic() {};
  Dynamic(byte pin);
  void init();
  void play();
  void stop();
  void flashingSound(int iteration);
};

#endif