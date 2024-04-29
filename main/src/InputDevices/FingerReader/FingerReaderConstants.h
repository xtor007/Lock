#ifndef FINGER_READER_CONSTANTS_H
#define FINGER_READER_CONSTANTS_H

class FingerReaderConstants {
public:
  static constexpr int fingerCodeSize = 512;
  static constexpr int fingerPackageSize = 534;
  static constexpr int fingerReaderBeginCode = 57600;
  static constexpr int readTime = 20000;
  static constexpr int headerSize = 9;
  static constexpr int checksumSize = 2;
};

#endif