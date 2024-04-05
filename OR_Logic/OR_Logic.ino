int out = 3;
int pin1 = 4;
int pin2 = 5;
int val1 = 0;
int val2=0;

void setup()
  {
 
      Serial.begin(9600);
      pinMode(out, OUTPUT);
       pinMode(pin1, INPUT);
        pinMode(pin2, INPUT);
  }

void loop() 
  {
      val1=digitalRead(pin1);
      val2=digitalRead(pin2);
      if(val1==1 || val2==1)
      {
        digitalWrite(out,HIGH);
      }
      else
      digitalWrite(out,LOW);
        Serial.println(val1);
        Serial.println(val2);
       delay(0);
        
  }
