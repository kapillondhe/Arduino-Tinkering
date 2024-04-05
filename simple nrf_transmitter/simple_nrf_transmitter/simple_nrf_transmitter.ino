#include <RF24.h>
#include <RF24Network.h>
#include <SPI.h>
RF24 radio(9, 10);               // nRF24L01 (CE,CSN)
RF24Network network(radio);      // Include the radio in the network
const uint16_t master= 00;   // Address of this node in Octal format ( 04,031, etc)
const uint16_t node1 = 01;    
int var;  
void setup() {
  Serial.begin(9600);
  SPI.begin();
  radio.begin();
  network.begin(90, node1);  //(channel, node address)
}
void loop() {
  network.update();
  // Read the potentiometer value
 // unsigned long angleValue = map(512, 0, 1023, 0, 180); // Convert the value to 0-180
 if(Serial.available()){
        var = Serial.read();
        RF24NetworkHeader header(master);     // (Address where the data is going)
  bool ok = network.write(header, &var, sizeof(var)); // Send the data
 }   
  
}
