#include <Servo.h>

Servo esc1;

void setup() {
  esc.attach(8);
}

void loop() {
  setSpeed(70);
  delay(1000);
  setSpeed(50);
  delay(500);
}

void setSpeed(int speed){
  int angle = map(speed, 0, 100, 57, 150); //Sets servo positions to different speeds esc.write;
  esc.write(angle);
}
