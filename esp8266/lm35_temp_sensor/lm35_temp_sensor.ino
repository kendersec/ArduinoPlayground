#include <Phant.h>
#include <ESP8266WiFi.h>

#define SAMPLES 100
#define MAGIC 0.09775171065 // reading*100/1023 -> 0-100C 0-1023

const char* host     = "data.sparkfun.com";
const char* ssid     = "ASUS";
const char* password = "9RAy2SefacRE";

Phant phant(host, "q5LJyVxgaGiqgO5NzpAN", "BVoBx67jGqHypDxEkl2E");

void setup(void) {
  Serial.begin(115200);

  delay(10);

  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {

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
  Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  phant.add("temp", strTemp);
  
  Serial.println("----HTTP POST----");
  const String req = phant.post();
  client.print(req);
  Serial.println(req);

  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line); // Trying to avoid using serial
  }
}
