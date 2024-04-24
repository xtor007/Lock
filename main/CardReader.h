#ifndef CARD_READER_H
#define CARD_READER_H

#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

class CardReader {
private:
  byte resetPin;
  byte sdaPin;
  byte masiPin;
  byte misoPin;
  byte sckPin;

  MFRC522 mfrc522;
public:
  CardReader(byte resetPin, byte sdaPin, byte masiPin, byte misoPin, byte sckPin);
  void init();
  bool checkCard(byte *buffer, byte *bufferSize);
};

#endif