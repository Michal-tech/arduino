#include <LCD.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h> 
// zmienne , dane
int stala;
int dane1;
int dane2;
int kalibracja1;
int kalibracja2;
int test1;
int test2;
int proba1;
int proba2;
int pomiar1;
int pomiar2;
int wysw;
int przycisk1;
int flaga1;

// zmienne hardwarwe
int czujnik1 =2;
int czujnik2 =3;
int gwizdek = 4;




#define BACKLIGHT_PIN     13
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup()
{
  

  pinMode ( BACKLIGHT_PIN, OUTPUT );
  pinMode(czujnik1,INPUT);
  pinMode(czujnik2,INPUT);
  pinMode(gwizdek,OUTPUT);

  
  digitalWrite ( BACKLIGHT_PIN, HIGH );
  stala = 6600;
  
  /// pierwsze wyswietlenie 
  lcd.begin(16,2); 
  lcd.setCursor(0,0);
  lcd.print("CZUJNIK GAZU");             
  lcd.setCursor(0,1);
  lcd.print("ver 01.1"); 
  delay(stala);
  lcd.clear();
   lcd.setCursor(0,0);
  lcd.print("by michal"); 
  delay(stala);
  lcd.clear();
  
  digitalWrite(gwizdek,HIGH);
  delay(400);
    digitalWrite(gwizdek,LOW);
  
   
   
   ///przygotowanie
   lcd.setCursor(0,0);
   lcd.print("*PRZYGOTOWANIE*");
   for ( int i=1;i<14;i++){
    lcd.setCursor(i,1);
    lcd.print("*");
    delay(10000);
   }
   lcd.clear();
  
  /// kalibracja sterownika
    
    lcd.print("KALIBRACJA CZ1");
   for(int i =1;i<11;i++){
    proba1 = analogRead(czujnik1);
    test1 = test1 + proba1;
    wysw = wysw + 10;
    lcd.setCursor(0,1);
    lcd.print(wysw);
    delay(2000);
   }
   kalibracja1 = test1/10;
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("w kal1 ");
   lcd.print(kalibracja1);
   lcd.print(" PPM ");
   
   delay(stala);
     lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("KALIBRACJA CZ2 ");
   for(int i =1;i<11;i++){
    proba2 = analogRead(czujnik2);
    test2 = test2 + proba2;
    if(wysw == 100){
      wysw = 0;
    }
    wysw = wysw + 10;
    lcd.setCursor(0,1);
    lcd.print(wysw);
    delay(2000);
   }
   kalibracja2 = test2/10;
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("w kal1 ");
   lcd.print(kalibracja1);
   lcd.print(" PPM ");
   lcd.setCursor(0,1);
   lcd.print("w kal2 ");
   lcd.print(kalibracja2);
    lcd.print(" PPM ");
   
   delay(stala);
   lcd.clear();
     lcd.setCursor(0,0);
   lcd.print("  POMIAR CIAGLY");
   for ( int i=1;i<14;i++){
    lcd.setCursor(i,1);
    lcd.print("*");
    delay(2000);
   }
   lcd.clear();
  
 
}

void loop()
{
   
   //// pomiar
for( int i=1 ; i<6;i++){
  pomiar1 = analogRead(czujnik1);
  dane1 = dane1 + pomiar1;
  delay(1000);
  
  
}
  dane1 = dane1/5;
  dane1 = dane1-kalibracja1;
    lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" st.CO:");
  lcd.print(dane1);
  lcd.print("PPM");
    lcd.setCursor(0,1);
  lcd.print(" st.CO2: ");
  lcd.print(dane2);
  lcd.print(" PPM");
  {
for( int i=1 ; i<6;i++){
  pomiar2 = analogRead(czujnik2);
  dane2 = dane2 + pomiar2;
  delay(1000);
  
}
dane2 = dane2/5;
  dane2 = dane2-kalibracja2;
  lcd.clear();
    lcd.setCursor(0,0);
  lcd.print(" st.CO:");
  lcd.print(dane1);
  lcd.print("PPM");
  lcd.setCursor(0,1);
  lcd.print(" st.CO2: ");
  lcd.print(dane2);
  lcd.print(" PPM");

  

/// zabzepieczenie 
}
  if(dane2 > 30){
    for( int i=1;i<6;i++){
    delay(50);
    digitalWrite(gwizdek,HIGH);
    delay(50);
    digitalWrite(gwizdek,LOW);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("uwaga przekroczono");
    lcd.setCursor(0,1);
    lcd.print("zakres pomiarowy");
    delay(stala);
    
    
    }
  }
  if(dane1 > 15){
    for( int i=1;i<6;i++){
    delay(50);
    digitalWrite(gwizdek,HIGH);
    delay(50);
    digitalWrite(gwizdek,LOW);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("uwaga przekroczono");
    lcd.setCursor(0,1);
    lcd.print("zakres pomiarowy");
    delay(stala);
  }
  }
}
