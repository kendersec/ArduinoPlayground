/*
   https://jgromes.github.io/RadioLib/

Use rtl_433 to sniff the data and inspectrum to inspect and extract the msg, run the extracted bits through bits_bytes.py

rtl_433 -f 433.20Mhz -s 1024k -S unknown

*/

#include <RadioLib.h>

#define LORA_SCK      5
#define LORA_MISO     19
#define LORA_MOSI     27
#define LORA_SS       18
#define LORA_RST      14
#define LORA_DIO0     26
#define LORA_DIO1     35
#define LORA_DIO2     25

// IP 63AA
//byte on_msg[] = { 0x63, 0xAA, 0x01, 0xA5/*0x5A*/, 0x12, 0x16/*0x11*/, 0x09, 0x01, 0x01, 0xA5, 0x71/*0x81*/ };
//byte off_msg[] = { 0x63, 0xaa, 0x1, 0x5a, 0x12, 0x13, 0x9, 0x1, 0x1, 0xa5, 0x87 };

// IP 71FE
byte on_msg[] = { 0x71, 0xfe, 0x1, 0xa5, 0x12, 0x14, 0x8, 0x1, 0x1, 0xa5, 0xd0 };
byte off_msg[] = { 0x71, 0xfe, 0x1, 0x5a, 0x12, 0x10, 0x8, 0x1, 0x1, 0xa5, 0x61 };

SX1278 radio = new Module (LORA_SS, LORA_DIO0, LORA_RST, LORA_DIO1);

void setup() {
  Serial.begin(9600);

  // initialize SX1278 FSK modem with default settings
  Serial.print(F("[SX1278] Initializing ... "));
  // First peak at 433.238, second at 433.260
  int state = radio.beginFSK(433.244, 2, 22/2, 125.0, 10, 32, false);
  state = radio.setDataShaping(RADIOLIB_SHAPING_NONE);
  state = radio.setCRC(false);
  state = radio.fixedPacketLengthMode(15);
  uint8_t syncWord[] = {0xAA, 0x20, 0x58, 0x9, 0x55, 0x1, 0xa0};
  state = radio.setSyncWord(syncWord, 7);
  if (state == RADIOLIB_ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true);
  }

//  state = radio.transmitDirect();
//  if (state != RADIOLIB_ERR_NONE) {
//    Serial.println(F("[SX1278] Unable to start direct transmission mode, code "));
//    Serial.println(state);
//  }

}

void loop() {
  if (Serial.available() > 0) {
    const String s = Serial.readStringUntil('\n');
    if (s == "on") {
      radio.transmit(on_msg, 12);
    } else {
      radio.transmit(off_msg, 12);
    }
    Serial.print("finished sending: ");
    Serial.println(s);
  }
}
