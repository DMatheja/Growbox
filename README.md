# Growbox
Open Source Code and instructions for making your own grow box using off-the-shelf components

you need:
ESP32
WiFi Smart plug (Tasmota firmware!!!)
CO2 Sensor (MHZ19B)
Temp/Humidity Sensor (DHT22)
1.8" TFT Screen (SPI)
3 Buttons
5V Power Supply 
Skill to make Basic electrical connections (solder or crimping)

you also need:
A fridge 
small 12V heater in the fridge, powered by any PSU you can trigger through connecting a PIN to ground (like any ATX-PSU)
Electric CO2 Valve (Optional, but required if you're goal is to make the BEST)
DOCUMENTATION IN PROGRESS, CODE WORKS.

Current version is 1.0
Everything works, and the logic is ROCK SOLID.
I even included safety precautions, for example, if the heater or the CO2 runs for longer than 120seconds (2minutes) it will turn them off once.
They will get turned back on if they need to.
This is just so that if they are turned on, and a sensor fails/disconnects, the system will turn them off eventually.

###TL:DR The code is definatly not perfect, but it works.###

The only problem is that the screen doesn't draw it perfectly and every 5 sec there is a short flicker, but it is totally usable.

IMPORTANT NOTES:
You must use my edited tft_eSPI library, because there are some changes needed for it to work properly with ESP32 
The other libraries you can download somewhere else, I just included them for simplicity, or if they break in the future.

Update: you probably don't need to use my edited library, it was a different issue and I fixed it, the problem was: you can't use esp32wifi library together with the normal wifi library. so I just kicked the esp32wifi library out, libraries are bloat anyways.


Why this license?
I chose the GNU License because I like Open Source, and I don't have a problem with people making money from my work. BUT, your product will also need to be Open Source.
