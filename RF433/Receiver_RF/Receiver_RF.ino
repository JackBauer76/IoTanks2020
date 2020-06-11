/* Tested RadioHead library
 * 
 * 
 */



#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

RH_ASK driver;

const int Buzzer = 8;

void setup()
{
    Serial.begin(9600);	// Debugging only
    if (!driver.init())
         Serial.println("init failed");
    pinMode(Buzzer,OUTPUT);     
}

void loop()
{
    uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
    uint8_t buflen = sizeof(buf);

    if (driver.recv(buf, &buflen)) // Non-blocking
    {
	    int i;
      driver.printBuffer("Got:", buf, buflen);
      tone(Buzzer, 1900, 25);
    }
}
