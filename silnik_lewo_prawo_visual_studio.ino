int s11 =2;
int s12 =3;
int stan;
bool zezwolenie;


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(s11,OUTPUT);
pinMode(s12,OUTPUT);
stan = 0;
zezwolenie = false;
}

void loop() {
  
;// put your main code here, to run repeatedly:
char data = Serial.read();
switch(data){
  case 'c':
  zezwolenie = true;
  break;
  case 'd':
  zezwolenie = false;
  break;
  }
if(zezwolenie == true){
switch (data){
  case 'a':
  digitalWrite(s11,HIGH);
  digitalWrite(s12,LOW);
  stan = stan + 10;
  digitalWrite(s11,LOW);
  digitalWrite(s12,LOW);
  break;
  case 'b':
  digitalWrite(s12,HIGH);
  digitalWrite(s11,LOW);
   stan = stan - 10;
  digitalWrite(s11,LOW);
  digitalWrite(s12,LOW);
  break;
  }
  
  Serial.println(stan);
  
  if(stan == 360){
    stan = 0;
  }
 
  }else{
  }
  }

  

