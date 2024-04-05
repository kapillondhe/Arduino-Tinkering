#include <RF24.h>
#include <SPI.h>
RF24 radio(9, 10);

void setup(void) {
  // put your setup code here, to run once:
  radio.begin();
  radio.setPALevel(RF24_PA_MAX);
  radio.setChannel(0x76);
  radio.openWritingPipe(0xF0F0F0F0E1LL);
  radio.enableDynamicPayloads();
  radio.powerUp();

}

void loop(void) {
  // put your main code here, to run repeatedly:
const char text[]="hello world";
radio.write(&text,sizeof(text));
delay(10);
}
