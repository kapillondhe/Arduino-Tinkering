      volatile unsigned long time1;
    volatile unsigned long time2;
    unsigned long time3;
    volatile float ps;
    volatile boolean data_available = false;
    
    void setup()
          {
          Serial.begin(115200);
          Serial.println();
          pinMode(PD2,INPUT);   
          pinMode(PD3,INPUT);  
          attachInterrupt(PD2,in1,RISING);     //enable ISR1 for voltage signal at rising from zero crossing 
          attachInterrupt(PD3,in2,RISING);     //enable ISR2 for current signal at rising from zero crossing
          interrupts();
          }
    void in1()
    {
               time1=micros();    //measure time in micro second for first zero crossing ISR1
    }
    void in2()
    {
               time2=micros();    //measure time in micro second for first zero crossing ISR2
               data_available = true;
    }
           
    void loop()
    {
               if (data_available == true)
               {
                  time3=time2-time1;
                  ps = ((time3*360.0)*50/1000000); //calculate the phase shift from measured time difference
                  Serial.print("Time1=");
                  Serial.println(time1);
                  Serial.print("Time2=");
                  Serial.println(time2);
                  Serial.print("Phase Shift = ");
                  Serial.println(ps,6);
                  Serial.print("degree\n\n");
                  data_available = false;
               }
    }
