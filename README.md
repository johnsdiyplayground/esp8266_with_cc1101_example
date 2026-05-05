I was having a lot of trouble finding working examples of CC1101 RF transceiver with ESP8266 boards.  

I could get this CC1101 board to work with newer ESP32 boards however so I suspected it could be done on ESP8266.

The biggest issue is making sure you have the pins from CC1101 going to the correct ESP8266 pins.  

CC1101 --> ESP8266  
1  GND --> G  
2  VCC --> 3V3 (do NOT use 5V!)  
3  GDO0 --> NC not needed  
4  CSN --> D1 (GPIO5)  
5  SCK --> D5 (GPIO14)  
6  MOSI --> D7 (GPIO13)  
7  MISO --> D6 (GPIO12)  
8  GPO2 --> NC not needed  
