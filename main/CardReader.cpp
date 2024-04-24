#include "CardReader.h"

CardReader::CardReader(byte resetPin, byte sdaPin, byte masiPin, byte misoPin, byte sckPin) {
  this->resetPin = resetPin;
  this->sdaPin = sdaPin;
  this->masiPin = masiPin;
  this->misoPin = misoPin;
  this->sckPin = sckPin;
  this->mfrc522 = MFRC522(sdaPin, resetPin);
}

void CardReader::init() {
  SPI.begin();
  mfrc522.PCD_Init();
  delay(10);
  mfrc522.PCD_DumpVersionToSerial();
}

 bool CardReader::checkCard(byte *code, byte *codeSize) {
  if (! mfrc522.PICC_IsNewCardPresent()) return false;
  if (! mfrc522.PICC_ReadCardSerial()) return false;
  *code = mfrc522.uid.uidByte; // B8 B8 B8 B8
  *codeSize = mfrc522.uid.size;
  return true;
 }