#include <Servo.h>

Servo servo1;
int pos = 0;

void setup(){
  Serial.begin(9600);
  servo1.attach(8);
}

void loop(){
  if(Serial.available()){
    pos = Serial.parseInt();
  }
  servo1.write(pos);
  delay(20);
}
