void display(float temp, float ldr) {
  tft.fillScreen(TFT_BLACK); // clear the screen
  tft.setTextSize(2);
  tft.setTextFont(2);
  tft.setTextWrap(true); // enable text wrapping
  tft.setTextDatum(MC_DATUM); // set text alignment to center

  tft.setCursor(50, 0);
  tft.setTextColor(TFT_BLUE);
  tft.print(temp);
  tft.print(" C°");

  if (isLedOn() == true) {
    tft.setCursor(50, 50);
    tft.setTextColor(TFT_GREEN);
    tft.println("LED Allumee");
  } else {
    tft.setCursor(50, 50);
    tft.setTextColor(TFT_RED);
    tft.println("LED Eteinte");
  }
}
