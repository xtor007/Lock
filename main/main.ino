#define UNLOCK_PIN 12

void setup() {
  setupLock();
}

void loop() {
  unlock();
  delay(5000);
}

void setupLock() {
  pinMode(UNLOCK_PIN, OUTPUT);
}

void unlock() {
  digitalWrite(UNLOCK_PIN, HIGH); // tmp LED
  delay(5000);
  lock();
}

void lock() {
  digitalWrite(UNLOCK_PIN, LOW); // tmp LED
}