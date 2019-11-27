#include <LCD.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

/// prasa pneumatyczna 21/10/2018
/// DOUT
int silownik_praca = 22;
int silownik_spoczynek = 24;
int zawor_bezpiecznik = 25;
int lampka_praca = 26;
int lampka_awaria = 27;
int lampka_bezpieczenstwa = 28;


/// DIN
int przycisk_start = 52;
int przycisk_stop = 51;
int przycisk_reset = 50;
int przycisk_man = 49;
int przycisk_auto = 48;
int przycisk_przod = 47;
int przycisk_tyl = 46;
int czujnik_cisnienia = 45;
int blokada_bezpieczenstwa = 30;
int obecnosc_detalu = 44;
int silownik_spoczynek_czujnik = 43;
/// AIN
int linial_pozycja = 3;


/// zmienne 
/// sekfencja maszyny
bool stan_bezpieczenstwa;
bool stan_auto;
bool stan_man;
bool ruch_przod;
bool ruch_tyl;
/// cykl automatyczny programu
int krok_cyklu;
int pozycja;
int licznik_detali;
///
bool wyswietlenie_kom1;
bool wyswietlenie_kom2;
 

/// inne urzadzenia i biblioteki 
#define BACKLIGHT_PIN 13 
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);






void setup() {
 Serial.begin(9600);
 lcd.begin(20,4);
 
///DOUT
pinMode(silownik_praca,OUTPUT);
pinMode(silownik_spoczynek,OUTPUT);
pinMode(zawor_bezpiecznik,OUTPUT);
pinMode(lampka_praca,OUTPUT);
pinMode(lampka_awaria,OUTPUT);
pinMode(lampka_bezpieczenstwa,OUTPUT);
///DIN
pinMode(przycisk_start,INPUT_PULLUP);
pinMode(przycisk_stop,INPUT_PULLUP);
pinMode(przycisk_reset,INPUT_PULLUP);
pinMode(przycisk_auto,INPUT_PULLUP);
pinMode(przycisk_man,INPUT_PULLUP);
pinMode(przycisk_przod,INPUT_PULLUP);
pinMode(przycisk_tyl,INPUT_PULLUP);
pinMode(czujnik_cisnienia,INPUT_PULLUP);
pinMode(blokada_bezpieczenstwa,INPUT_PULLUP);
pinMode(obecnosc_detalu,INPUT_PULLUP);
pinMode(silownik_spoczynek_czujnik,INPUT_PULLUP);
///AIN
pinMode(linial_pozycja,INPUT);
///LCD
pinMode ( BACKLIGHT_PIN, OUTPUT );
digitalWrite ( BACKLIGHT_PIN, HIGH );

///
stan_bezpieczenstwa = true;
digitalWrite(silownik_praca,HIGH);
digitalWrite(silownik_spoczynek,HIGH);
ruch_tyl = true;
ruch_przod = true;

}

void loop() {
///odczytanie danych 
  if(digitalRead(przycisk_auto) == false){
  stan_auto = true;
  stan_man = false;
  wyswietlenie_kom1 = true;
  wyswietlenie_kom2 = true;
  Serial.println("przycisk auto");
  }
  if(digitalRead(przycisk_man) == false){
  stan_man = true;
  stan_auto = false;
  wyswietlenie_kom1 = true;
  Serial.println("przycisk manual");
  }
  if(digitalRead(czujnik_cisnienia) == false){
  //stan_bezpieczenstwa = true;
  }else{
  //stan_bezpieczenstwa = false;
  }
   if(digitalRead(blokada_bezpieczenstwa) == false){
  stan_bezpieczenstwa = true;
  digitalWrite(lampka_praca,HIGH);
  digitalWrite(zawor_bezpiecznik,LOW);
   lcd.setCursor(0,1);
  lcd.print("    OK SAFETY      ");
  }else{
  stan_bezpieczenstwa = false;
  digitalWrite(lampka_praca,LOW);
  digitalWrite(zawor_bezpiecznik,HIGH);
  digitalWrite(silownik_praca,HIGH);
  digitalWrite(silownik_spoczynek,HIGH);
  krok_cyklu = 0;
  lcd.setCursor(0,1);
  lcd.print("NARUSZONE SAFETY");
  lcd.setCursor(0,2);
  lcd.print("              ");
  digitalWrite(lampka_bezpieczenstwa,HIGH);
  delay(500);
  digitalWrite(lampka_bezpieczenstwa,LOW);
  delay(500);
  
  
  }
  
///modelpracy
  if(stan_bezpieczenstwa == true){
  if((stan_auto == true)&&(stan_man == false)){
     if(wyswietlenie_kom1 == true){
    lcd.clear();
    lcd.print("TRYB AUTOMATYCZNY");
    wyswietlenie_kom1 = false;
    }
  //Serial.println("tryb auto");
 // Serial.println("umiesc detal, nacisnij start");
  /// Krok 1 nacisniecie przyscisku start   if(wyswietlenie_kom1 == true){
    if(krok_cyklu == 0){
    if(digitalRead(obecnosc_detalu) == false){
    lcd.setCursor(0,2);
    lcd.print("NACIS START");
    wyswietlenie_kom2 = false;
    }else{
    lcd.setCursor(0,2);
    lcd.print("WLOZ DETAL");
    }
    }
    
  if((digitalRead(przycisk_start) == false)&&(digitalRead(silownik_spoczynek_czujnik) == false )){
    if(digitalRead(obecnosc_detalu) == false){
       krok_cyklu = 1;
      // przycisk_start = true;
       Serial.println("OK ide dalej");
    lcd.setCursor(0,2);
    lcd.print("PRASOWANIE /123/");
    }else{
    lcd.setCursor(0,2);
    lcd.print("NIE WLASCIWA POZYCJA ");
    }
  }
  if(krok_cyklu == 1){
    //przycisk_start = true;
    digitalWrite(silownik_praca,LOW);
    pozycja = analogRead(linial_pozycja);
    lcd.setCursor(0,3);
    lcd.print(" POZYCJA: ");
    lcd.setCursor(10,3);
    lcd.print(pozycja);
    Serial.print(pozycja);
    if(pozycja >= 500){
      digitalWrite(silownik_praca,HIGH);
      delay(500);
      krok_cyklu = 2;
    }
  }
  if(krok_cyklu == 2){
    digitalWrite(silownik_spoczynek,LOW);
    lcd.setCursor(0,2);
    lcd.print(" POWROT             ");
    Serial.print(pozycja);
    if(digitalRead(silownik_spoczynek_czujnik) == false){
      digitalWrite(silownik_spoczynek,HIGH);
      krok_cyklu = 3;
  }
  }
  if(krok_cyklu == 3){
    licznik_detali = licznik_detali +1;
     lcd.setCursor(0,3);
     lcd.print("ILOSC SZTUK ");
     lcd.setCursor(12,3);
     lcd.print(licznik_detali);
    Serial.print(pozycja);
    Serial.print(licznik_detali);
    Serial.print(" licznik detali ");
    krok_cyklu = 0;
    
  }
 
  }
  if((stan_man == true)&&(stan_auto == false)){
     if(wyswietlenie_kom1 == true){
    lcd.clear();
    lcd.print("TRYB MANUALNY");
    wyswietlenie_kom1 = false;
    }
  Serial.println("tryb manualny");
  krok_cyklu = 0;
  if(ruch_przod == true){
  if((digitalRead(przycisk_przod) == false)&&(analogRead(linial_pozycja)<= 500)){
  digitalWrite(silownik_praca,LOW);
  Serial.println("silownik praca");
   lcd.setCursor(0,2);
   lcd.print("RUCH PRZOD");
  ruch_tyl = false;
  }else{
  digitalWrite(silownik_praca,HIGH);
  lcd.setCursor(0,2);
  lcd.print("          ");
  ruch_tyl = true;
   
  }
  }

  if(ruch_tyl == true){
  if((digitalRead(przycisk_tyl) == false)&&(digitalRead(silownik_spoczynek_czujnik) == true)){
  digitalWrite(silownik_spoczynek,LOW);
  Serial.println("Silownik spoczynek");
  lcd.setCursor(0,2);
  lcd.print("RUCH TYL");
  ruch_przod = false;
  }else{
  digitalWrite(silownik_spoczynek,HIGH);
  lcd.setCursor(0,2);
  lcd.print("         ");
  ruch_przod = true;  
  }
  }
  
  
  }else{
  
  
  }
  }
}
