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
double midpointcs;
double midpointvs;
unsigned long factor1;
struct A{
  double vpp;
  double midpt;
};
struct A CS;
struct A VS;
void setup(){ 
 Serial.begin(9600);
}
 
void loop(){
 CS=getVPP_CS();
 Voltage_pp_CS = CS.vpp;
 VRMS_CS = (Voltage_pp_CS/2.0) *0.707;  //root 2 is 0.707
 AmpsRMS = (VRMS_CS * 1000)/mVperAmp;
 midpointcs=CS.midpt;
 
  VS=getVPP_VS();
 Voltage_pp_VS = VS.vpp;
 VRMS_VS = (Voltage_pp_VS/2.0) *0.707;  //root 2 is 0.707
 VoltRMS = (VRMS_VS * 1000)/mVperVOLT;
 midpointvs=VS.midpt;
 if(VoltRMS<50)
 VoltRMS=0;
 power = AmpsRMS*VoltRMS;

 //Serial.println(midpointcs);
 // Serial.println(midpointvs);
 factor1 =powfac(midpointcs,midpointvs);
// Serial.println( VoltRMS);
 //Serial.println(AmpsRMS);
 //Serial.println(power);
 //Serial.println(" Watt");
  Serial.println(factor1);
 // Serial.println(midpointcs);
 // Serial.println(midpointvs);
}
 
struct A getVPP_CS()
{
  struct A result;
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
   result.vpp = ((maxValue - minValue) * 5.0)/1024.0;
   result.midpt=( maxValue+minValue)/2;
   return result;
 }

 struct A getVPP_VS()
{
  struct A result;
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
    result.vpp = ((maxValue - minValue) * 5.0)/1024.0;
   result.midpt= ( maxValue+minValue)/2;
   return result;
 }

 float powfac(double midpointcs , double midpointvs)
 {
  float factor=1;
  int readValue1;
  int readValue2;
  int a=1,b=1,c=1,d=1;
  unsigned long first,last;
  readValue1 = analogRead(voltage_sensor);
  readValue2 = analogRead(current_sensor);
  while(d){
    //Serial.println("pass1");
   if(analogRead(current_sensor)>midpointcs)
      { 
         while(c){ //Serial.println("pass2");
        if(analogRead(voltage_sensor)>midpointvs)
        {
           while(b){ // Serial.println("pass3");
              while(a){ //Serial.println("pass4");
                 if(analogRead(current_sensor)==midpointcs)
                       { 
                        first=micros();
                         a=0;
                       }
                      }
               if(analogRead(voltage_sensor)==midpointvs)
                {
                  //Serial.println("pass5");
                  last=micros();
                  b=0;c=0;d=0;
                }
             }
  
       }
      }
   }}
   factor=last-first;
   return factor;}

