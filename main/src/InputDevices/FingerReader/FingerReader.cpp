#include "FingerReader.h"
#include "FingerReaderConstants.h"

FingerReader::FingerReader(byte rxPin, byte txPin, SoftwareSerial *reader, Adafruit_Fingerprint *finger, IFingerVerifier *verifier) {
  this->reader = reader;
  this->finger = finger;
  this->verifier = verifier;
}

void FingerReader::init() {
  finger->begin(57600);
  if (finger->verifyPassword()) {
    Serial.println(F("Found fingerprint sensor!"));
  } else {
    Serial.println(F("Did not find fingerprint sensor :("));
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

  writeFinger(fingerTemplate);

  return true;
}

void FingerReader::writeFinger(uint8_t *fingerTemplate) {
  memset(fingerTemplate, 0xff, FingerReaderConstants::fingerCodeSize);

  uint32_t starttime = millis();
  int halfFingerCodeSize = FingerReaderConstants::fingerCodeSize / 2;

  int i = 0;
  int fingerIndex = 0;
  while (i < FingerReaderConstants::fingerPackageSize && (millis() - starttime) < FingerReaderConstants::readTime) {
    if (reader->available()) {
      if (
        (i - FingerReaderConstants::headerSize < 0)
        || ((i - FingerReaderConstants::headerSize - halfFingerCodeSize > 0) && (i - FingerReaderConstants::headerSize - halfFingerCodeSize - FingerReaderConstants::checksumSize - FingerReaderConstants::headerSize < 0) )
        || (i - FingerReaderConstants::headerSize - halfFingerCodeSize - FingerReaderConstants::checksumSize - FingerReaderConstants::headerSize - halfFingerCodeSize > 0)
      ) {
        i++;
        continue;
      }
      fingerTemplate[fingerIndex++] = reader->read();
      i++;
    }
  }
}