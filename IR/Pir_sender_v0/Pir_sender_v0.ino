/* Sender on D12
 * Led on D13 
 * Pushbutton on D3
 * 470uF Cap over +-
 * Pir on D2
 */
#include <IRremote.h>

IRsend irsend;

const int Pushbutton = 3;
const int PIR = 2;
const int Led = 9;

void setup() 
{
    pinMode(Led,OUTPUT);   
    pinMode(PIR,INPUT);    
}

void loop() 
{

    if(digitalRead(PIR))
    {
        digitalWrite(Led, HIGH);      
        for (int i = 0; i < 8; i++) 
        {
          irsend.sendSony(8251, 12);
          //testSony(0x577, 12);
          delay(40);
        }
    }
    else
    {
      digitalWrite(Led,LOW);
    }
      
      delay(500);
      
    
    
  
}
