// cc1101 with esp8266 sending temperature data - MAY 5, 2026
// Author is John at Johns DIY Playground

// THIS IS TESTED AND WORKING - MAY 5, 2026
// Sketch will send a "Hello" along with a counter number and then the temp in Celsius 

// ESP8266 D1 MINI CLONE may need CH340 ver 3.5.2019.1 DRIVER TO PROGRAM IN WINDOWS 11

/*

CC1101 --> ESP8266
1  GND --> G
2  VCC --> 3V3 (do NOT use 5V!)
3  GDO0 --> NC not needed
4  CSN --> D4 (GPIO2)
5  SCK --> D5 (GPIO14) 
6  MOSI --> D7 (GPIO13)
7  MISO --> D6 (GPIO12)
8  GPO2 --> NC not needed

BME280 --> ESP8266
VIN --> 3V3
GND --> G
SCL --> D1 (GPIO5)
SDA --> D2 (GPIO4)

*/

#include <Adafruit_BME280.h>
#include <Arduino.h>
#include <cc1101.h>

using namespace CC1101;

// BME280 Configuration
Adafruit_BME280 bme; // I2C

Radio radio(/* cs pin */ 2);  // labeled D4 on esp8266 (GPIO2)

void setup() {
  Serial.begin(9600);
 
  // Initialize BME280
  if (!bme.begin(0x76)) { // 0x76 is common I2C address, change to 0x77 if needed
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }

  delay(3000);
  Serial.println(F("Starting ..."));
  delay(1000);

  if (radio.begin() == STATUS_CHIP_NOT_FOUND) {
    Serial.println(F("Chip not found!"));
    while (true) { delay(1000); }
  }

  radio.setModulation(MOD_ASK_OOK);
  radio.setFrequency(433.8);
  radio.setDataRate(10);
  radio.setOutputPower(10);

  radio.setPacketLengthMode(PKT_LEN_MODE_VARIABLE);
  radio.setAddressFilteringMode(ADDR_FILTER_MODE_NONE);
  radio.setPreambleLength(64);
  radio.setSyncWord(0x1234);
  radio.setSyncMode(SYNC_MODE_16_16);
  radio.setCrc(true);
  radio.setDataWhitening(true);
  radio.setManchester(false);
  radio.setFEC(false);
}

int counter = 0;

void loop() {
  String data = "Hello #" + String(counter++) + "  " + String(bme.readTemperature()) + " C";

  Serial.print(F("Transmitting: "));
  Serial.print(data);
  Serial.print(F(" "));
  Status status = radio.transmit((uint8_t *)data.c_str(), data.length());

  if (status == STATUS_OK) {
    Serial.println(F("[OK]"));
  } else {
    Serial.print("[ERROR ");
    Serial.print(status);
    Serial.println("]");
  }

  delay(1000);
}
