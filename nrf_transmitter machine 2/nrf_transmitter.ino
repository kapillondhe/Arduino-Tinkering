#include <RF24.h>
#include <RF24Network.h>
#include <SPI.h>
RF24 radio(9, 10);               // nRF24L01 (CE,CSN)
RF24Network network(radio);      // Include the radio in the network
const uint16_t node2 = 02;   // Address of this node in Octal format ( 04,031, etc)
const uint16_t master = 00;    
const int sensor = A0;
int mVperAmp = 66; // use 100 for 20A Module and 66 for 30A Module
double Voltage = 0;
double VRMS = 0;
double AmpsRMS = 0;
double pow_fac;
//String data="Bulb"; 
char var[50]; 
void setup() {
  Serial.begin(9600);
  SPI.begin();
  radio.begin();
  network.begin(90, node2);  //(channel, node address)
}
void loop() {
  network.update();
  Voltage = getVPP();
 VRMS = (Voltage/2.0) *0.707; 
 AmpsRMS = (VRMS * 1000)/mVperAmp;
  String data =String('"'); data +="+";data +='"';data +="machine2"; data +='"';data +="+";data +='"';
   data +="&power="; data +='"';data +="+";data +='"'; data +=AmpsRMS;data +='"';data +="+";data +='"'; 
   data +="&pf=";data +='"';data +="+";data +='"'; data +=pow_fac;

 
 data.toCharArray(var, 50);
        RF24NetworkHeader header(master);     // (Address where the data is going)
  bool ok = network.write(header, &var, sizeof(var)); // Send the data
 //}   
  
}
float getVPP()
{
  float result;
  
  int readValue;             //value read from the sensor
  int maxValue = 0;          // store max value here
  int minValue = 1024;          // store min value here
  
   uint32_t start_time = millis();
   while((millis()-start_time) < 1000) //sample for 1 Sec
   {
       readValue = analogRead(sensor);
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
 }
