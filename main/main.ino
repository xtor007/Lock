#define UNLOCK_PIN 12
#define OPEN_BUTTON_PIN 2

int prevButtonState = LOW;

void setup() {
  setupLock();
}

void loop() {
  if (checkButtonTapping()) {
    unlock();
  }
}

void setupLock() {
  pinMode(UNLOCK_PIN, OUTPUT);
}

void setupButton() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

bool checkButtonTapping() {
  int buttonState = digitalRead(OPEN_BUTTON_PIN);
  return (buttonState == HIGH);
}

void unlock() {
  delay(100);
  digitalWrite(UNLOCK_PIN, HIGH); // tmp LED
  delay(1000);
  lock();
}

void lock() {
  digitalWrite(UNLOCK_PIN, LOW); // tmp LED
}