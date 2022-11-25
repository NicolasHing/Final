#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 4

OneWire oneWire(ONE_WIRE_BUS); 
DallasTemperature sensors(&oneWire);
DeviceAddress insideThermometer;

int deviceCount=0;
DeviceAddress deviceAddress;

void setup() {
  Serial.begin(9600);
  sensors.begin();
  deviceCount = sensors.getDeviceCount();
  Serial.println(deviceCount);

  for  ( int i = 0; i < deviceCount; i ++ )  {
    Serial.print ( "Capteur" ) ;
    Serial.print ( i + 1 ) ;
    Serial.print (":") ;
    sensors.getAddress(deviceAddress, i) ;
    printAddress (deviceAddress);
  }
  
}

void loop() {
}

void  printAddress ( DeviceAddress deviceAddress )  {
  for  ( uint8_t i = 0; i < 8; i ++ )  {
    Serial.print ("0x") ;
    if  ( deviceAddress [ i ]  <  0x10 )  {
      Serial.print ("0") ;
    }
    Serial.print ( deviceAddress [ i ] , HEX );
    if  ( i < 7 )  {
      Serial.print (",");
    }
  }
  Serial.println ();
}