#include "src/InputDevices/Button/Button.h"
#include "src/Door/Door.h"
#include "src/InputDevices/CardReader/CardReader.h"
#include "src/Helpers/CardCodeVerifier/ServerCardCodeVerifier.h"
#include "src/InputDevices/FingerReader/FingerReader.h"
#include "src/Helpers/FingerVerifier/ServerFingerVerifier.h"
#include "src/Network/Server/Server.h"
#include "src/Helpers/NetworkSender/NetworkSender.h"

// Pins

#define FINGER_READER_TX_PIN 2
#define FINGER_READER_RX_PIN 3
#define SOUND_PIN 4
#define UNLOCK_PIN 5

#define CARD_READER_SDA_PIN 6

#define DOOR_STATE_PIN 7
#define OPEN_BUTTON_PIN 8

#define CARD_READER_RESET_PIN 9

#define INTERNET_CONNECTOR_SS_PIN 10

#define MASI_PIN 11
#define MISO_PIN 12
#define SCK_PIN 13

// Global objects

ServerConstants* ServerConstants::sharedArrays = nullptr;
bool NetworkSender::isRequestFinished = true;
bool NetworkSender::isRequestSuccessed = false;

byte Ethernet::buffer[ServerConstants::bufferSize];

NetworkSender networkSender;
ServerCardCodeVerifier cardVerifier(&networkSender);
ServerFingerVerifier fingerVerifier;

SoftwareSerial fingerReaderSerial(FINGER_READER_TX_PIN, FINGER_READER_RX_PIN);
Adafruit_Fingerprint finger(&fingerReaderSerial);

Door door(DOOR_STATE_PIN, UNLOCK_PIN, SOUND_PIN);

Button openButton(OPEN_BUTTON_PIN);
CardReader cardReader(
  CARD_READER_RESET_PIN,
  CARD_READER_SDA_PIN,
  &cardVerifier
);
FingerReader fingerReader(
  FINGER_READER_TX_PIN, 
  FINGER_READER_RX_PIN,
  &fingerReaderSerial,
  &finger,
  &fingerVerifier
);
Server inputServer(INTERNET_CONNECTOR_SS_PIN);

// Lyfecycle

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println(F("Arduino start"));
  door.init();
  openButton.init();
  cardReader.init();
  fingerReader.init();
  inputServer.init();
  networkSender.init();
}

void loop() {
  door.lockDoorIfDoorClosed();
  if (NetworkSender::isRequestFinished) {
    checkButton();
    cardReader.checkPossibleCard();
    checkFingerReader();
  }
  checkServer();
  checkNetworkSender();
}

// Checking objects

void checkButton() {
  if (openButton.checkButtonTapping()) {
    door.unlock();
  }
}

void checkFingerReader() {
  if (fingerReader.checkPossibleFinger()) {
    door.unlock();
  }
}

void checkServer() {
  if (inputServer.isRequestDone()) {
    door.unlock();
  }
}

void checkNetworkSender() {
  if (NetworkSender::isRequestSuccessed) {
    NetworkSender::responseDataWasProcessed();
    door.unlock();
  }
}