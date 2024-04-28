#include "Button.h"
#include "Door.h"
#include "CardReader.h"
#include "ServerCardCodeVerifier.h"

// Pins

#define SOUND_PIN 4
#define UNLOCK_PIN 5
#define OPEN_BUTTON_PIN 6
#define DOOR_STATE_PIN 7

#define CARD_READER_RESET_PIN 9
#define CARD_READER_SDA_PIN 10
#define CARD_READER_MASI_PIN 11
#define CARD_READER_MISO_PIN 12
#define CARD_READER_SCK_PIN 13

// Global objects

ServerCardCodeVerifier cardVerifier;

Door door(DOOR_STATE_PIN, UNLOCK_PIN, SOUND_PIN);
Button openButton(OPEN_BUTTON_PIN);
CardReader cardReader(
  CARD_READER_RESET_PIN,
  CARD_READER_SDA_PIN,
  CARD_READER_MASI_PIN,
  CARD_READER_MISO_PIN,
  CARD_READER_SCK_PIN,
  &cardVerifier
);

// Lyfecycle

void setup() {
  Serial.begin(9600);
  while (!Serial);
  door.init();
  openButton.init();
  cardReader.init();
}

void loop() {
  door.lockDoorIfDoorClosed();
  checkButton();
  checkCardReader();
}

// Checking objects

void checkButton() {
  if (openButton.checkButtonTapping()) {
    door.unlock();
  }
}

void checkCardReader() {
  if (cardReader.checkPossibleCard()) {
    door.unlock();
  }
}