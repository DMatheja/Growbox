
#include "MHZ19.h"  //CO2 library MH-Z19
#include <WiFi.h>
#include <DHT.h>
#include <Wire.h>  ///////////////SDA=D21  SCL=22////////////////////////////////////
#include <Adafruit_GFX.h>
//#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
//#include <esp_wifi.h>
//Display libraries
#include <SPI.h>
#include <TFT_eSPI.h>  // Hardware-specific library

int aktuelleVariable;
const int heizungPin = 32;  // Pin für die Heizung
const int ventilPin = 33;   // Pin für das Ventil

float lastTemperature = 0.0;
float lastHumidity = 0.0;
int lastCO2 = 0;
String lastErrorcode = "";
String lastVentilStatus = "";
String lastHeizungStatus = "";
String lastKühlschrankStatus = "";



TFT_eSPI tft = TFT_eSPI();  // Invoke custom library
String randfarbe = "grün";
String errorcode = "Code: David Matheja";
String CO2 = "BOOT";
int co2;
String String_temperature = "BOOT";
String String_humidity = "BOOT";

bool Kühlschrank = false;
bool Ventil = false;
bool Heizung = false;


//CO2 PINS
const int rx_pin = 13;  //Serial rx pin no
const int tx_pin = 16;  //Serial tx pin no
MHZ19* mhz19_uart = new MHZ19(rx_pin, tx_pin);

unsigned long millis5S = 15000;  //CO2 Timer messung


//CopyPasta
bool VentilTimerläuft = 0;
bool HeizungTimerläuft = 0;
unsigned long VentilTimer = 0;
unsigned long HeizungTimer = 0;
int maxF = 72;     //Feuchtigkeit MAX
int minF = 68;     //Feuchtigkeit MIN
int maxTemp = 25;  //Temperatur MAX
int minTemp = 23;  //Temperatur MIN
int minCO2 = 800;
int maxCO2 = 1200;

// Array to store custom MAC to IP mappings
/*const int MAX_DEVICES = 5;
const char* device_macs[MAX_DEVICES] = {"48:55:19:17:b8:71", "48:55:19:c3:a0:a4","48:55:19:c4:0c:f8"};
const char* device_ips[MAX_DEVICES] = {"192.168.4.2", "192.168.4.4","192.168.4.3"};
const int num_devices = 3;
*/

#define DHT_PIN 17      // Ändere die Nummer entsprechend, je nachdem, an welchem Pin du den DHT22 angeschlossen hast
#define DHT_TYPE DHT22  // Ändere den Sensortyp hier auf DHT11, wenn du den DHT11-Sensor verwendest

DHT dht(DHT_PIN, DHT_TYPE);
float humidity = 0;
float temperature = 0;



const char* ssid = "ESP32-AP-WebServer";
const char* password = "12345678";

// Replace with the IP addresses of your Tasmota Smartplugs
const char* smartplugIP1 = "192.168.4.2";  // IP-Adresse der ersten Smartplug
const char* smartplugIP2 = "192.168.4.3";  // IP-Adresse der zweiten Smartplug
const int smartplugPort = 80;

unsigned long previousMillis = 0;
const long interval = 2000;  // Zeitintervall in Millisekunden (1 Sekunde)
unsigned long previousMillisSensor = 0;

int currentState = 0;  // Zustandsvariable zum Wechseln zwischen den Smartplugs



//Copy Ende

const int button1 = 25;
const int button2 = 26;
const int button3 = 27;

void setup() {
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);

  //relais
  pinMode(heizungPin, OUTPUT);
  pinMode(ventilPin, OUTPUT);
  //tft
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.drawRect(0, 0, tft.width(), tft.height(), TFT_GREEN);
  //CO2 Startup
  Serial.begin(9600);
  mhz19_uart->begin(rx_pin, tx_pin);
  mhz19_uart->setAutoCalibration(false);
  delay(3000);  // Issue #14
  Serial.print("MH-Z19 now warming up...  status:");
  Serial.println(mhz19_uart->getStatus());
  delay(1000);

  //CO2 Finish
  //DHT22 Start
  delay(2000);
  tft.fillScreen(TFT_BLACK);

  tft.setTextFont(0);
  dht.begin();
  delay(3000);
  tft.drawRect(0, 0, tft.width(), tft.height(), TFT_GREEN);

  //WIFI Start
  WiFi.softAP(ssid, password);
  //Wifi Finish
  HeizungAus();
  turnOffSmartplug(smartplugIP1);
  VentilZu();
  tft.drawString(errorcode, 5, 2, 1);
}


void loop() {
  // Sensormessung alle 5 Sekunden
  if (millis() > millis5S) {
    millis5S = millis() + 5000;
    Messung();  //CO2 und Temperatur
  }

  UserInput();
}
//turnOnSmartplug(smartplugIP1); //Kühlschrank an

//turnOffSmartplug(smartplugIP1); //Kühlschrank aus
