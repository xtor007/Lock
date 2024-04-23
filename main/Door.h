#ifndef DOOR_H
#define DOOR_H

#include <Arduino.h>
#include "Dynamic.h"
#include "Lock.h"
#include "DoorIndicator.h"

class Door {
private:
  DoorIndicator doorIndicator;
  Lock lockDevice;
  Dynamic dynamic;

  bool isDoorUnlock = false;

  bool isDoorOpen();
  void startCheckingLockLoop();
  void flashDynamicIfNeeded(int soundPeriodicity, int iteration);
public:
  Door(byte indicatorPin, byte lockPin, byte soundPin);
  void init();
  void unlock();
  void lock();
  bool lockDoorIfDoorClosed();
};

#endif