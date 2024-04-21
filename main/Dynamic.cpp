#include "Dynamic.h"

Dynamic::Dynamic(byte pin) {
  this->pin = pin;
}

void Dynamic::init() {
  pinMode(pin, OUTPUT);
  stop();
}

void Dynamic::play() {
  digitalWrite(pin, LOW);
}

void Dynamic::stop() {
  digitalWrite(pin, HIGH);
}

void Dynamic::flashingSound(int iteration) {
  if (iteration % 2 == 0) {
    play();
  } else {
    stop();
  }
}