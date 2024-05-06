#ifndef DOOR_INDICATOR_H
#define DOOR_INDICATOR_H

#include <Arduino.h>

class DoorIndicator {
private:
  byte pin;
  bool wasDoorOpen = false;
public:
  DoorIndicator() {};
  DoorIndicator(byte pin);
  void init();
  bool isOpen();
  bool isChangedDoorStatus();
};

#endif