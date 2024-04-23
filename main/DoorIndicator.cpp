#include "DoorIndicator.h"

DoorIndicator::DoorIndicator(byte pin) {
  this->pin = pin;
}

void DoorIndicator::init() {
  pinMode(pin, INPUT_PULLUP);
}

bool DoorIndicator::isOpen() {
  int doorState = digitalRead(pin);
  return (doorState == HIGH);
}

bool DoorIndicator::isClose() {
  int doorState = digitalRead(pin);
  return !(doorState == HIGH);
}

bool DoorIndicator::isChangedDoorStatus() {
  bool isDoorOpened = isOpen();
  bool shouldLock = (!isDoorOpened) && (wasDoorOpen);
  wasDoorOpen = isDoorOpened;
  return shouldLock;
}