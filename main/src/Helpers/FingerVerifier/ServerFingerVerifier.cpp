#include "ServerFingerVerifier.h"
#include "../../InputDevices/FingerReader/FingerReaderConstants.h"

void ServerFingerVerifier::checkFinger(int index) {
  char* prefix = network->getQueryPrefix();
  int codeStrSize = strlen(prefix) + 3 + 1; 
  char* codeStr = new char[codeStrSize];
  snprintf(codeStr, codeStrSize, "%s%d", prefix, index);
  network->send(PSTR("/verifier/verifyFinger"), codeStr);
}