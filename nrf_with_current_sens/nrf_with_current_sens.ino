#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
RF24 radio(10, 9);               // nRF24L01 (CE,CSN)
RF24Network network(radio);      // Include the radio in the network
const uint16_t this_node = 00;   // Address of our node in Octal format ( 04,031, etc)
const uint16_t master00 = 00;    // Address of the other node in Octal format
const unsigned long interval = 10;  //ms  // How often to send data to the other unit
unsigned long last_sent;            // When did we last send?
String Data1 = "Machine1+";

void setup() {
  SPI.begin();
  radio.begin();
  network.begin(90, this_node);  //(channel, node address)
  radio.setDataRate(RF24_2MBPS);
}
void loop() {
  network.update();
  //===== Sending =====//
  //unsigned long now = millis();
 // if (now - last_sent >= interval) {   // If it's time to send a data, send it!
     int readValue;             //value read from the sensor
  int maxValue = 0;          // store max value here
  int minValue = 1024;          // store min value here
  
   uint32_t start_time = millis();
   while((millis()-start_time) < 1000) //sample for 1 Sec
   {
       readValue = analogRead(sensorIn);
       // see if you have a new maxValue
       if (readValue > maxValue) 
       {
           /*record the maximum sensor value*/
           maxValue = readValue;
       }
       if (readValue < minValue) 
       {
           /*record the maximum sensor value*/
           minValue = readValue;
       }
   }
   
   // Subtract min from max
   result = ((maxValue - minValue) * 5.0)/1024.0;
      
   return result;
   // unsigned long current = analogRead(A0);
   // unsigned long voltage = analogRead(A1);
   // unsigned long power = current*current;
   // unsigned long power_fac = 0.85;
    Data1 +=power;
    Data1 += "+";
    Data1 += power_fac;
    RF24NetworkHeader header(master00);   // (Address where the data is going)
    bool ok = network.write(header, &Data1, sizeof(Data1)); // Send the data
    last_sent = now;
  }
}
