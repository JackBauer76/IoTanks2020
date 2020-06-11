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

const int Led = 3;
const int TiltS = 2;

volatile bool AuthState = 0;
int PirCounter = 0;
int Buffer = 0;
int CounterDisplay;
int Counter;

void setup() {

  pinMode(Led, OUTPUT);
  pinMode(TiltS, INPUT_PULLUP);
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 8000000) clock_prescale_set(clock_div_1);
  #endif
  attachInterrupt(0, Auth, CHANGE);
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

    if(Buffer!= PirCounter)
    {
      
      delay(250);
      Buffer = PirCounter;
      CounterDisplay++;
      digitalWrite(Led, HIGH);
    }
    else
    {
      digitalWrite(Led,LOW);   
      Buffer = PirCounter;
    }
    Counter = int(CounterDisplay/2);
  display.showNumberDec(Counter, false); // Expect: ___0
  
  
}
