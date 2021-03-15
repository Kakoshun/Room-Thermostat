//ENGINEER:BETOUNIS IOANNIS

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
#include <dht.h>

dht DHT;

int rele = 5;
float setsens = 1 - 0.9;
float wrtemp = 5;
int ygrasia = 50;

void setup()
{
  pinMode (2,INPUT_PULLUP); 
  pinMode (4,INPUT_PULLUP); 
  pinMode (12,INPUT_PULLUP); 
  pinMode (13,INPUT_PULLUP); 
  pinMode (rele, OUTPUT); //relay pin
  digitalWrite(rele, HIGH);
  lcd.init();
  lcd.begin(20, 4);
  lcd.backlight();
  lcd.setCursor(6,0);
  lcd.print("BETOUNIS");
  lcd.setCursor(6,1);
  lcd.print("ROBOTICS");
  lcd.setCursor(2,2);
  lcd.print("ROOM  THERMOSTAT");
  lcd.setCursor(3,3);
  lcd.print("BEGIN PROGRAMM");
  delay(5000);    
}
void loop()
{
  int tempstep = digitalRead(2);
  int hmstep = digitalRead(4);
  int thermsyn = digitalRead(12);
  int thermplin = digitalRead(13);
  float readDHT = DHT.read11(8);
  float ther = DHT.temperature; // for correction
  float ygr = DHT.humidity; // for correction    

    if (setsens > 2.1) setsens = setsens - 2.0; 
    else if (tempstep == HIGH) setsens = setsens + 0.1; 

    if (ygrasia > 100) ygrasia = ygrasia - 95; 
    else if (hmstep == HIGH) ygrasia = ygrasia + 5; 

    if (thermsyn == HIGH) wrtemp = wrtemp + 1; 
    else if (thermplin == HIGH) wrtemp = wrtemp - 1; 
    
    lcd.begin(20, 4);
    lcd.backlight();
    lcd.setCursor(0,0);
    lcd.print("RoomTemp : ");
    lcd.setCursor(11,0);
    lcd.print(ther);
    lcd.setCursor(16,0);
    lcd.print((char)223);
    lcd.setCursor(17,0);
    lcd.print("C");
    lcd.setCursor(0,1);
    lcd.print("Step:");
    lcd.setCursor(5,1);
    lcd.print(setsens);
    lcd.setCursor(10,1);
    lcd.print("Tem:");
    lcd.setCursor(14,1);
    lcd.print(wrtemp);
    lcd.setCursor(18,1);
    lcd.print((char)223);
    lcd.setCursor(19,1);
    lcd.print("C");
    lcd.setCursor(0,2);
    lcd.print("Humidity: ");
    lcd.setCursor(11,2);
    lcd.print(ygr); 
    lcd.setCursor(16,2);
    lcd.print("%");  
    lcd.setCursor(0,3);
    lcd.print("Set Humidity:");
    lcd.setCursor(13,3);
    lcd.print(ygrasia);
    lcd.setCursor(18,3);
    lcd.print("%"); 

    if (ygr > ygrasia) digitalWrite(rele, LOW);
    else if (ther > wrtemp + setsens) digitalWrite(rele, HIGH);
    else if (ther < wrtemp - setsens) digitalWrite(rele, LOW);
    else digitalWrite(rele, HIGH);
}
