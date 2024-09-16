void HeizungAn() {  //HeizungAn();
Heizung = true;
digitalWrite(heizungPin, LOW);  // Heizung an
}

void HeizungAus() {  //HeizungAus();
Heizung = false;
digitalWrite(heizungPin, HIGH);  // Heizung aus
}

void VentilAuf() {  //VentilAuf();
Ventil = true;
digitalWrite(ventilPin, LOW);   // Ventil auf
}

void VentilZu() {  //VentilZu();
Ventil = false;
digitalWrite(ventilPin, HIGH);   // Ventil zu
}

//turnOnSmartplug(smartplugIP1);    //Kühlschrank an
//turnOffSmartplug(smartplugIP1);   //Kühlschrank aus

// Funktion, um den Befehl zum Einschalten der Smartplug zu senden
void turnOnSmartplug(const char* smartplugIP) {
  WiFiClient client;
  if (client.connect(smartplugIP, smartplugPort)) {
    client.print("GET /cm?cmnd=Power%20On HTTP/1.1\r\n");
    client.print("Host: ");
    client.print(smartplugIP);
    client.print("\r\n\r\n");
    client.stop();
  }
  Kühlschrank = true;
}

// Funktion, um den Befehl zum Ausschalten der Smartplug zu senden
void turnOffSmartplug(const char* smartplugIP) {
  WiFiClient client;
  if (client.connect(smartplugIP, smartplugPort)) {
    client.print("GET /cm?cmnd=Power%20Off HTTP/1.1\r\n");
    client.print("Host: ");
    client.print(smartplugIP);
    client.print("\r\n\r\n");
    client.stop();
  }
  Kühlschrank = false;
}