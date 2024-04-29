#include "FingerReader.h"
#include "FingerReaderConstants.h"

FingerReader::FingerReader(byte rxPin, byte txPin, SoftwareSerial *reader, Adafruit_Fingerprint *finger, IFingerVerifier *verifier) {
  this->rxPin = rxPin;
  this->txPin = txPin;
  this->reader = reader;
  this->finger = finger;
  this->verifier = verifier;
}

void FingerReader::init() {
  finger->begin(57600);
  if (finger->verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
  }
}

bool FingerReader::checkPossibleFinger() {
  if (checkFinger()) {
    uint8_t fingerCode[FingerReaderConstants::fingerCodeSize];
    return ((loadFinger(fingerCode)) && verifier->checkFinger(fingerCode));
  }
  return false;
}

bool FingerReader::checkFinger() {
  int readerStatus = finger->getImage();
  if (readerStatus != FINGERPRINT_OK)  { return false; }

  int convertStatus = finger->image2Tz(1);
  if (convertStatus != FINGERPRINT_OK)  { return false; }

  int creatingStatus = finger->createModel();
  if (creatingStatus == FINGERPRINT_PACKETRECIEVEERR)  { return false; }

  int storeStatus = finger->storeModel(memoryCell);
  if (storeStatus != FINGERPRINT_OK)  { return false; }

  return true;
}

bool FingerReader::loadFinger(uint8_t *fingerTemplate) {
  int loadingStatus = finger->loadModel(memoryCell);
  if (loadingStatus != FINGERPRINT_OK)  { return false; }

  int status = finger->getModel();
  if (status != FINGERPRINT_OK)  { return false; }

  uint8_t bytesReceived[FingerReaderConstants::fingerPackageSize]; // 2 data packets
  memset(bytesReceived, 0xff, FingerReaderConstants::fingerPackageSize);

  uint32_t starttime = millis();
  int i = 0;
  while (i < FingerReaderConstants::fingerPackageSize && (millis() - starttime) < FingerReaderConstants::readTime) {
    if (reader->available()) {
      bytesReceived[i++] = reader->read();
    }
  }

  memset(fingerTemplate, 0xff, FingerReaderConstants::fingerCodeSize);

  // filtering only the data packets
  int uindx = FingerReaderConstants::headerSize, index = 0;
  int halfFingerCodeSize = FingerReaderConstants::fingerCodeSize / 2;
  memcpy(fingerTemplate + index, bytesReceived + uindx, halfFingerCodeSize);   // first 256 bytes
  uindx += halfFingerCodeSize;       // skip data
  uindx += FingerReaderConstants::checksumSize;         // skip checksum
  uindx += FingerReaderConstants::headerSize;         // skip next header
  index += halfFingerCodeSize;       // advance pointer
  memcpy(fingerTemplate + index, bytesReceived + uindx, halfFingerCodeSize);   // second 256 bytes

  return true;
}