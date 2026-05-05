// ESP8266 with CC1101 RF Transceiver Module example RECEIVE code - MAY 4, 2026
// GDO0 and GDO2 pins connections are NOT needed for this example 
// For problems programming using Windows 11, roll CH340 back to 3.5.2019.1 driver
// Note that Windows 11 will go ahead and update the driver to current version without notifying you so problem programming may return

// CS pin is 5 which on ESP8266 is labeled D1 (also known as GPIO5)

#include <Arduino.h>
#include <cc1101.h>

using namespace CC1101;

Radio radio(/* cs pin */ 5);   // esp8266 pin 5 is labeled as D1

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

void loop() {
  char buff[32];
  size_t read;

  Serial.println(F("Receiving ..."));
  Status status = radio.receive((uint8_t *)buff, sizeof(buff) - 1, &read);

  if (status == STATUS_OK) {
    buff[read] = '\0';

    Serial.print(F("Data: "));
    Serial.println(buff);

    Serial.print(F("Length: "));
    Serial.println(read);

    Serial.print(F("RSSI: "));
    Serial.print(radio.getRSSI());
    Serial.println(F(" dBm"));

    Serial.print(F("LQI: "));
    Serial.println(radio.getLQI());
  } else if (status == STATUS_CRC_MISMATCH) {
    Serial.println(F("CRC mismatch!"));
  } else {
    Serial.print(F("Error: "));
    Serial.println(status);
  }

  Serial.println();
}
