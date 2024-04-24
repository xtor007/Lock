#include "Button.h"
#include "Door.h"
#include "CardReader.h"

#define OPEN_BUTTON_PIN 2
#define DOOR_STATE_PIN 3
#define SOUND_PIN 4
#define UNLOCK_PIN 5

#define CARD_READER_RESET_PIN 9
#define CARD_READER_SDA_PIN 10
#define CARD_READER_MASI_PIN 11
#define CARD_READER_MISO_PIN 12
#define CARD_READER_SCK_PIN 13

Door door(DOOR_STATE_PIN, UNLOCK_PIN, SOUND_PIN);
Button openButton(OPEN_BUTTON_PIN);
CardReader cardReader(
  CARD_READER_RESET_PIN,
  CARD_READER_SDA_PIN,
  CARD_READER_MASI_PIN,
  CARD_READER_MISO_PIN,
  CARD_READER_SCK_PIN
);

void setup() {
  Serial.begin(9600);
  door.init();
  openButton.init();
  cardReader.init();
}

void loop() {
  if (openButton.checkButtonTapping()) {
    door.unlock();
  }
  door.lockDoorIfDoorClosed();
  byte code;
  byte codeSize;
  if (cardReader.checkCard(&code, &codeSize)) {
    door.unlock();
  }
}
