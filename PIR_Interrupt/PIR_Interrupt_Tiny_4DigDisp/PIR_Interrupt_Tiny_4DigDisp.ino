/*
 * 
 * Pin
0 PIR
1 CLK
2 DIO
3 Led
4
5
 * 
 * 
 * 
 */


#include <avr/interrupt.h> 
#ifdef __AVR__
#include <avr/power.h>
#endif
#include <TM1637Display.h>

#define CLK 0
#define DIO 1



TM1637Display display(CLK, DIO);

int pos = 0;    // variable to store the servo position
int target = 120;
int pos_top = 0;    // variable to store the servo position
const int Led = 3;

const int Pir = 2;

volatile bool AuthState = 0;
int PirCounter = 0;
int CounterDisplay;

void setup() {

  pinMode(Led, OUTPUT);
  pinMode(Pir, INPUT);
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 8000000) clock_prescale_set(clock_div_1);
  #endif
  attachInterrupt(0, Auth, RISING);
  //GIMSK |= _BV(INT0);
  
}


/*

ISR(INT0_vect) {
   PirCounter++;
   AuthState = !AuthState;
   
}

*/
void Auth() 
{
  AuthState = !AuthState;
  PirCounter++;
  
}


void loop() 
{
    display.setBrightness(0x4f);
    CounterDisplay = int(PirCounter/2);
    display.showNumberDec(CounterDisplay, false); // Expect: ___0
  
    
  if(AuthState==HIGH )
  {
    digitalWrite(Led, HIGH);


  }
  else
  {
    digitalWrite(Led,LOW);    
  }
  
}
