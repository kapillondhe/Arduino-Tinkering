int a = 0;
void setup()
{
  Serial.begin(9600);
int a = 0;
}

void loop() 
{
   if (Serial.available() > 0)
  {a = Serial.read();
  switch(a)
  { 
    case (1) : Serial.println("Done");
    case 2 : Serial.println("Ok");
  }
  
  }

}
