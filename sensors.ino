#define A 0.001129148
#define B 0.000234125
#define C 8.76741E-08
const float R1 = 10000.0; // value of R1 on board

float getTemperature() {
  // read the analog value from the thermistor pin
  int analogValue = analogRead(TEMP);
  // convert the analog value to resistance
  float resistance = (float)R1 / ((4095 / (float)analogValue) - 1);
  // Use the Steinhart-Hart equation
  float lnR = log(resistance);
  float temp = (1 / (A + (B * lnR) + (C * lnR * lnR * lnR))) - 273.15;
  return temp;
}

float getLDR() {
  return analogRead(LDR);
}

void checkSeuil() {
  if (isOn == true) {
    if (ldr < seuil) {
      turnLedOn();
    } else {
      turnLedOff();
    }
  }
}
