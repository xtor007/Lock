#include "Door.h"

Door::Door(byte pin, byte lockPin) {
  this->pin = pin;
  this->lockPin = lockPin;
}

void Door::init() {
  pinMode(pin, INPUT_PULLUP);
  pinMode(lockPin, OUTPUT);
}

void Door::unlock() {
  isDoorUnlock = true;
  delay(100);
  digitalWrite(lockPin, HIGH); // tmp LED
  startCheckingLockLoop();
}

void Door::lock() {
  isDoorUnlock = false;
  digitalWrite(lockPin, LOW); // tmp LED
}

bool Door::lockDoorIfDoorClosed() {
  bool isDoorOpen = checkDoorStatus();
  bool shouldLock = (!isDoorOpen) && (wasDoorOpen);
  if (shouldLock) {
    lock();
  }
  wasDoorOpen = isDoorOpen;
  return shouldLock;
}

bool Door::checkDoorStatus() {
  int doorState = digitalRead(pin);
  return (doorState == HIGH);
}

void Door::startCheckingLockLoop() {
  for(int i = 0; i < 500; i++) {
    bool isDoorClosing = lockDoorIfDoorClosed();
    if (isDoorClosing) {
      break;
    }
    delay(10);
  }
  if (!checkDoorStatus()) {
    lock();
  }
}