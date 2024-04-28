#include "Button.h"

Button::Button(byte pin) {
  this->pin = pin;
}

void Button::init() {
  pinMode(pin, INPUT_PULLUP);
}

bool Button::checkButtonTapping() {
  int buttonState = digitalRead(pin);
  return (buttonState == HIGH);
}