#ifndef CARD_READER_H
#define CARD_READER_H

#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

#include "../../Helpers/CardCodeVerifier/ICardCodeVerifier.h"

class CardReader {
private:
  MFRC522 mfrc522;

  ICardCodeVerifier *verifier;

  byte lastNotNormCardSize = 0;
  byte lastNotNormCardCode[4];

  bool compareWithNotNormCard(byte size, byte *code);
  bool checkCard(byte *buffer, byte *bufferSize);
public:
  CardReader(byte resetPin, byte sdaPin, ICardCodeVerifier *verifier);
  void init();
  bool checkPossibleCard();
  ~CardReader() { };
};

#endif
