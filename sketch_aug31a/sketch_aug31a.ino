import processing.serial.*;
import cc.arduino.*;

Arduino arduino; //creates arduino object

color back = color(64, 218, 255); //variables for the 2 colors

int sensor= 0;
int read;

float value;


void setup() {
  size(800, 600);
  arduino = new Arduino(this, Arduino.list()[0], 57600); //sets up arduino
    arduino.pinMode(sensor, Arduino.INPUT);//setup pins to be input (A0 =0?)
   
    background(back);
}

void draw() {
 
 
  read=arduino.analogRead(sensor);
  background(back);
  println (read);
  value=map(read, 0, 680, 0, width); //use to callibrate  
  ellipse(value, 300,30, 30);
  

}

