/*
 Example sketch for the PS4 Bluetooth library - developed by Kristian Lauszus
 For more information visit my blog: http://blog.tkjelectronics.dk/ or
 send me an e-mail:  kristianl@tkjelectronics.com
 */

#include <PS4BT.h>
#include <usbhub.h>
#include <stdio.h>
#include <math.h>
#include <Servo.h>


#include <SoftwareSerial.h>

//AF_DCMotor lm(1);
//AF_DCMotor rm(2);


// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

USB Usb;
//USBHub Hub1(&Usb); // Some dongles have a hub inside
BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so

/* You can create the instance of the PS4BT class in two ways */
// This will start an inquiry and then pair with the PS4 controller - you only have to do this once
// You will need to hold down the PS and Share button at the same time, the PS4 controller will then start to blink rapidly indicating that it is in pairing mode
PS4BT PS4(&Btd, PAIR);

// After that you can simply create the instance like so and then press the PS button on the device
//PS4BT PS4(&Btd);

bool printAngle, printTouch;
uint8_t oldL2Value, oldR2Value;



int x;
int y;
int p1;
int p2;
int p3;


int r1;
int r2;
String r3;


String line = "0,0,1,2,3";


Servo esc1;
Servo esc2;
Servo esc3;
Servo esc0;


int power;



void setup() {
  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); // Halt
  }
  Serial.print(F("\r\nPS4 Bluetooth Library Started"));
  Serial.print(F("\n"));

  esc0.attach(7);
  esc1.attach(8);
  esc2.attach(9);
  esc3.attach(10);
  //Serial.begin(9600);
  Serial.println("ESC attached!");

  
}
//convert String to char*
char* sc(String command){
    if(command.length()!=0){
        char *p = const_cast<char*>(command.c_str());
        return p;
    }
}

//split the data into x, y and string of 3 vectors
void splitData(char data[]){
  String string[5];
  char* token = strtok(data, ",");
  int i = 0;
  while(token!= NULL){
    string[i] = token;
    i++;
  }
  r1 = string[0].toInt();
  r2 = string[1].toInt();
  r3 = string[2] + "," + string[3] + "," + string[4];
}

/*
//store x, y and string of 3 vectors to array
void storeData(int a, int b, String c){
  if(a >=0 && b >=0){
    table1[a][b] = sc(c);
  }else if(a > 0 && b < 0){
    table2[a][b + 128] = sc(c);
  }else if(a <= 0 && b <= 0){
    table3[a+128][b+128] = sc(c);
  }else if(a < 0 && b > 0){
    table4[a + 128][b] = sc(c);
  }
}

//receive raw input (x,y) from controller and return the string of 3 vectors
String getData(int x, int y){
  String result = "";
  if(x >= 128 && y >= 129){
    result = table1[x-128][y-129];
  }else if(x > 128 && y < 127){
    result = table2[x-128][y];
  }else if(x <= 127 && y <= 126){
    result = table3[x][y];
  }else if(x <= 127 && y >= 129){
    result = table4[x][y-129];
  }
  return result;
}*/

/*
///chandler's code
double radians(double x){
  return x*M_PI/180.0;
}*/

struct Tuple {
    int a, b, c;
};
struct Tuple calc(int Fx, int Fy){
  struct Tuple result;
  int maxSpeed = 100;
  float tang = fabs((float)Fy/(float)Fx);
  if(Fx > -10 && Fx < 10 && Fy > -10 && Fy < 10){
    result.a = 0;
    result.b = 0;
    result.c = 0;
    return result;
  }
  else if (tang >= tan(radians(67.5)) && Fy >= 0){
    result.a = maxSpeed;
    result.b = maxSpeed;
    result.c = 0;
    return result;
  }
  else if (tang < tan(radians(67.5)) && tang >= tan(radians(22.5)) && Fy >= 0 && Fx >= 0){
    result.a = maxSpeed/sqrt(2);
    result.b = maxSpeed/sqrt(2);
    result.c = 0;
    return result;
  }
  else if (tang < tan(radians(22.5)) && Fx >= 0){
    result.a = 0;
    result.b = 2*maxSpeed/sqrt(3);
    result.c = maxSpeed/sqrt(3);
    return result;
  }
  else if (tang < tan(radians(67.5)) && tang >= tan(radians(22.5)) && Fy < 0 && Fx >= 0){
    result.a = 2*maxSpeed/sqrt(6);
    result.b = 0;
    result.c = (maxSpeed/sqrt(2)+maxSpeed/sqrt(6));
    return result;
  }
  else if (tang >= tan(radians(67.5)) && Fy < 0){
    result.a = 0;
    result.b = 0;
    result.c = maxSpeed;
    return result;
  }
  else if (tang < tan(radians(67.5)) && tang >= tan(radians(22.5)) && Fy < 0 && Fx < 0){
    result.a = 2*maxSpeed/sqrt(6);
    result.b = 0;
    result.c = (maxSpeed/sqrt(2)+maxSpeed/sqrt(6));
    return result;
  }
  else if (tang < tan(radians(22.5)) && Fx < 0){
    result.a = 2*maxSpeed/sqrt(3);
    result.b = 0;
    result.c = maxSpeed/sqrt(3);
    return result;
  }
  else if (tang < tan(radians(67.5)) && tang >= tan(radians(22.5)) && Fy >= 0 && Fx < 0){
    result.a = maxSpeed/sqrt(2);
    result.b = maxSpeed/sqrt(2);
    result.c = 0;
    return result;
  }
}



void setSpeed0(int speed){
  int angle = map(speed, 0, 100, 57, 150); //Sets servo positions to different speeds esc.write;
  esc0.write(angle);
}

void setSpeed1(int speed){
  int angle = map(speed, 0, 100, 57, 150); //Sets servo positions to different speeds esc.write;
  esc1.write(angle);
}

void setSpeed2(int speed){
  int angle = map(speed, 0, 100, 57, 150); //Sets servo positions to different speeds esc.write;
  esc2.write(angle);
}

void setSpeed3(int speed){
  int angle = map(speed, 0, 100, 57, 150); //Sets servo positions to different speeds esc.write;
  esc3.write(angle);
}


struct Tuple temp;


void loop() {
  setSpeed1(100);
    setSpeed2(100);
  setSpeed3(100);
  setSpeed0(100);

  delay(2000);
  Usb.Task();

  
  
  

  if (PS4.connected()) {
    //our code

        temp = calc(PS4.getAnalogHat(LeftHatX) - 128, PS4.getAnalogHat(LeftHatY) - 128);
        setSpeed1(temp.a);
        setSpeed2(temp.b);
        setSpeed3(temp.c);
        setSpeed0(100);

        


    /*if(PS4.getButtonPress(LEFT)){


      setSpeed1(10);
      delay(3000);
      setSpeed1(0);
      delay(3000);

      
     
    }*/
    
    /*String paolo = getData(PS4.getAnalogHat(LeftHatX), PS4.getAnalogHat(LeftHatY));
    String paolo = getData(0,0);
    char* chandler = sc(paolo);
    char* token = strtok(chandler, ",");
    String yen[3];
    int i = 0;
    while(token!= NULL){
      yen[i] = token;
      i++;
     }
     p1 = yen[0].toInt();
     p2 = yen[1].toInt();
     p3 = yen[2].toInt();
     Serial.print(p1);
     Serial.print(F("\n"));
     Serial.print(p2);
     Serial.print(F("\n"));
     Serial.print(p3);
     Serial.print(F("\n"));
     */

    
    Serial.print(F("Power 1:\t"));
    Serial.print(temp.a);
    Serial.print(F("\tPower 2:\t"));
    Serial.print(temp.b);
    Serial.print(F("\tPower 3:\t"));
    Serial.print(temp.c);
    Serial.print(F("\n\n"));
    

/*
  
    //moving car

    //forward
    if(PS4.getButtonPress(UP)){
      if (PS4.getButtonPress(LEFT)) {
        lm.setSpeed(0);
        lm.run(RELEASE);
        rm.run(f);
        rm.setSpeed(100);
      }
      if (PS4.getButtonPress(RIGHT)){
        rm.setSpeed(0);
        rm.run(RELEASE);
        lm.run(f);
        lm.setSpeed(100);
      }
      else fd();
    }
    //left rotation
    else if(PS4.getButtonPress(LEFT)){


      setSpeed1(10);
      delay(3000);
      setSpeed1(0);
      delay(3000);

      
      lt();
    }
    //right rotation
    else if(PS4.getButtonPress(RIGHT)){
      rt();
    }
    //backwards
    else if(PS4.getButtonPress(DOWN)){
      bd();
    }
    //stop if not button is being held
    else {
      sp();
    }
    
*/
    /*
    //moving forward
    if(PS4.getAnalogHat(LeftHatY) < 64){
      p1 = 0;
      p2 = 50;
      p3 = 50;
      Serial.print(F("power 1 is"));
      Serial.print(p1);
     Serial.print(F("\npower 2 is"));
     Serial.print(p2);
     Serial.print(F("\npower 3 is"));
     Serial.print(p3);
     Serial.print(F("\n"));
    }


    //moving left
    if(PS4.getAnalogHat(LeftHatX) < 64){
      p1 = 50;
      p2 = 87;
      p3 = 0;
      Serial.print(F("power 1 is"));
      Serial.print(p1);
     Serial.print(F("\npower 2 is"));
     Serial.print(p2);
     Serial.print(F("\npower 3 is"));
     Serial.print(p3);
     Serial.print(F("\n"));
    }


    //moving back
    if(PS4.getAnalogHat(LeftHatY) > 192){
      p1 = 100;
      p2 = 0;
      p3 = 0;
      Serial.print(F("power 1 is"));
      Serial.print(p1);
     Serial.print(F("\npower 2 is"));
     Serial.print(p2);
     Serial.print(F("\npower 3 is"));
     Serial.print(p3);
     Serial.print(F("\n"));
    }


    //moving right
    if(PS4.getAnalogHat(LeftHatX) > 192){
      p1 = 50;
      p2 = 0;
      p3 = 87;
      Serial.print(F("power 1 is"));
      Serial.print(p1);
     Serial.print(F("\npower 2 is"));
     Serial.print(p2);
     Serial.print(F("\npower 3 is"));
     Serial.print(p3);
     Serial.print(F("\n"));
    }
    */
      
    
    if (PS4.getAnalogHat(LeftHatX) > 137 || PS4.getAnalogHat(LeftHatX) < 117 || PS4.getAnalogHat(LeftHatY) > 137 || PS4.getAnalogHat(LeftHatY) < 117 || PS4.getAnalogHat(RightHatX) > 137 || PS4.getAnalogHat(RightHatX) < 117 || PS4.getAnalogHat(RightHatY) > 137 || PS4.getAnalogHat(RightHatY) < 117) {
      //Serial.print(F("\r\nLeftHatX: "));
      //Serial.print(PS4.getAnalogHat(LeftHatX));
      //Serial.print(F("\tLeftHatY: "));
      //Serial.print(PS4.getAnalogHat(LeftHatY));
      //Serial.print(F("\tRightHatX: "));
      //Serial.print(PS4.getAnalogHat(RightHatX));
      //Serial.print(F("\tRightHatY: "));
      //Serial.print(PS4.getAnalogHat(RightHatY));




      
    }

    if (PS4.getAnalogButton(L2) || PS4.getAnalogButton(R2)) { // These are the only analog buttons on the PS4 controller
      Serial.print(F("\r\nL2: "));
      Serial.print(PS4.getAnalogButton(L2));
      Serial.print(F("\tR2: "));
      Serial.print(PS4.getAnalogButton(R2));
    }
    if (PS4.getAnalogButton(L2) != oldL2Value || PS4.getAnalogButton(R2) != oldR2Value) // Only write value if it's different
      PS4.setRumbleOn(PS4.getAnalogButton(L2), PS4.getAnalogButton(R2));
    oldL2Value = PS4.getAnalogButton(L2);
    oldR2Value = PS4.getAnalogButton(R2);

    if (PS4.getButtonClick(PS)) {
      Serial.print(F("\r\nPS"));
      PS4.disconnect();
    }
    else {
      if (PS4.getButtonClick(TRIANGLE)) {
        Serial.print(F("\r\nTraingle"));
        PS4.setRumbleOn(RumbleLow);
      }
      if (PS4.getButtonClick(CIRCLE)) {
        Serial.print(F("\r\nCircle"));
        PS4.setRumbleOn(RumbleHigh);
      }
      if (PS4.getButtonClick(CROSS)) {
        Serial.print(F("\r\nCross"));
        PS4.setLedFlash(10, 10); // Set it to blink rapidly
      }
      if (PS4.getButtonClick(SQUARE)) {
        Serial.print(F("\r\nSquare"));
        PS4.setLedFlash(0, 0); // Turn off blinking
      }

      if (PS4.getButtonClick(UP)) {
        Serial.print(F("\r\nUp"));
        PS4.setLed(Red);
      } if (PS4.getButtonClick(RIGHT)) {
        Serial.print(F("\r\nRight"));
        PS4.setLed(Blue);
      } if (PS4.getButtonClick(DOWN)) {
        Serial.print(F("\r\nDown"));
        PS4.setLed(Yellow);
      } if (PS4.getButtonClick(LEFT)) {
        Serial.print(F("\r\nLeft"));
        PS4.setLed(Green);
      }

      if (PS4.getButtonClick(L1))
        Serial.print(F("\r\nL1"));
      if (PS4.getButtonClick(L3))
        Serial.print(F("\r\nL3"));
      if (PS4.getButtonClick(R1))
        Serial.print(F("\r\nR1"));
      if (PS4.getButtonClick(R3))
        Serial.print(F("\r\nR3"));

      if (PS4.getButtonClick(SHARE))
        Serial.print(F("\r\nShare"));
      if (PS4.getButtonClick(OPTIONS)) {
        Serial.print(F("\r\nOptions"));
        printAngle = !printAngle;
      }
      if (PS4.getButtonClick(TOUCHPAD)) {
        Serial.print(F("\r\nTouchpad"));
        printTouch = !printTouch;
      }

      if (printAngle) { // Print angle calculated using the accelerometer only
        Serial.print(F("\r\nPitch: "));
        Serial.print(PS4.getAngle(Pitch));
        Serial.print(F("\tRoll: "));
        Serial.print(PS4.getAngle(Roll));
      }

      if (printTouch) { // Print the x, y coordinates of the touchpad
        if (PS4.isTouching(0) || PS4.isTouching(1)) // Print newline and carriage return if any of the fingers are touching the touchpad
          Serial.print(F("\r\n"));
        for (uint8_t i = 0; i < 2; i++) { // The touchpad track two fingers
          if (PS4.isTouching(i)) { // Print the position of the finger if it is touching the touchpad
            Serial.print(F("X")); Serial.print(i + 1); Serial.print(F(": "));
            Serial.print(PS4.getX(i));
            Serial.print(F("\tY")); Serial.print(i + 1); Serial.print(F(": "));
            Serial.print(PS4.getY(i));
            Serial.print(F("\t"));
          }
        }
      }
    }
  }
}
