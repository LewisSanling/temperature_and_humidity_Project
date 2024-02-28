#include "DHT.h"     
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <pm2008_i2c.h>

PM2008_I2C pm2008_i2c;
LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(2, DHT11); 
  int t1;
  int h1;
  int p;
  char data;
  char data1;

void setup() {
  lcd.init();             
  lcd.backlight(); 
  pinMode(8,OUTPUT); // led 빨강
  digitalWrite(8, HIGH); // led 빨강 
  pinMode(9,OUTPUT); // led 파랑
  digitalWrite(9, HIGH); // led 파랑
  pinMode(4,OUTPUT); // 릴레이 2번
  pinMode(5,OUTPUT); // 릴레이 3번
  pm2008_i2c.begin(); // 미세먼지 
  pm2008_i2c.command();
  Serial.begin(9600); 
  dht.begin(); 
  delay(500);

}

void loop() {

  int h = dht.readHumidity();
  int t = dht.readTemperature();
  uint8_t ret = pm2008_i2c.read();
  int p= pm2008_i2c.pm10_grimm;
  
  Serial.print(h);
  Serial.print("\n"); 
  Serial.print(t);
  Serial.print("\n");
  Serial.println(p);


  lcd.setCursor(0,0);
  lcd.print("H:  ");
  lcd.print(h);
  lcd.print("%");
  lcd.setCursor(0,1);
  lcd.print("T:  ");
  lcd.print(t);
  lcd.print("C");
  lcd.setCursor(0,2);
  lcd.print("PM:  ");
  lcd.print(pm2008_i2c.pm10_grimm);
  lcd.print("    ");

  if(Serial.available()){
    data = Serial.read();
    }
    
  if(data=='a'){
    if(t>=30 && h >=20 && p >=70){
      digitalWrite(4, HIGH);
      digitalWrite(5, HIGH);
  }
  else{
      digitalWrite(4, LOW);
      digitalWrite(5, LOW); 
  }
  }

  if(data=='f'){
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
    }
  
  else if(data=='t'){
      digitalWrite(4, HIGH);
      digitalWrite(5, HIGH);     
    }
  
  else if(t>=30 && h >=20 && p >=70){
      digitalWrite(4, HIGH);
      digitalWrite(5, HIGH);
  }
  else{
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);   
  }

  delay(200);

  }
