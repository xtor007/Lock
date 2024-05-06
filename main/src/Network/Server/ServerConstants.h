#ifndef SERVER_CONSTANTS_H
#define SERVER_CONSTANTS_H

class ServerConstants {
private:
  ServerConstants() {};
  static ServerConstants* sharedArrays;
public:
  static constexpr int bufferSize = 500;
  static constexpr int codeSize = 4;
  static constexpr int neededReqSize = 9;

  const byte myip[4] PROGMEM = { 192,168,1,203 };
  const byte mymac[6] PROGMEM = { 0x74,0x69,0x69,0x2D,0x30,0x31 };
  const char requestStart[9] PROGMEM = "GET /?id=";

  const char s200[17] PROGMEM = "HTTP/1.0 200 OK\r\n";
  const char s503[34] PROGMEM = "HTTP/1.0 503 Service Unavailable\r\n";

  const char headers[56] PROGMEM = "Server: Arduino Nano\r\n"
                                "Content-Type: application/json\r\n"
                                "\r\n";

  const char b503[14] PROGMEM = "{\"error\":true}";
  const char b200[15] PROGMEM = "{\"error\":false}";

  static ServerConstants* sharedArraysInstanse() {
    if (sharedArrays == nullptr) {
        sharedArrays = new ServerConstants();
    }
    return sharedArrays;
  };
};

#endif
