#include <RF24.h>
#include <RF24Network.h>
#include <SPI.h>
RF24 radio(9, 10);               // nRF24L01 (CE,CSN)
RF24Network network(radio);      // Include the radio in the network
const uint16_t node2 = 02;   // Address of this node in Octal format ( 04,031, etc)
const uint16_t master = 00;    

const int voltage_sensor = A1;
const int current_sensor = A0;

float mVperAmp = 34.5; // use 100 for 20A Module and 66 for 30A Module
double mVperVOLT = 1.9; 
double Voltage_pp_CS = 0;
double VRMS_CS = 0;
double AmpsRMS = 0;
double Voltage_pp_VS = 0;
double VRMS_VS = 0;
double VoltRMS = 0;
double power = 0;
char var[50]; 


void setup(){ 
 Serial.begin(9600);
 SPI.begin();
  radio.begin();
  network.begin(90, node2);  //(channel, node address)
}
 
void loop(){
  network.update();
 
 Voltage_pp_CS = getVPP_CS();
 VRMS_CS = (Voltage_pp_CS/2.0) *0.707;  //root 2 is 0.707
 AmpsRMS = (VRMS_CS * 1000)/mVperAmp;
if(AmpsRMS<16)
 AmpsRMS=0;
  
 Voltage_pp_VS = getVPP_VS();
 VRMS_VS = (Voltage_pp_VS/2.0) *0.707;  //root 2 is 0.707
 VoltRMS = (VRMS_VS * 1000)/mVperVOLT;
 if(VoltRMS<50)
 VoltRMS=0;
 power = AmpsRMS*VoltRMS;
  String dbuff2="machine3";dbuff2+=",";
 dbuff2+=(String)power;dbuff2+="*";dbuff2+=(String)VoltRMS;dbuff2+="$";dbuff2+=(String)AmpsRMS;

 dbuff2.toCharArray(var, 50);
        RF24NetworkHeader header(master);     // (Address where the data is going)
  bool ok = network.write(header, &var, sizeof(var)); // Send the data
  delay(5000);
 Serial.println( VoltRMS);
 Serial.println(AmpsRMS);
 Serial.print(power);
 Serial.println(" Watt");
}
 
float getVPP_CS()
{
  float result;
  int readValue;             //value read from the sensor
  int maxValue = 0;          // store max value here
  int minValue = 1024;          // store min value here
  
   uint32_t start_time = millis();
   while((millis()-start_time) < 2000) //sample for 1 Sec
   {
       readValue = analogRead(current_sensor);
       // see if you have a new maxValue
       if (readValue > maxValue) 
       {
           /*record the maximum sensor value*/
           maxValue = readValue;
       }
       if (readValue < minValue) 
       {
           /*record the minimum sensor value*/
           minValue = readValue;
       }
   }
   
   // Subtract min from max
   result = ((maxValue - minValue) * 5.0)/1024.0;
      
   return result;
 }

 float getVPP_VS()
{
  float result;
  int readValue;             //value read from the sensor
  int maxValue = 0;          // store max value here
  int minValue = 1024;          // store min value here
  
   uint32_t start_time = millis();
   while((millis()-start_time) < 2000) //sample for 1 Sec
   {
       readValue = analogRead(voltage_sensor);
       // see if you have a new maxValue
       if (readValue > maxValue) 
       {
           /*record the maximum sensor value*/
           maxValue = readValue;
       }
       if (readValue < minValue) 
       {
           /*record the minimum sensor value*/
           minValue = readValue;
       }
   }
   
   // Subtract min from max
   result = ((maxValue - minValue) * 5.0)/1024.0;
      
   return result;
 }
