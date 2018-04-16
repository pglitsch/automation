#include <SimpleDHT.h>

//www.elegoo.com
//2016.12.9

#include <SimpleDHT.h>

int pinDHT11 = 2;
SimpleDHT11 dht11;
int setPoint = 55;
String readString;
char values[10];
#include "SR04.h"
#define TRIG_PIN 12
#define ECHO_PIN 11
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
long a;


void setup() {
  Serial.begin(9600);
}  

void loop() {
  //read sensor data 
  byte temperature = 0;
  byte humidity = 0;
  byte data[40] = {
    0          };
  readString = "";
  delay(1000); 
  dht11.read(pinDHT11, &temperature, &humidity, data);
  temperature = temperature * 1.8 + 32;
  int intTemp = (int) temperature;
  /*Serial.print("Sample OK: ");
   Serial.print((int)temperature); 
   Serial.print(" *F, ");
   Serial.print((int)humidity); 
   Serial.println(" %"); */
  // get distance 1
  a=sr04.Distance();
  
  while(!Serial.available()) {
    //what is this for?

  }
  // Get Commands From PI
  while (Serial.available())
  {
    Serial.readBytesUntil('Z', values , 10);
    //readString = values;
  }  

  delay(500);


  //char ard_sends = '1';
  //Serial.print("Arduino sends: ");
  Serial.write("ET=");
  Serial.print(temperature);
  Serial.write(",");
  Serial.write("ERH=");
  Serial.print(humidity);
  Serial.write(",");
  Serial.print(a);
  Serial.println("cm");





  /*byte temperature = 0;
   byte humidity = 0;
   byte data[40] = {
   0      };
   
   
   
   
   
  /*Serial.print("Sample RAW Bits: ");
   for (int i = 0; i < 40; i++) {
   Serial.print((int)data[i]);
   if (i > 0 && ((i + 1) % 4) == 0) {
   Serial.print(' ');
   }
   } */
  //Serial.println("");
  //convert to fahrenheit 

  // DHT11 sampling rate is 1HZ.
  //delay(1000);
}









