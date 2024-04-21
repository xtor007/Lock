#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

class Button {
private:
  byte pin;
public:
  Button(byte pin);
  void init();
  bool checkButtonTapping();
};

#endif