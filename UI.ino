void UserInput() {
  if (digitalRead(button1) == LOW) {
    increase();
    delay(200);
  }
  if (digitalRead(button2) == LOW) {
    decrease();
    delay(200);
  }
  if (digitalRead(button3) == LOW) {
    randfarbe="grün";
    if (aktuelleVariable >= 6) {
      aktuelleVariable = 1;
    } else {
      aktuelleVariable++;
    }
    delay(250);
  }

  UpdateDisplay();  // Aktualisiere die Anzeige nach jeder Änderung
  delay(20);
}

void increase() {
  switch (aktuelleVariable) {
    case 1: minTemp++; break;
    case 2: maxTemp++; break;
    case 3: minF++; break;
    case 4: maxF++; break;
    case 5: minCO2 += 100; break;
    case 6: maxCO2 += 100; break;
  }
}

void decrease() {
  switch (aktuelleVariable) {
    case 1: minTemp--; break;
    case 2: maxTemp--; break;
    case 3: minF--; break;
    case 4: maxF--; break;
    case 5: minCO2 -= 100; break;
    case 6: maxCO2 -= 100; break;
  }
}

// Funktion zur Aktualisierung des Displays und zum Hervorheben der aktuellen Variable
void UpdateDisplay() {
  // Lösche den bisherigen Textbereich
  tft.fillRect(0, 50, 240, 20, TFT_BLACK);  // Lösche die Bereich der Min-Werte
  tft.fillRect(0, 60, 240, 20, TFT_BLACK);  // Lösche die Bereich der Max-Werte

  // Erstelle die Textzeilen mit den aktuellen Werten
  String minLine = "Min   " + String(minTemp) + "C " + String(minF) + "% " + String(minCO2) + "ppm";
  String maxLine = "Max   " + String(maxTemp) + "C " + String(maxF) + "% " + String(maxCO2) + "ppm";

  // Setze die Schriftgröße
  tft.setTextSize(1);

  // Zeichne die Min-Werte (Zeile 1) und Max-Werte (Zeile 2) abhängig von der ausgewählten Variable
  if (aktuelleVariable == 1) {
    // minTemp ist ausgewählt -> invertiere Hintergrund
    tft.setTextColor(TFT_BLACK, TFT_WHITE);  // Invertiere Farben
  } else {
    tft.setTextColor(TFT_WHITE, TFT_BLACK);  // Normale Farben
  }
  tft.drawString("min: "+String(minTemp) + "C", 10, 50, 1);  // minTemp

  if (aktuelleVariable == 2) {
    tft.setTextColor(TFT_BLACK, TFT_WHITE);  // Invertiere Farben
  } else {
    tft.setTextColor(TFT_WHITE, TFT_BLACK);  // Normale Farben
  }
  tft.drawString("max: "+String(maxTemp) + "C", 10, 60, 1);  // maxTemp

  if (aktuelleVariable == 3) {
    tft.setTextColor(TFT_BLACK, TFT_WHITE);  // Invertiere Farben
  } else {
    tft.setTextColor(TFT_WHITE, TFT_BLACK);  // Normale Farben
  }
  tft.drawString(String(minF) + "%", 70, 50, 1);  // minF

  if (aktuelleVariable == 4) {
    tft.setTextColor(TFT_BLACK, TFT_WHITE);  // Invertiere Farben
  } else {
    tft.setTextColor(TFT_WHITE, TFT_BLACK);  // Normale Farben
  }
  tft.drawString(String(maxF) + "%", 70, 60, 1);  // maxF

  if (aktuelleVariable == 5) {
    tft.setTextColor(TFT_BLACK, TFT_WHITE);  // Invertiere Farben
  } else {
    tft.setTextColor(TFT_WHITE, TFT_BLACK);  // Normale Farben
  }
  tft.drawString(String(minCO2) + "ppm", 110, 50, 1);  // minCO2

  if (aktuelleVariable == 6) {
    tft.setTextColor(TFT_BLACK, TFT_WHITE);  // Invertiere Farben
  } else {
    tft.setTextColor(TFT_WHITE, TFT_BLACK);  // Normale Farben
  }
  tft.drawString(String(maxCO2) + "ppm", 110, 60, 1);  // maxCO2
}