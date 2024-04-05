const int voltage_sensor = A1;
const int current_sensor = A0;
int i=0;
float CS[100];
float VS[100];
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
struct A CS1;
struct A VS1;
void setup(){ 
 Serial.begin(9600);
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

float powfac(double midpointcs , double midpointvs){
  int a=1,b=1,c=1,d=1;
  unsigned long first,last;
  float factor;
  i=0;
  while(d){
    
    //Serial.println("pass1");
   if(CS[i]>midpointcs)
      { 
         while(c){ //Serial.println("pass2");
        if(VS[i]>midpointvs)
        {
           while(b){ // Serial.println("pass3");
              while(a){ //Serial.println("pass4");
                 if(CS[i]==midpointcs)
                       { 
                        first=millis();
                         a=0;
                       }
                       i++; 
                      }
               if(VS[i]==midpointvs)
                {
                  //Serial.println("pass5");
                  last=micros();
                  b=0;c=0;d=0;
                }i++; 
             }
  
       }
      }
      } i++;  
      }

factor=last-first;
   return factor;
}

void loop(){
   CS1=getVPP_CS();
   midpointcs=CS1.midpt;
    VS1=getVPP_VS();
     Voltage_pp_VS = VS1.vpp;
   CS[i] = analogRead(current_sensor);
   VS[i] = analogRead(voltage_sensor);
   i++;
   if(i==100)
   {  factor1 =powfac(midpointcs,midpointvs);
      Serial.println(factor1);
   }
    
}
