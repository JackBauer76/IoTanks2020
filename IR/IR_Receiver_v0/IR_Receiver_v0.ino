/*
 * 
 * Sender with:  irsend.sendSony(8251, 12);
 * 
 * Decoded SONY: 3B (12 bits)
Raw (26): 2350 -650 600 -600 600 -600 550 -650 600 -600 550 -600 650 -550 1200 -600 1150 -650 1150 -600 650 -550 1200 -600 1200 
3B
Decoded SONY: 3B (12 bits)
Raw (26): 2350 -650 600 -550 650 -600 600 -600 550 -600 600 -600 600 -600 1200 -600 1200 -600 1150 -600 650 -550 1150 -650 1150 
AA20EE00
Unknown encoding: AA20EE00 (32 bits)
Raw (26): 2400 -600 550 -650 550 -650 550 -650 550 -650 500 -700 550 -600 1200 -600 1150 -650 1150 -600 550 -650 1150 -650 1200 

 * 
 * 
 */



#include <IRremote.h>

const int Led = 7;
int RECV_PIN = 5;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup() 
{
    Serial.begin(9600);
    irrecv.enableIRIn(); // Start the receiver
    pinMode(Led,OUTPUT);

}

void loop() 
{
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    dump(&results);
    irrecv.resume(); // Receive the next value
  }

}


void dump(decode_results *results) {
  // Dumps out the decode_results structure.
  // Call this after IRrecv::decode()
  int count = results->rawlen;
  if (results->decode_type == UNKNOWN) {
    Serial.print("Unknown encoding: ");
  }
  
  else if (results->decode_type == SONY) 
  {
    Serial.print("Decoded SONY: ");
    if(results->value == 0x3B)
    {
    digitalWrite(Led,HIGH);
    }
    else
    {
      digitalWrite(Led,LOW);
    }
    
  }
  
  Serial.print(results->value, HEX);
  Serial.print(" (");
  Serial.print(results->bits, DEC);
  Serial.println(" bits)");
  Serial.print("Raw (");
  Serial.print(count, DEC);
  Serial.print("): ");
  
  for (int i = 1; i < count; i++) {
    if (i & 1) {
      Serial.print(results->rawbuf[i]*USECPERTICK, DEC);
    }
    else {
      Serial.write('-');
      Serial.print((unsigned long) results->rawbuf[i]*USECPERTICK, DEC);
    }
    Serial.print(" ");
  }
  Serial.println();

}
