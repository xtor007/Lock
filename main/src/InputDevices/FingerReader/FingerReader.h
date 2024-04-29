#ifndef FINGER_READER_H
#define FINGER_READER_H

#include <Arduino.h>
#include <Adafruit_Fingerprint.h>

#include "../../Helpers/FingerVerifier/IFingerVerifier.h"

class FingerReader {
private:
  byte rxPin;
  byte txPin;
  SoftwareSerial *reader;
  Adafruit_Fingerprint *finger;

  IFingerVerifier *verifier;
  
  const int memoryCell = 1;

  bool checkFinger();
  bool loadFinger(uint8_t *fingerCode);
public:
  FingerReader(byte rxPin, byte txPin, SoftwareSerial *reader, Adafruit_Fingerprint *finger, IFingerVerifier *verifier);
  void init();
  bool checkPossibleFinger();
  ~FingerReader() { delete reader; delete finger; delete verifier; };
};

#endif
