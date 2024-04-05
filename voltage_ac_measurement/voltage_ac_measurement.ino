const int sensorIn = A0;
float mVperVOLT = 1.8; // use 100 for 20A Module and 66 for 30A Module
 
double Voltage = 0;
double VRMS = 0;
double vrms = 0;
 
void setup(){ 
 Serial.begin(9600);
}
 
void loop(){
 
 Voltage = getVPP();
 VRMS = (Voltage/2.0) *0.707;  //root 2 is 0.707
 vrms = (VRMS * 1000)/mVperVOLT;
 Serial.print(vrms);
 Serial.println(" Volts RMS");
}
 
float getVPP()
{
  float result;
  int readValue;             //value read from the sensor
  int maxValue = 0;          // store max value here
  int minValue = 1024;          // store min value here
  
   uint32_t start_time = millis();
   while((millis()-start_time) < 5000) //sample for 1 Sec
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
           /*record the minimum sensor value*/
           minValue = readValue;
       }
   }
   
   // Subtract min from max
   result = ((maxValue - minValue) * 5.0)/1024.0;
      
   return result;
 }
