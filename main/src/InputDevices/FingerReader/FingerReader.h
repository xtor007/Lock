#ifndef FINGER_READER_H
#define FINGER_READER_H

#include <Arduino.h>
#include <Adafruit_Fingerprint.h>

#include "../../Helpers/FingerVerifier/IFingerVerifier.h"

class FingerReader {
private:
  SoftwareSerial *reader;
  Adafruit_Fingerprint *finger;

  IFingerVerifier *verifier;

  bool checkFinger(int *index);
public:
  FingerReader(byte rxPin, byte txPin, SoftwareSerial *reader, Adafruit_Fingerprint *finger, IFingerVerifier *verifier);
  void init();
  void checkPossibleFinger();
  ~FingerReader() { };
};

#endif
