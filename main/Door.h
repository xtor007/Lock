#ifndef DOOR_H
#define DOOR_H

#include <Arduino.h>

class Door {
private:
  byte pin;
  byte lockPin;
  bool wasDoorOpen = false;
  bool isDoorUnlock = false;

  bool checkDoorStatus();
  void startCheckingLockLoop();
public:
  Door(byte pin, byte lockPin);
  void init();
  void unlock();
  void lock();
  bool lockDoorIfDoorClosed();
};

#endif