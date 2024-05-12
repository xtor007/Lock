#ifndef FINGER_READER_CONSTANTS_H
#define FINGER_READER_CONSTANTS_H

class FingerReaderConstants {
public:
  static constexpr int fingerCodeSize = 120;
  static constexpr int fingerPackageSize = 534;
  static constexpr int fingerReaderBeginCode = 57600;
  static constexpr int readTime = 20000;
  static constexpr int headerSize = 148;
};

#endif