bool isLedOn() {
  if (digitalRead(LED) == HIGH) {
    return true;
  }
  return false;
}

void turnLedOn() {
  digitalWrite(LED, HIGH);
}

void turnLedOff() {
  digitalWrite(LED, LOW);
}
