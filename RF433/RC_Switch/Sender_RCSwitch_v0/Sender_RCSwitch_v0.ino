/* Sender on D12
 * Led on D13 
 * Pushbutton on D3
 * 470uF Cap over +-
 * Pir on D2
 */

#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

const int Pushbutton = 3;
const int PIR = 2;
const int Led = 13;

void setup() 
{
    Serial.begin(9600);
    mySwitch.enableTransmit(12);
    pinMode(Led,OUTPUT);   
    pinMode(Pushbutton,INPUT_PULLUP);   
    pinMode(PIR,INPUT);    
}

void loop() 
{
    if(!digitalRead(Pushbutton))
    {
      mySwitch.send(5393, 24);
      digitalWrite(13, HIGH);
      delay(500);
      digitalWrite(13,LOW);
    
    }
    
    if(digitalRead(PIR))
    {
      mySwitch.send(9875, 24);
      digitalWrite(13, HIGH);
      delay(500);
      digitalWrite(13,LOW);
    
    }
  
}
