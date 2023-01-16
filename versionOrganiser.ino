#include<TFT_eSPI.h>
#include<SPI.h>
#include<math.h>

#include<WiFi.h>
#include<AsyncTCP.h>
#include<ESPAsyncWebServer.h>
#include<HTTPClient.h>


const char* ssid = "idriss";
const char* password = "12121212";
const char* secretKey = "93AXokuwrl&ob29icrOw";
AsyncWebServer server(80);
const int TEMP = 37;
const int LED = 33;
const int LDR = 32;
const int defaultSeuil = 1000;



int seuil = defaultSeuil;
float temp;
float ldr;
bool isOn = true;


TFT_eSPI tft = TFT_eSPI();

void setup() {
  tft.begin();
  tft.fillScreen(TFT_BLACK);
  tft.init();
  tft.setRotation(1);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  startListening();
}

void loop() {
  temp = getTemperature();
  ldr = getLDR();

  Serial.println(ldr);
  checkSeuil();

  display(temp, ldr);
  delay(1000);
}
