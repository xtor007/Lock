#include "Arduino.h"
#include "Door.h"
#include "Constants.h"

Door::Door(byte pin, byte lockPin, byte soundPin) {
  this->pin = pin;
  this->lockDevice = Lock(lockPin);
  this->dynamic = Dynamic(soundPin);
}

void Door::init() {
  pinMode(pin, INPUT_PULLUP);
  lockDevice.init();
  dynamic.init();
}

void Door::unlock() {
  isDoorUnlock = true;
  delay(Constants::doorOpeningDelay);
  lockDevice.unlock();
  startCheckingLockLoop();
  dynamic.stop();
  if (!isDoorOpen()) {
    lock();
  }
}

void Door::lock() {
  isDoorUnlock = false;
  lockDevice.lock();
}

bool Door::lockDoorIfDoorClosed() {
  bool isDoorOpened = isDoorOpen();
  bool shouldLock = (!isDoorOpened) && (wasDoorOpen);
  if (shouldLock) {
    lock();
  }
  wasDoorOpen = isDoorOpened;
  return shouldLock;
}

bool Door::isDoorOpen() {
  int doorState = digitalRead(pin);
  return (doorState == HIGH);
}

void Door::startCheckingLockLoop() {
  int iterationsCount = Constants::waitingForDoorOpeningTime / Constants::closeMaxPeriod;
  int soundPeriodicity = Constants::dynamicSoundDuration / Constants::closeMaxPeriod;
  for(int i = 0; i < iterationsCount; i++) {
    flashDynamicIfNeeded(soundPeriodicity, i);
    bool isDoorClosing = lockDoorIfDoorClosed();
    if (isDoorClosing) {
      break;
    }
    delay(Constants::closeMaxPeriod);
  }
}

void Door::flashDynamicIfNeeded(int soundPeriodicity, int iteration) {
  if (!isDoorOpen()) {
      if (iteration % soundPeriodicity == 0) {
        dynamic.flashingSound(iteration / soundPeriodicity);
      }
    } else {
      dynamic.stop();
    }
}