#include <IRremote.h>

IRsend irsend;
void setup()
{
}

void loop() {
  for (int i=0; i < 3; i++){
    irsend.sendSony(0xb4b8f, 20);
    delay(40);
  }
  delay(5000);
}
