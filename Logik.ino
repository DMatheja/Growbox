void Logik() {
  if (dht.readTemperature() < minTemp) {
    HeizungAn();
    if (HeizungTimerläuft != true) { HeizungTimer = millis(); }
    HeizungTimerläuft = true;

  } else if (temperature > maxTemp) {
    HeizungAus();  //sollte schon vorher aus gewesen sein, zur Sicherheit nochmal.
    HeizungTimerläuft = false;
    turnOnSmartplug(smartplugIP1);
  }


  if (dht.readHumidity() < minF) {
    if (dht.readTemperature() < maxTemp) {
      turnOffSmartplug(smartplugIP1);
    } else if (millis() > 600000) {  //NICHTS TUN, TEMPERATUR WICHTIGER nach 10minuten
      errorcode = "Feuchte niedrig und zu heiß";
      randfarbe = "rot";
    }
  }
  if (dht.readHumidity() > minF) {
    turnOnSmartplug(smartplugIP1);
  }
  if (co2 < minCO2) {
    VentilAuf();
    if (VentilTimerläuft != true) { VentilTimer = millis(); }
    VentilTimerläuft = true;
  }
  if (co2 > maxCO2) {
    VentilZu();
    VentilTimerläuft = false;
  }


  if (VentilTimerläuft == true && (VentilTimer + 120000) < millis()) {
    VentilZu();
    errorcode = "Ventil lief 120 Sekunden";
    randfarbe = "rot";
    VentilTimerläuft = false;
  }

  if (HeizungTimerläuft == true && (HeizungTimer + 120000) < millis()) {
    HeizungAus();
    errorcode = "Heizung lief 120 Sekunden";
    randfarbe = "rot";
    HeizungTimerläuft = false;
  }
}
