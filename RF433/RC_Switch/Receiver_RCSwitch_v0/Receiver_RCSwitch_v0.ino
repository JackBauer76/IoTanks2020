/* Receiver on D2
 * Led on D13 
 * Buzzer on D8
 * 470uF Cap over +-
 * 
 */

#include <RCSwitch.h>
#include <Arduino.h>
#include <TM1637Display.h>

#define CLK 4
#define DIO 5

RCSwitch mySwitch = RCSwitch();
TM1637Display display(CLK, DIO);

const int Led = 13;
const int Buzzer = 8;

#define TEST_DELAY   2000

void setup() 
{
  Serial.begin(9600);
  mySwitch.enableReceive(0);  // Receiver on interrupt 0 => that is pin #2
  pinMode(Buzzer,OUTPUT);  
}

void loop() 
{
    display.setBrightness(0x8f);
    if (mySwitch.available()) {
    
    Serial.print("Received ");
    Serial.print( mySwitch.getReceivedValue() );
    Serial.print(" / ");
    Serial.print( mySwitch.getReceivedBitlength() );
    Serial.print("bit ");
    Serial.print("Protocol: ");
    Serial.println( mySwitch.getReceivedProtocol() );
    tone(Buzzer, 1900, 75);
    if(mySwitch.getReceivedValue()==9875)
    {
         tone(Buzzer, 4000, 75);  
         display.clear();
         display.showNumberDec(mySwitch.getReceivedValue(), false); // Expect: ___0
         delay(TEST_DELAY);
    }
    if(mySwitch.getReceivedValue()==5393)
    {
         tone(Buzzer, 1000, 75);  
         display.clear();
         display.showNumberDec(mySwitch.getReceivedValue(), false);
         delay(TEST_DELAY);
    }  
    mySwitch.resetAvailable();
  }

}
