#include <RF24.h>
#include <RF24Network.h>
#include <SPI.h>
RF24 radio(9, 10);               // nRF24L01 (CE,CSN)
RF24Network network(radio);      // Include the radio in the network
const uint16_t this_node = 01;   // Address of our node in Octal format ( 04,031, etc)

void setup() {
  Serial.begin(9600);
  SPI.begin();
  radio.begin();
  network.begin(90, this_node); //(channel, node address)
 
}
void loop() {
  network.update();
  while ( network.available() ) {     // Is there any incoming data?
    RF24NetworkHeader header;
   char incomingData;
    network.read(header, &incomingData, sizeof(incomingData)); // Read the incoming data
    //myservo.write(incomingData);  // tell servo to go to a particular angle
    Serial.println(incomingData);
  }
}
