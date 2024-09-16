void Messung() {
  // CO2 Messung
  measurement_t m = mhz19_uart->getMeasurement();

  Serial.print("co2: ");
  Serial.println(m.co2_ppm);  //CO2 Messwert
  Serial.print("temp: ");
  Serial.println(m.temperature);
  CO2 = String(m.co2_ppm); //CO2 --> STRING
  co2 = m.co2_ppm; //co2 --> Integer
  Serial.println(CO2);


  // Überprüfe, ob die Werte erfolgreich gelesen wurden
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Fehler beim Auslesen des Sensors!");
  } else {
    // Zeige die Werte auf dem seriellen Monitor an
    temperature = dht.readTemperature();  // Temperatur in Celsius
    humidity = dht.readHumidity();        // Luftfeuchtigkeit in Prozent
    Serial.print("Temperatur: ");
    Serial.print(temperature);
    Serial.print("°C, Luftfeuchtigkeit: ");
    Serial.print(humidity);
    Serial.println("%");
  }
  print();
}


void print() {

  String_temperature = dht.readTemperature();  // Temperatur in Celsius
  String_humidity = dht.readHumidity();        // Luftfeuchtigkeit in Prozent

  tft.fillRect(0, 0, 240, 50, TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  if(randfarbe== "grün"){tft.drawRect(0, 0, tft.width(), tft.height(), TFT_GREEN); errorcode = "Status: OK!";}
  else tft.drawRect(0, 0, tft.width(), tft.height(), TFT_RED); 
  //Setup


  tft.drawString(errorcode, 5, 2, 1);
  tft.drawString("CO2 ist " + CO2+"ppm Ventil: "+Ventil, 5, 12, 1);
  tft.drawString("Temp: " + String_temperature + "C   Heizung: "+Heizung, 5, 22, 1);
  tft.drawString("Feuchte: " + String_humidity + "%     KS: "+Kühlschrank, 5, 32, 1);

  Logik();  //Logik ausführen
}