
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

RF24 radio(10,9);

const int role_pin = 7;
const int PushButton = 6;
const int Led = 3;
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };
typedef enum { role_ping_out = 1, role_pong_back } role_e;
const char* role_friendly_name[] = { "invalid", "Ping out", "Pong back"};
role_e role;

/////////////////////////////// SETUP ///////////////////////
void setup(void)
{
   pinMode(role_pin, INPUT);
   pinMode(Led, OUTPUT);
   pinMode(PushButton,INPUT_PULLUP);
  digitalWrite(role_pin,HIGH);
  delay(20); // Just to get a solid reading on the role pin
  if ( ! digitalRead(role_pin) )
    role = role_ping_out;
  else
    role = role_pong_back;
  Serial.begin(9600);
  Serial.print("ROLE: ");
  Serial.println(role_friendly_name[role]);
  radio.begin();
  radio.setRetries(15,15);
  radio.setPayloadSize(8);

  if ( role == role_ping_out )
  {
    radio.openWritingPipe(pipes[0]);
    radio.openReadingPipe(1,pipes[1]);
  }
  else
  {  
    radio.openWritingPipe(pipes[1]);
    radio.openReadingPipe(1,pipes[0]);
 }

  radio.startListening();
  radio.printDetails();
}
/////////////////////// Loop ////////////////////////////////

void loop(void)
{
////  role_ping_out//////////////////

  if(!digitalRead(PushButton))
  {
  if (role == role_ping_out)
  {
    // First, stop listening so we can talk.
    radio.stopListening();
    // Take the time, and send it.  This will block until complete
    unsigned long counter = 5577514;
    counter++;
    Serial.print("Now sending ");
    Serial.println(counter);
    bool ok = radio.write( &counter, sizeof(unsigned long) );
    
    if (ok)
    {
      Serial.print("mande esto ");
      Serial.print(counter);
    }
    
    radio.startListening();

    // Wait here until we get a response, or timeout (250ms)
    unsigned long started_waiting_at = millis();
    bool timeout = false;
    while ( ! radio.available() && ! timeout )
    {
      if (millis() - started_waiting_at > 2000 )
        timeout = true;
    }    
    if ( timeout )
    {
      Serial.print("Failed, response timed out.");
    }
    else
    {
      unsigned long got_time;
      radio.read( &got_time, sizeof(unsigned long) );
      Serial.print(" what i heard is ");
      Serial.println(got_time);
      if(got_time == 8251)
      {
        digitalWrite(Led,HIGH);
        Serial.print(" se armo la gorda ");
      }
      else
      {
        digitalWrite(Led,LOW);
      }
    }
    delay(1000);
  } // end of role_ping_out


 // Pong back role.  Receive each packet, dump it out, and send it back
  if ( role == role_pong_back )
  {
    // if there is data ready
    if ( radio.available() )
    {
      unsigned long got_time;
      bool done = false;
      while (!done)
      {
        // Fetch the payload, and see if this was the last one.
        done = radio.read( &got_time, sizeof(unsigned long) );
        Serial.print("Got payload ");
        Serial.println(got_time);
	      delay(20);
      }

      radio.stopListening();
      int responseback = 1;
      responseback++;
      // Send the final one back.
      radio.write( &responseback, sizeof(int) );
      Serial.print("le regrese el responseback: ");
      Serial.print(responseback);
      radio.startListening();
    }
  } // end of role_pong_back

} // end of PushButton
} // end of loop
