#include <Servo.h>

Servo esc1;
//Servo esc2;
//Servo esc3;

void setup() {
  esc1.attach(8);
  Serial.begin(9600);
  Serial.println("ESC attached!");
}

int pos;
void loop() {
  setSpeed1(100);
}

void setSpeed1(int speed){
  int angle = map(speed, 0, 100, 57, 150); //Sets servo positions to different speeds esc.write;
  esc1.write(angle);
}

//void setSpeed2(int speed){
//  int angle = map(speed, 0, 100, 57, 150); //Sets servo positions to different speeds esc.write;
//  esc2.write(angle);
//}

//void setSpeed3(int speed){
//  int angle = map(speed, 0, 100, 57, 150); //Sets servo positions to different speeds esc.write;
//  esc3.write(angle);
//}
