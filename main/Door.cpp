#include "Arduino.h"
#include "Door.h"
#include "Constants.h"

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
  isDoorUnlock = true;
  delay(Constants::doorOpeningDelay);
  lockDevice.unlock();
  startCheckingLockLoop();
  dynamic.stop();
  if (doorIndicator.isClose()) {
    lock();
  }
}

void Door::lock() {
  isDoorUnlock = false;
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
    bool isDoorClosing = lockDoorIfDoorClosed();
    if (isDoorClosing) {
      break;
    }
    delay(Constants::closeMaxPeriod);
  }
}

void Door::flashDynamicIfNeeded(int soundPeriodicity, int iteration) {
  if (doorIndicator.isClose()) {
      if (iteration % soundPeriodicity == 0) {
        dynamic.flashingSound(iteration / soundPeriodicity);
      }
    } else {
      dynamic.stop();
    }
}