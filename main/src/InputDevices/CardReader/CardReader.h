#ifndef CARD_READER_H
#define CARD_READER_H

#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

#include "../../Helpers/CardCodeVerifier/ICardCodeVerifier.h"

class CardReader {
private:
  byte resetPin;
  byte sdaPin;
  byte masiPin;
  byte misoPin;
  byte sckPin;

  MFRC522 mfrc522;

  ICardCodeVerifier *verifier;

  byte lastNotNormCardSize = 0;
  byte *lastNotNormCardCode;

  bool compareWithNotNormCard(byte size, byte *code);
  bool checkCard(byte *buffer, byte *bufferSize);
  void setNewNotNormCard(byte size, byte *code);
public:
  CardReader(byte resetPin, byte sdaPin, byte masiPin, byte misoPin, byte sckPin, ICardCodeVerifier *verifier);
  void init();
  bool checkPossibleCard();
  ~CardReader() { delete verifier; delete lastNotNormCardCode; };
};

#endif
