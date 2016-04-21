#include <ESP8266WiFi.h>

//https://github.com/tzapu/WiFiManager
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

#include <Phant.h>

#define MINUTE_MICROS 60 * 1000 * 1000

#define SAMPLES 100
#define MAGIC 0.09775171065 // reading*100/1023 -> 0-100C 0-1023

const char* host = "data.sparkfun.com";
const int httpPort = 80;
Phant phant(host, "q5LJyVxgaGiqgO5NzpAN", "BVoBx67jGqHypDxEkl2E");

void setup()
{ 
  //WiFiManager
  //Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;

  //sets timeout until configuration portal gets turned off
  //useful to make it all retry or go to sleep in seconds
  wifiManager.setTimeout(180);

  //fetches ssid and pass and tries to connect
  //if it does not connect it starts an access point with the specified name
  //here  "AutoConnectAP"
  //and goes into a blocking loop awaiting configuration
  if(!wifiManager.autoConnect("ESP8266")) {
    ESP.deepSleep(5 * MINUTE_MICROS);
  }
}

void loop()
{
  float temp = 0;

  for (int i = 0; i <= SAMPLES; i++) {
    temp += analogRead(A0) * MAGIC;
    delay(300);
  }

  temp = temp / SAMPLES;

  // convert to string
  char buf[16];
  const String strTemp = dtostrf(temp, 4, 1, buf);

  // Sending to the server
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  if (client.connect(host, httpPort)) {
    phant.add("temp", strTemp);
    client.print(phant.post());
  }

  ESP.deepSleep(MINUTE_MICROS);
}
