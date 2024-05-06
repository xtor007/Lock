#include "CardReader.h"
#include "../../Constants/Constants.h"

CardReader::CardReader(byte resetPin, byte sdaPin, ICardCodeVerifier *verifier) {
  this->mfrc522 = MFRC522(sdaPin, resetPin);
  this->verifier = verifier;
}

void CardReader::init() {
  SPI.begin();
  mfrc522.PCD_Init();
  delay(10);
  mfrc522.PCD_DumpVersionToSerial();
}


bool CardReader::checkPossibleCard() {
  byte code[Constants::maxBytesOnCard];
  byte codeSize;
  if (checkCard(code, &codeSize)) {
    if (verifier->checkCard(code, codeSize)) {
      return true;
    } else {
      lastNotNormCardSize = codeSize;
      memcpy(lastNotNormCardCode, code, codeSize);
    }
  }
  return false;
}

bool CardReader::checkCard(byte *code, byte *codeSize) {
  if (! mfrc522.PICC_IsNewCardPresent()) { return false; }
  if (! mfrc522.PICC_ReadCardSerial()) { return false; }
  if (compareWithNotNormCard(mfrc522.uid.size, mfrc522.uid.uidByte)) { return false; }
  memcpy(code, mfrc522.uid.uidByte, mfrc522.uid.size);
  *codeSize = mfrc522.uid.size;
  return true;
}

bool CardReader::compareWithNotNormCard(byte size, byte *code) {
  if (size != lastNotNormCardSize) {
    return false;
  }
  for (byte i = 0; i < size; i++) {
    if (code[i] != lastNotNormCardCode[i]) {
      return false;
    }
  }
  return true;
}
