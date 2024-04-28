#ifndef LOCK_H
#define LOCK_H

#include <Arduino.h>

class Lock {
private:
  byte pin;
public:
  Lock() {};
  Lock(byte pin);
  void init();
  void lock();
  void unlock();
};

#endif