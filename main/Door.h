#ifndef DOOR_H
#define DOOR_H

#include <Arduino.h>
#include "Dynamic.h"
#include "Lock.h"

class Door {
private:
  byte pin;
  Lock lockDevice;
  Dynamic dynamic;

  bool wasDoorOpen = false;
  bool isDoorUnlock = false;

  bool isDoorOpen();
  void startCheckingLockLoop();
  void flashDynamicIfNeeded(int soundPeriodicity, int iteration);
public:
  Door(byte pin, byte lockPin, byte soundPin);
  void init();
  void unlock();
  void lock();
  bool lockDoorIfDoorClosed();
};

#endif