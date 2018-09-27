#include <AFMotor.h>
#include <SoftwareSerial.h>

AF_DCMotor lm(1);
AF_DCMotor rm(2);

SoftwareSerial HC06(9,10);

void setup() {
  Serial.begin(9600);
  HC06.begin(9600);
  Serial.println("HC06 ready!");

  lm.setSpeed(0);
  rm.setSpeed(0);

  lm.run(RELEASE);
  rm.run(RELEASE);
  Serial.println("Motors ready!");
}

char c;
void loop() {
  if(HC06.available()){
    c = HC06.read();
    Serial.println(c);
    selector(c);
  }
}

void selector(char dir){
  switch(dir){
    case 'F':
      fd();
      break;
    case 'B':
      bd();
      break;
    case 'R':
      rt();
      break;
    case 'L':
      lt();
      break;
    case 'S':
      sp();
      break;
    default:
      sp();
      break;
  }
}

int f = FORWARD;
int b = BACKWARD;

void fd(){
  lm.run(f);
  rm.run(f);
  lm.setSpeed(200);
  rm.setSpeed(200);
}

void bd(){
  lm.run(b);
  rm.run(b);
  lm.setSpeed(200);
  rm.setSpeed(200);  
}

void lt(){
  lm.run(b);
  rm.run(f);
  lm.setSpeed(100);
  rm.setSpeed(100);
}

void rt(){
  lm.run(f);
  rm.run(b);
  lm.setSpeed(100);
  rm.setSpeed(100);
}

void sp(){
  lm.setSpeed(0);
  rm.setSpeed(0);
}
