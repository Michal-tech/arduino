/// STEROWNIK MULTI /// ALARM /// CO // BRAMA 
///CYFROWE WEJSCIA
int czujnikp1=26;
int czujnikp2=23;
int czujnikp3=24;
int czujnikp4=25;
int zadana_temp=27;/// nastawa kotła co

int otwieranie_brama = 28;
int zamykanie_brama = 29;
int krancowy_z = 30;
int krancowy_o = 31;
///CYFROWE WYJSCIA
int silnik_z = 45;
int silnik_o = 46;

int buzzer = 47;
int pompa_co = 48;
int lampka_alarm_NOK = 49;
int lampka_alarm=50;
int zamek_brama=52;
///ANALOGOWE WEJSCIA

///ZMIENNE 
bool aktywacja_alarm;
bool dezaktywacja_alarm;
bool rodzaj_akcji_bool;
bool stan_aktywacja_alarmu;
bool stan_dezaktywacja_alarmu;
bool stan_wyswietlenie_kom;
bool stan;
bool stan2 = false;
bool wl_menu = true;
bool zamknij_brama;
bool otworz_brama;
bool alarm_haslo = true;
char znak_keypad;
int akcja;
char haslo[5]= {'B','2','3','4','5'};
char dane[5]= {};
int x;
int rodzaj_akcji;// potrzebne do obsł. menu
int licznik;
int licznik1;
int licznik2;
int licznik3;
int licznik4;
int licznik10;
/// piec co
int nastawa_co;
float temp_co;
int stan_on_off_co;
int ONEWIRE_PIN = 10;
 
///KLAWIATURA MEMBRANOWA
#include <Keypad.h>
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {2, 3, 4, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 7, 8, 9}; //connect to the column pinouts of the keypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
///WYSWIETLACZ LCD MAGISTRALA IC2
#include <LCD.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h> 
#define BACKLIGHT_PIN  13
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
LiquidCrystal_I2C lcd_co(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
///CZUJNIK TEMPERATURY
#include <OneWire.h>          
#include <DS18B20.h> 
byte address[8] = {0x28, 0x64, 0x3D, 0x76, 0x8, 0x0, 0x0, 0xED};
OneWire onewire(ONEWIRE_PIN);
DS18B20 sensors(&onewire);
//#define ONEWIRE_PIN 10;

///
void setup() {
  pinMode (czujnikp1,INPUT_PULLUP); // deklaracja ze to jest wejscie INPUT
  pinMode (czujnikp2,INPUT_PULLUP);
  pinMode (czujnikp3,INPUT_PULLUP);
  pinMode (czujnikp4,INPUT_PULLUP);

  pinMode (otwieranie_brama,INPUT_PULLUP);
  pinMode (zamykanie_brama,INPUT_PULLUP);
  pinMode (krancowy_z,INPUT_PULLUP);
  pinMode (krancowy_o,INPUT_PULLUP);
  
  /// piec co
  pinMode (zadana_temp,INPUT_PULLUP);
  ///
  pinMode (lampka_alarm,OUTPUT);
  pinMode (lampka_alarm_NOK,OUTPUT);
  pinMode (zamek_brama,OUTPUT);
  pinMode (buzzer,OUTPUT);

  pinMode (silnik_z,OUTPUT);
  pinMode (silnik_o,OUTPUT);
  /// piec co
  pinMode (pompa_co,OUTPUT);
  ///
  /// DO WYSWIETLACZA
   pinMode ( BACKLIGHT_PIN, OUTPUT );
  digitalWrite ( BACKLIGHT_PIN, HIGH );
  digitalWrite(zamek_brama,true);
  digitalWrite(silnik_o,true);
  digitalWrite(silnik_z,true);
  //digitalWrite(czujnikp2,true);
  ///
   stan = false;
   stan_aktywacja_alarmu = false;
   stan_wyswietlenie_kom = false;
   nastawa_co = 30;
  ///Czujnik temp 
  sensors.begin();
 //// sensors.request(address);
  ///
  
  
  Serial.begin(9600); // komunikacja miedzy komputerem a sterownikiem predkosc transmisji 9600
  lcd.begin(20,4);
  lcd_co.begin(16,2);
    lcd.home ();                   // go home
  lcd.print("     STEROWNIK     ");  
  lcd.setCursor ( 0,1 );        // go to the next line
  lcd.print ("      MULTI    ");
  delay ( 500 );
  lcd.clear();
     lcd_co.home ();                   // go home
  lcd_co.print("     STEROWNIK     ");  
  lcd_co.setCursor ( 0,1 );        // go to the next line
  lcd_co.print ("      MULTI    ");
  delay ( 500 );
  lcd_co.clear();
  delay(500);
  menu();
 

}

void loop() {

  delay(200);
  
  //char customKey = customKeypad.getKey();
  
  //if (customKey){
 
 // Serial.println(customKey);}
  znak_keypad = customKeypad.getKey();
  sensors.request(address);
  temp_co = sensors.readTemperature(address);
//////////////////////////////////////////////STEROWANIE MENU GLOWNE
    
   
      if(znak_keypad == 'A'){
       lcd.clear();
       licznik ++;
       Serial.println(licznik);
       if(licznik == 5){
        licznik = 0;
       }
    }
   
    
     if(znak_keypad == 'B'){
       lcd.clear();
       wl_menu = false;
       if(licznik == 1){
        licznik1++;
        if(licznik1 == 4){
          licznik1 = 1;
        }
        if(licznik1 > 1){
         // licznik = 0; // wylaczenie menu gl
          licznik2 = 0; // wyl menu 2
          licznik3 = 0; // wyl menu 3
          licznik4 = 0; // wyl menu 4
        }
       Serial.println(licznik1);
    }
        if(licznik == 2){
        licznik2++;
         if(licznik2 < 3){
          licznik2 = 1;
        }
       Serial.println(licznik2);
    }
        if(licznik == 3){
        licznik3++;
       Serial.println(licznik3);
    }
     if(licznik == 4){
        licznik4++;
       Serial.println(licznik4);
    }
     }
/////////////////////////////////////////////STEROWANIE MENU GLOWNE
/////////////////////////////////////////////WYBIERANIE 
   // if(znak_keypad == 'C'){
     // lcd.clear();
      //licznik1 = licznik;
     // licznik = 0;
     // stan = true;
    //}
    if(znak_keypad == 'D'){
      lcd.clear();
      wl_menu = true;
      licznik1 = 0;
      licznik = 0;
      licznik2 = 0;
      licznik3 = 0;
      licznik4 = 0;
      
      //stan = false;
      menu();
    }
    
/////////////////////////////////////////////WYBIERANIE
if(wl_menu == true){
  switch(licznik){
    case 0 :
    menu();
    break;
    case 1:
    menu1();
    break;
    case 2 :
    menu2(); 
    break;
    case 3 :
    menu3(); 
    break;
  }
}
  switch(licznik1){
    case 0 :
    
    break;
    case 1 :
    menualarm();
    //licznik = 0;
    break;
    case 2 :
    menualarm1();
    aktywacja_alarmu();
     if(znak_keypad == '1'){
      reset_ok();
    }
    //licznik = 0;
    
    break;
    case 3 :
    if(alarm_haslo == true){
    menualarm2();
    }
    dezaktywacja_alarmu();
    //licznik = 0;
    break;
    case 4 :
    licznik = 0;
    break;
     case 5 :
    //licznik1 = 1;
    break;
   
  }
  switch(licznik2)
  { case 1 :
    menubrama();
    break;
    case 2 :
    licznik2 = 1;
    
  }
   switch(licznik3)
  {
    case 1 :
    menupiec1();
    break;
    case 2 :
    licznik = 2;
    break;
  }

  alarm_dzialanie();
  sterownik_co();
  sterownik_brama();
}
void menu()
{ //lcd.clear();
  lcd.home();
  lcd.print("A - ALARM   ");
  lcd.setCursor(0,1);
  lcd.print("B - BRAMA/INNE ");
  lcd.setCursor(0,2);
  lcd.print("D - KOCIOL CO ");
  
}
void menu1()
{ //lcd.clear();
  lcd.home();
  lcd.print("> - ALARM   ");
  lcd.setCursor(0,1);
  lcd.print("B - BRAMA/INNE ");
  lcd.setCursor(0,2);
  lcd.print("D - KOCIOL CO ");
  
}
void menu2()
{// lcd.clear();
  lcd.home();
  lcd.print("A - ALARM   ");
  lcd.setCursor(0,1);
  lcd.print("> - BRAMA/INNE ");
  lcd.setCursor(0,2);
  lcd.print("D - KOCIOL CO ");
  
}
void menu3()
{ //lcd.clear();
  lcd.home();
  lcd.print("A - ALARM   ");
  lcd.setCursor(0,1);
  lcd.print("B - BRAMA/INNE ");
  lcd.setCursor(0,2);
  lcd.print("> - KOCIOL CO ");
  
}

void menualarm()
{ //lcd.clear();
  lcd.setCursor(5,0);
  lcd.print("ALARM MENU");
  lcd.setCursor(0,1);
  lcd.print(" AKTYWACJA ALARMU");
  lcd.setCursor(0,2);
  lcd.print(" DEZAKTYWACJA ");
  lcd.setCursor(0,3);
  lcd.print(" RESET ANOMALI ");
}
void menualarm1()
{ //lcd.clear();
  lcd.setCursor(5,0);
  lcd.print("ALARM MENU");
  lcd.setCursor(0,1);
  lcd.print(">AKTYWACJA ALARMU");
  lcd.setCursor(0,2);
  lcd.print(" DEZAKTYWACJA ");
  lcd.setCursor(0,3);
  lcd.print(" RESET NACIS * ");
 }

void menualarm2()
{ //lcd.clear();
  lcd.setCursor(5,0);
  lcd.print("ALARM MENU");
  lcd.setCursor(0,1);
  lcd.print(" AKTYWACJA ALARMU");
  lcd.setCursor(0,2);
  lcd.print(">DEZAKTYWACJA ");
  lcd.setCursor(0,3);
  lcd.print("RESET NACIS * ");
}
void menualarm3()
{ //lcd.clear();
  lcd.setCursor(5,0);
  lcd.print("ALARM MENU");
  lcd.setCursor(0,1);
  lcd.print(" AKTYWACJA ALARMU");
  lcd.setCursor(0,2);
  lcd.print(" DEZAKTYWACJA ");
  lcd.setCursor(0,3);
  lcd.print("> RESET ANOMALI ");
}
void menubrama()
{ //lcd.clear();
  lcd.setCursor(5,0);
  lcd.print(" BRAMA MENU");
  lcd.setCursor(0,1);
  lcd.print(" STAN: ");
  lcd.setCursor(0,2);
  lcd.print("  ");
  lcd.setCursor(0,3);
  lcd.print(" ");
}
void menupiec ()
{
  
}
void menupiec1()

{      
       
       lcd.setCursor(0,0);
       lcd.print("    PIEC MENU");
       lcd.setCursor(0,1);
       lcd.print("TEMP ZADANA: ");
       lcd.setCursor(13,1);
       lcd.print(nastawa_co);
       lcd.setCursor(15,1);
       lcd.print(" C");
       lcd.setCursor(0,2);
       lcd.print("TEMP CO");
       lcd.setCursor(10,2);
       lcd.print(temp_co);
        lcd.setCursor(15,2);
       lcd.print(" C");
  
}

void aktywacja_alarmu(){
  if(znak_keypad == '#'){
    stan_aktywacja_alarmu = true;
  }
 }
 void reset_ok(){
  if(znak_keypad == '1'){
    stan_aktywacja_alarmu = false;
    stan_wyswietlenie_kom = false;
    akcja = 2;
    lcd.clear();
    lcd.home();
    lcd.print("RESET");
    delay(1000);
    lcd.clear();
    stan_aktywacja_alarmu = true;
  }
 }
 void dezaktywacja_alarmu(){
  
          if(znak_keypad == 'B'){
          alarm_haslo = false;
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("PODAJ HASLO");
          
          }
          
          if(znak_keypad){
          lcd.setCursor(0,0);
          lcd.print("PODAJ HASLO");
          dane[x] = znak_keypad;
          x++;
          Serial.println(x);
          Serial.println("alarm");
          if(x == 2){
            lcd.setCursor(0,1);
            lcd.print("x");
          }
          if(x == 3){
            lcd.setCursor(1,1);
            lcd.print("x");
          }
          if(x == 4){
            lcd.setCursor(2,1);
            lcd.print("x");
          }
          if(x == 5){
            lcd.setCursor(3,1);
            lcd.print("x");
          }
          }
    if(znak_keypad == '#'){ 
    if((dane[0] == haslo[0])&&
       (dane[1] == haslo[1])&&
          (dane[2] == haslo[2])&&
          (dane[3] == haslo[3])&&
          (dane[4] == haslo[4])){
    stan_aktywacja_alarmu = false;
    akcja = 2;
 
    lcd.setCursor(19,1);
    lcd.print(" ");
    digitalWrite(lampka_alarm,false);
   
    lcd.setCursor(0,0);
    lcd.print("HASLO POPRAWNE");
    delay(1000);
    lcd.clear();
    alarm_haslo = true;
    x = 0;
    
      }else{ 
        lcd.setCursor(0,0);
        lcd.print("HASLO NIE POPRAWNE");
        delay(1000);
        lcd.clear();
        alarm_haslo = true;
        x = 0;
      }
    }
  }
 
 
 
  
 void alarm_dzialanie(){
    if(stan_aktywacja_alarmu == true){
        lcd.setCursor(19,1);
        lcd.print("^");
        digitalWrite(lampka_alarm,true);
    if(digitalRead(czujnikp1) == true){
        akcja = 1;
        stan_wyswietlenie_kom = true;
    }
   // if(digitalRead(czujnikp2) == true){
     //   akcja = 1;
    //    stan_wyswietlenie_kom = true;
   //     }
   // if(digitalRead(czujnikp3) == true){
     //   akcja = 1;
     //   stan_wyswietlenie_kom = true;
   // }
   // if(digitalRead(czujnikp4) == true){
   //     akcja = 1;
   //     stan_wyswietlenie_kom = true;
   // }
  }
 
  /// dezaktywacja alarmu///
 
   switch(akcja){
    case 1:
    if(stan_wyswietlenie_kom == true){
    lcd.clear();
    lcd.print("AKTYWOWANO ALARM");
    lcd.setCursor(0,1);
    lcd.print("CZUJKA NR 1");
    delay(1000);
    lcd.clear();
    stan_wyswietlenie_kom = false;
    }
    
    digitalWrite(zamek_brama,false);
    digitalWrite(lampka_alarm_NOK,true);
    digitalWrite(buzzer,true);
  
  
    break;
    case 2:
    digitalWrite(zamek_brama,true);
    digitalWrite(lampka_alarm_NOK,false);
    digitalWrite(buzzer,false);
    break;
    
}
}
 void sterownik_co(){
   
    //licznik10++;
   // if(licznik10 == 20){
 
       lcd_co.setCursor(0,0);
       lcd_co.print("TEMP NASTAWA: ");
       lcd_co.setCursor(9,0);
       lcd_co.print(nastawa_co);
       lcd_co.setCursor(0,1);
       lcd_co.print("TEMP CO");
       lcd_co.setCursor(10,1);
       lcd_co.print(temp_co);
       //licznik10 = 20;
    //}
    Serial.print("stan licznika 10 ");
    Serial.println(licznik10);
    if(digitalRead(zadana_temp)== LOW){
      nastawa_co = nastawa_co + 10;
    }
    if(nastawa_co == 80){
      nastawa_co = 30;
    }
    if(temp_co >= nastawa_co){
      digitalWrite(pompa_co,LOW);
      }
      else{
      digitalWrite(pompa_co,HIGH);
      }
       
      
       
 }
 void sterownik_brama(){
  if(digitalRead(otwieranie_brama) == false){
    otworz_brama = true;
    Serial.println("otwieranie");
  }
  if(digitalRead(zamykanie_brama) == false){
    zamknij_brama = true;
    Serial.println("zamykanie");
  }
  if(digitalRead(krancowy_o) == false){
    otworz_brama = false;
  }
    if(digitalRead(krancowy_z) == false){
    zamknij_brama = false;
  }
  if(otworz_brama == true){
    digitalWrite(silnik_o,false);
    zamknij_brama = false;
  }else{
    digitalWrite(silnik_o,true);
  }
   if(zamknij_brama == true){
    digitalWrite(silnik_z,false);
    otworz_brama = false;
  }else{
    digitalWrite(silnik_z,true);
  }
 }
 
