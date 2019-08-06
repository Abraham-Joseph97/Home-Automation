#include "DHTesp.h"
#include "UbidotsMicroESP8266.h"
#include<ESP8266WiFi.h>
#define TOKEN "BBFF-rxr6LKExjPwkUF51I9xsCJ30sxbEEg"
#define ID_1 "5d14907a1d847256ae6ccd01"

#define WIFISSID "esp"
#define PASSWORD "12345678"

float humidity=0;

Ubidots client(TOKEN);
DHTesp dht;


void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
Serial.println();
Serial.println("Status\tHumidity");
String thisBoard=ARDUINO_BOARD;
Serial.println(thisBoard);
dht.setup(13,DHTesp::DHT11);
client.wifiConnection(WIFISSID,PASSWORD);
pinMode(5,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  delay(dht.getMinimumSamplingPeriod());
  float humidity=dht.getHumidity();
  
  client.add(ID_1,humidity);

  client.sendAll(false);
  delay(1000);
 Serial.print(dht.getStatusString());
 Serial.print("\t");
 Serial.print(humidity);
 float value=client.getValueWithDevice("demo","humidity");
 if(value>75)
 {
  digitalWrite(5,HIGH);
  
 } 
else

{
  digitalWrite(5,LOW);

}

}
