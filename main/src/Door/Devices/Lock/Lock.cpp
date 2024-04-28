#include "Lock.h"

Lock::Lock(byte pin) {
  this->pin = pin;
}

void Lock::init() {
  pinMode(pin, OUTPUT);
  lock();
}

void Lock::lock() {
  digitalWrite(pin, LOW);
}

void Lock::unlock() {
  digitalWrite(pin, HIGH);
}