#include "Arduino.h"
#include "Door.h"
#include "../Constants/Constants.h"

Door::Door(byte indicatorPin, byte lockPin, byte soundPin) {
  this->doorIndicator = DoorIndicator(indicatorPin);
  this->lockDevice = Lock(lockPin);
  this->dynamic = Dynamic(soundPin);
}

void Door::init() {
  doorIndicator.init();
  lockDevice.init();
  dynamic.init();
}

void Door::unlock() {
  delay(Constants::doorOpeningDelay);
  lockDevice.unlock();
  startCheckingLockLoop();
  dynamic.stop();
  if (!doorIndicator.isOpen()) {
    lock();
  }
}

void Door::lock() {
  lockDevice.lock();
}

bool Door::lockDoorIfDoorClosed() {
  bool shouldLock = doorIndicator.isChangedDoorStatus();
  if (shouldLock) {
    lock();
  }
  return shouldLock;
}

void Door::startCheckingLockLoop() {
  int iterationsCount = Constants::waitingForDoorOpeningTime / Constants::closeMaxPeriod;
  int soundPeriodicity = Constants::dynamicSoundDuration / Constants::closeMaxPeriod;
  for(int i = 0; i < iterationsCount; i++) {
    flashDynamicIfNeeded(soundPeriodicity, i);
    if (lockDoorIfDoorClosed()) {
      break;
    }
    delay(Constants::closeMaxPeriod);
  }
}

void Door::flashDynamicIfNeeded(int soundPeriodicity, int iteration) {
  if (!doorIndicator.isOpen()) {
    if (iteration % soundPeriodicity == 0) {
      dynamic.flashingSound(iteration / soundPeriodicity);
    }
  } else {
    dynamic.stop();
  }
}
