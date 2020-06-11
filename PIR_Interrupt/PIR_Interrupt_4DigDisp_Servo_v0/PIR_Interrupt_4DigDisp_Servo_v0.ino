
#include <Servo.h>
#include <avr/interrupt.h> 
 #include <TM1637Display.h>

#define CLK 6
#define DIO 7

Servo servoBase;  
Servo servoTop;  

TM1637Display display(CLK, DIO);

int pos = 0;    // variable to store the servo position
int target = 120;
int pos_top = 0;    // variable to store the servo position
const int Led = 13;

const int Pir = 2;
volatile int AuthState = 0;
volatile int PirCounter = 0;

void setup() {
  servoBase.attach(9);  // attaches the servo on pin 9 to the servo object
  //servoTop.attach(10); 
  pinMode(Led, OUTPUT);
  pinMode(Pir, INPUT_PULLUP);
  attachInterrupt(0, Auth, CHANGE);
  
}

void Auth() 
{
  AuthState = !AuthState;
  if(AuthState == 1)
  {  PirCounter++;}
  
}


void loop() {
    display.setBrightness(0x0f);
    display.showNumberDec(int(PirCounter), false); // Expect: ___0

  if(AuthState==HIGH )
  {
    digitalWrite(Led, HIGH);
    int target = 120;
    int pos = 0; 
    while (servoBase.read() < target) 
    {
    servoBase.write(pos++);
    delay(15); 
    }
  }
  else
  {
    
    digitalWrite(Led,LOW);
    //servoBase.write(0); 
    int target = 120;
    int pos = 0; 
    while (servoBase.read() > pos) 
    {
    servoBase.write(target--);
    delay(15); 
    }
    
  }

/*
      for (pos = 0; pos <= 180; pos += 1) 
    { 
          servoBase.write(pos); 
          delay(15);                    
    }

    for (pos = 180; pos >= 0; pos -= 1) 
    {
          servoBase.write(pos);              
          delay(15);                       
    }
  /*for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    servoBase.write(pos); 
    
    delay(15);                       // waits 15ms for the servo to reach the position
  }

  for (pos_top = 0; pos_top <= 180; pos_top += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    servoTop.write(pos_top);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }

  
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    servoBase.write(pos);              // tell servo to go to position in variable 'pos'
   
    delay(15);                       // waits 15ms for the servo to reach the position
  }
/*
  for (pos_top = 180; pos_top >= 0; pos_top -= 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    servoTop.write(pos_top);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
*/
  
}
