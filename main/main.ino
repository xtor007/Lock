#define UNLOCK_PIN 12
#define OPEN_BUTTON_PIN 2
#define LOCK_STATE_PIN 3

bool wasDoorOpen = false;
bool isDoorUnlock = false;

void setup() {
  setupLock();
  setupButton();
  setupLockState();
}

void loop() {
  if (checkButtonTapping()) {
    unlock();
  }
  bool isDoorClosing = lockDoorIfDoorClosed();
}

void setupLock() {
  pinMode(UNLOCK_PIN, OUTPUT);
}

void setupButton() {
  pinMode(OPEN_BUTTON_PIN, INPUT_PULLUP);
}

void setupLockState() {
  pinMode(LOCK_STATE_PIN, INPUT_PULLUP);
}

bool checkButtonTapping() {
  int buttonState = digitalRead(OPEN_BUTTON_PIN);
  return (buttonState == HIGH);
}

bool checkDoorStatus() {
  int doorState = digitalRead(LOCK_STATE_PIN);
  return (doorState == HIGH);
}

bool lockDoorIfDoorClosed() {
  bool isDoorOpen = checkDoorStatus();
  bool shouldLock = (!isDoorOpen) && (wasDoorOpen);
  if (shouldLock) {
    lock();
  }
  wasDoorOpen = isDoorOpen;
  return shouldLock;
}

void unlock() {
  isDoorUnlock = true;
  delay(100);
  digitalWrite(UNLOCK_PIN, HIGH); // tmp LED
  startCheckingLockLoop();
}

void startCheckingLockLoop() {
  for(int i = 0; i < 500; i++) {
    bool isDoorClosing = lockDoorIfDoorClosed();
    if (isDoorClosing) {
      break;
    }
    delay(10);
  }
  if (!checkDoorStatus()) {
    lock();
  }
}

void lock() {
  isDoorUnlock = false;
  digitalWrite(UNLOCK_PIN, LOW); // tmp LED
}