#include "Door.h"
#include "Constants.h"

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
  delay(Constants::doorOpeningDelay);
  digitalWrite(lockPin, HIGH); // tmp LED
  startCheckingLockLoop();
}

void Door::lock() {
  isDoorUnlock = false;
  digitalWrite(lockPin, LOW); // tmp LED
}

bool Door::lockDoorIfDoorClosed() {
  bool isDoorOpen = isDoorOpen();
  bool shouldLock = (!isDoorOpen) && (wasDoorOpen);
  if (shouldLock) {
    lock();
  }
  wasDoorOpen = isDoorOpen;
  return shouldLock;
}

bool Door::isDoorOpen() {
  int doorState = digitalRead(pin);
  return (doorState == HIGH);
}

void Door::startCheckingLockLoop() {
  int iterationsCount = Constants::waitingForDoorOpeningTime / Constants::closeMaxPeriod;
  for(int i = 0; i < iterationsCount; i++) {
    bool isDoorClosing = lockDoorIfDoorClosed();
    if (isDoorClosing) {
      break;
    }
    delay(Constants::closeMaxPeriod);
  }
  if (!isDoorOpen()) {
    lock();
  }
}