#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

#define trigger 4
#define ecco 3

void setup() {
  lcd.init();                      // initialize the lcd 
  lcd.init();
  lcd.backlight();
  pinMode(trigger, OUTPUT);
  pinMode(ecco, INPUT);
  Serial.begin(9600);       
  lcd.setCursor(0,0);
  lcd.print("  Water level=  ");
}

void loop() {
  long duration, distance ; 
  digitalWrite(trigger, LOW);
  delayMicroseconds(30);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  duration = pulseIn(ecco, HIGH);
  distance = 0.034*duration/2;
  
  
  Serial.print("Object is at ");
  Serial.print(distance);
  Serial.println(" cm");
  

  lcd.setCursor(5,1);
  lcd.print("                ");
  lcd.setCursor(5,1);
  lcd.print(150- distance);
  
  delay(1500); 

}
