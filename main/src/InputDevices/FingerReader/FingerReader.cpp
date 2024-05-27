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

void FingerReader::checkPossibleFinger() {
  int fingerIndex = 0;
  if (checkFinger(&fingerIndex)) {
    verifier->checkFinger(fingerIndex);
  }
  return false;
}

bool FingerReader::checkFinger(int *index) {
  int readerStatus = finger->getImage();
  if (readerStatus != FINGERPRINT_OK)  { return false; }

  int convertStatus = finger->image2Tz(1);
  if (convertStatus != FINGERPRINT_OK)  { return false; }

  int searchStatus = finger->fingerSearch();
  if (searchStatus != FINGERPRINT_OK)  { return false; }

  *index = finger->fingerID;

  return true;
}