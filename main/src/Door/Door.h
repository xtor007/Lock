#ifndef DOOR_H
#define DOOR_H

#include <Arduino.h>
#include "Devices/Dynamic/Dynamic.h"
#include "Devices/Lock/Lock.h"
#include "Devices/DoorIndicator/DoorIndicator.h"

class Door {
private:
  DoorIndicator doorIndicator;
  Lock lockDevice;
  Dynamic dynamic;

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
