#include <OneWire.h>
#include <DallasTemperature.h>
#include <SoftwareSerial.h>

#define ONE_WIRE_BUS 4 //4 = numéro d'entrée port 4

OneWire oneWire(ONE_WIRE_BUS); 
DallasTemperature sensors(&oneWire);

byte sensor2 [ 8 ] = { 0x28 , 0xF1 , 0x3F , 0x5E , 0x12 , 0x21 , 0x01 , 0x23 } ; //sonde nico
byte sensor1 [ 8 ] = { 0x28 , 0x05 , 0x57 , 0x75 , 0x12 , 0x21 , 0x01 , 0x46 } ; //sonde lucien

const int ventilo=9; 
const int led=2;
const int pompe=12;
float Tchoisi = 20; // température idéal
String fromPython; //chaine venant de python via port série
float Humidite;
int SensorHum=1;
int HumiditeIdeale=20;
int i=101;
int etatVentilo=0;
int etatPompe=0;
int etatLed=0;
int tempRecue=0;
int humRecue=0;

void setup() {

  Serial.begin(9600);

  sensors.begin(); 

  pinMode(pompe, OUTPUT);
  digitalWrite(pompe, LOW);
  
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);

  pinMode(ventilo, OUTPUT);
  digitalWrite(ventilo, LOW);
}



void loop() {

sensors.requestTemperatures();

float temp = sensors.getTempC(sensor1);
float tempext = sensors.getTempC(sensor2);

  Humidite = analogRead(SensorHum);
  Humidite = (Humidite*100)/1023;
  
delay(1000);
i+=1;


 //allumer la pompe si H<HumiditeIdeal
 if (i>100){
  if(Humidite<HumiditeIdeale){
    digitalWrite(pompe, HIGH);
    etatPompe=1;
    delay(2000);
    digitalWrite(pompe, LOW);
    etatPompe=0;
    i=0;
  }
 }

 if(temp>Tchoisi){
    digitalWrite(ventilo, HIGH);
    etatVentilo=1;
    digitalWrite(led,LOW);
    etatLed=0;
 }
 if (temp<Tchoisi) {
  digitalWrite(ventilo,LOW);
  etatVentilo=0;
  digitalWrite(led,HIGH);
  etatLed=1;
 }

  if (Serial.available()) {
    fromPython = Serial.readStringUntil('\n');
    if(fromPython == "?"){
      Serial.print(tempext);
      Serial.print("/");
      Serial.print(temp);
      Serial.print("/");
      Serial.print(Humidite);
      Serial.print("/");
      Serial.print(etatVentilo);
      Serial.print("/");
      Serial.print(etatLed);
      Serial.print("/");
      Serial.println(etatPompe);
    }

     if(fromPython == "setTemp"){
      Serial.println("Saisissez la nouvelle valeure de température : ");
      delay(5000);
      if (Serial.available()) {
        Tchoisi =(Serial.readString()).toInt();
        Serial.print("Valeur de la temperature modifiée : ");
        Serial.println(Tchoisi);
      }
     }
       
      if(fromPython == "setHum"){
        Serial.println("saisissez la nouvelle valeure d'humidité :");
        delay(5000);
        if (Serial.available()) {
          HumiditeIdeale=(Serial.readString()).toInt();
          Serial.print("Valeur de l'humidité modifiée : ");
          Serial.println(HumiditeIdeale);
        }
      }
  }
} 