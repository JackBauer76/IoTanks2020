#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <dht.h>



#define DHT11_PIN 5

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
dht DHT;


void setup()
{
  lcd.init();

}

void loop() 
{
  int chk = DHT.read11(DHT11_PIN);
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Temp ");
  lcd.setCursor(5,0);
  lcd.print(DHT.temperature);
  lcd.setCursor(10,0);
  lcd.print(" C");
  
  
  lcd.setCursor(0,1);
  lcd.print("Humidity");
  lcd.setCursor(9,1);
  lcd.print(DHT.humidity);
  lcd.setCursor(14,1);
  lcd.print("%");
  
  
 
 

}
