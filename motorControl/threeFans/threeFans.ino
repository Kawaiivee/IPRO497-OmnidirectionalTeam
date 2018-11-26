#include <Servo.h>

#define NUMMOTORS 3
typedef struct MotorDef{
    Servo Motor; 
    int Pin;
};

MotorDef Motors[NUMMOTORS];

typedef struct ESCSettingsDef{
  int Low;
  int High;
};

ESCSettingsDef ESCSettings; 

//#define PROGRAM_MODE
//#define THROTTLE_MODE
#define NORMAL_MODE

int CurrentSpeed;
int Step = 10;


#define ESC_HIGH_DEFAULT 200
#define ESC_LOW_DEFAULT 20

void setup(){
  Serial.begin(9600);
  Serial.println("Setup: Serial port communication at 9600bps");
  
  Motors[0].Pin =  8;
  Motors[1].Pin =  9;
  Motors[2].Pin =  10;

    for(int i = 0; i < NUMMOTORS; i++){
      int pin = Motors[i].Pin;
      Motors[i].Motor.attach(pin);
    }

  ESCSettings.Low = ESC_LOW_DEFAULT;
  ESCSettings.High = ESC_HIGH_DEFAULT;
}

// Read low/high speed for the ESC
void ReadLHSpeed(){
  Serial.println("Enter Low Speed");
  delay(10);
  while(!Serial.available()){}
  ESCSettings.Low = Serial.parseInt();
  Serial.println("Low Speed is");
  Serial.print(ESCSettings.Low);
  Serial.println("\nEnter High Speed\n");
  delay(10);
  while(!Serial.available()){}
  ESCSettings.High = Serial.parseInt();
  Serial.println("High Speed is");
  Serial.print(ESCSettings.High);
  Serial.println("\n");
}

void SetThrottleRange(){
  Serial.println("In Set Throttle Range mode");
  for(int i = 0; i < NUMMOTORS; i++){
    Motors[i].Motor.write(ESCSettings.High);
  }
  Serial.println("Connect the ESC now. After connecting the ESC, you should hear the ESC startup tones. Shortly afterwards, you should hear two beeps indicating that the ESC has registered the high throttle value. Immediately after hearing the two beeps, push any key. If you don't do so in 5 sec, the ESC will go into program mode");
  // Wait for user input
  while(!Serial.available()){
  }
  Serial.read();

  Serial.println("\nSetting the low throttle setting. If this happens successfully, you should hear several beeps indicating the input voltage supplied to the ESC followed by a long beep indicating that the low throttle has been set. After this point, push any key to proceed, your ESC is ready to be used");
  for (int i = 0; i < NUMMOTORS; i++)
  {
    Motors[i].Motor.write(ESCSettings.Low);
  }

  // Wait for user input
  while(!Serial.available()){
  }
  Serial.read();
}

void ProgramESC(){
  Serial.println("In program mode");

  for (int i = 0; i < NUMMOTORS; i++){
    Motors[i].Motor.write(ESCSettings.High);
  }

  // After the user inputs a key stroke, set the throttle to low
  while(!Serial.available()){
  }
  Serial.read();

  for(int i = 0; i < NUMMOTORS; i++){
    Motors[i].Motor.write(ESCSettings.Low);
  }

  // After the user inputs a key stroke, set the throttle to high. This will set the value of the setting.
  while(!Serial.available()){
  }
  Serial.read();

  for(int i = 0; i < NUMMOTORS; i++){
    Motors[i].Motor.write(ESCSettings.High);
  }
  delay(2000);
  Serial.println("Programming the ESC finished, you can power off the ESC now");
}

// Increase the speed of the motor from low to high as set by the user
void Run(){
  // Send a low signal initially for normal mode
  for(int i = 0; i < NUMMOTORS; i++){
    Motors[i].Motor.write(ESCSettings.Low);
  }
  Serial.println("Running ESC");
  Serial.println("Step = ");
  Serial.print(Step);
  Serial.println("\nPress 'u' to increase speed, 'd' to reduce speed");

  CurrentSpeed = ESCSettings.Low;
  while(1){
    while(!Serial.available()){
    }
    char currentChar = Serial.read();
    if(currentChar == 'u'){
      Serial.println("\nIncreasing motor speed by step");
      if(CurrentSpeed + Step < ESCSettings.High) {
        CurrentSpeed = CurrentSpeed + Step;
        Serial.println("New speed = ");
        Serial.print(CurrentSpeed);
      }

      else{
        Serial.println("\nMax speed reached\n");
      }
    }
    if(currentChar == 'd'){
      Serial.println("\nDecreasing motor speed by step\n");
      if(CurrentSpeed - Step >= ESCSettings.Low){
        CurrentSpeed = CurrentSpeed - Step;
        Serial.println("New speed = ");
        Serial.print(CurrentSpeed);
      }

      else{
        Serial.println("\nMin speed reached\n");
      }
    }
    if(currentChar == 'e'){
      Serial.println("\nStopping Motors\n");
      CurrentSpeed = ESCSettings.Low;
    }
    for (int i = 0; i < NUMMOTORS; i++){
      Motors[i].Motor.write(CurrentSpeed);
    }
  }
}

void loop(){
#ifdef NORMAL_MODE
  Run();
#elif defined THROTTLE_MODE
  SetThrottleRange();
  Run();
#elif defined PROGRAM_MODE
  ProgramESC();
#endif
  while(1){
  }
}
