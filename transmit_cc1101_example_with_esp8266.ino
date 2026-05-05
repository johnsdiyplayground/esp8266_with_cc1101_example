// ESP8266 with CC1101 RF Transceiver Module example TRANSMIT code - MAY 4, 2026
// GDO0 and GDO2 pins connections are NOT needed for this example 
// For problems programming using Windows 11, roll CH340 back to 3.5.2019.1 driver
// Note that Windows 11 will go ahead and update the driver to current version without notifying you so problem programming may return

// CS pin is 5 which on ESP8266 is labeled D1 (also known as GPIO5)


#include <Arduino.h>
#include <cc1101.h>

using namespace CC1101;

Radio radio(/* cs pin */ 5);  // this is esp8266 pin labeled D1 on PCB 

void setup() {
  Serial.begin(115200);
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
  String data = "Hello #" + String(counter++);

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
