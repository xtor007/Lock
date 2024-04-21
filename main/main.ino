#include "Button.h"
#include "Door.h"

#define UNLOCK_PIN 12
#define SOUND_PIN 11
#define OPEN_BUTTON_PIN 2
#define DOOR_STATE_PIN 3

Door door(DOOR_STATE_PIN, UNLOCK_PIN, SOUND_PIN);
Button openButton(OPEN_BUTTON_PIN);

void setup() {
  door.init();
  openButton.init();
}

void loop() {
  if (openButton.checkButtonTapping()) {
    door.unlock();
  }
  door.lockDoorIfDoorClosed();
}