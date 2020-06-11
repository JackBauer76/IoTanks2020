// Sender Sketch
// Using RadioHead library  and example ask_transmitter.pde
/* Pinout Nano
 * D12 Led
 * D12 RfSender // it seems that the library always uses this pin
 * D3 Pushbutton
 * D2 PIR
 */

#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

const int Led = 6;
const int Pushbutton = 3;
const int PIR = 2;


RH_ASK driver;

void setup() 
{
   pinMode(Led, OUTPUT);
   pinMode(Pushbutton, INPUT_PULLUP);  
   pinMode(PIR, INPUT);
   Serial.begin(9600);   // Debugging only
    if (!driver.init())
         Serial.println("init failed");
   
}

void loop() 
{
  
    const char *msg = "666";

    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    delay(200);  
    /*
    if((digitalRead(PIR) || digitalRead(Pushbutton))== HIGH)
    {
      digitalWrite(Led, HIGH);
      delay(200);  
    }
    else
    {
      digitalWrite(Led, LOW);
      delay(200);  
    }
    */

}
