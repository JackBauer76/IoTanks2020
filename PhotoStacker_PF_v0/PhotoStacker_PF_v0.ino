/* Nano w/ LCD I2C Display
 * 2 Pushbuttons using interrupts
 * 2 Poti
 * 
 */
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
 
const int PushbuttonPlus = 2;
const int PushbuttonMinus = 3;
const int Potix = A1;
const int Potiy = A2;

int counter = 0;
volatile long PIRstate=0;

///////////////////////////////// SETUP //////////////////////////////////////
void setup() 
{
  pinMode(PushbuttonPlus,INPUT_PULLUP);
  pinMode(PushbuttonMinus,INPUT_PULLUP);
  pinMode(Potix,INPUT);
  pinMode(Potiy,INPUT);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(PushbuttonPlus),motionDetectorPlus,FALLING);
  attachInterrupt(digitalPinToInterrupt(PushbuttonMinus),motionDetectorMinus,FALLING);
  lcd.init(); 
  lcd.backlight();
  lcd.clear();
}

///////////////////////////////// LOOP /////////////////////////////////////////
void loop() 
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Counter");
  lcd.setCursor(8,0);
  lcd.print(PIRstate);
  
  int PotiValuex = analogRead(Potix);
  int PotiValuey= analogRead(Potiy);
  lcd.setCursor(0,1);
  lcd.print("Pos. ");
  lcd.setCursor(5,1);
  
  lcd.print(PotiValuex);
  lcd.setCursor(11,1);
  lcd.print(PotiValuey);
//
//  for (int positionCounter = 0; positionCounter < 29; positionCounter++) 
//  {
//    lcd.scrollDisplayLeft();
//    delay(250);
//  }

  float voltageX = PotiValuex * (5.0 / 1023.0);
  float voltageY = PotiValuey * (5.0 / 1023.0);
  
  Serial.println(voltageX, voltageY);  
  


  
}


/////////////////////////////// Functions
void motionDetectorPlus()
{
  PIRstate++;  
}

void motionDetectorMinus()
{
  PIRstate--;  
}
