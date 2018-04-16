#include <SimpleDHT.h>
#include "SR04.h"

//www.elegoo.com
//2016.12.9

#include <SimpleDHT.h>

// DHT11 sensor
int pinDHT11 = 2;
SimpleDHT11 dht11;
int setPoint = 55;
String readString;
char values[10];
int tempPin = 0;
int photoPin = 1;

// Ultrasonic Sensor
#define TRIG_PIN 12
#define ECHO_PIN 11
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
long a;

//4 module relay control
int relayControl1 = 3; 
int relayControl2 = 4;
int relayControl3 = 5; 
int relayControl4 = 6;



void setup() {
  Serial.begin(9600);
  pinMode(relayControl1, OUTPUT);
  pinMode(relayControl2, OUTPUT);
  pinMode(relayControl3, OUTPUT);
  pinMode(relayControl4, OUTPUT);
  
  digitalWrite(relayControl1, HIGH);
  digitalWrite(relayControl2, HIGH);
  digitalWrite(relayControl3, HIGH);
  digitalWrite(relayControl4, HIGH);
  delay(1000);
}  

void loop() {
  //read ext Temp/Humidity Sensor 
  byte temperature = 0;
  byte humidity = 0;
  byte data[40] = {
    0          };
  readString = "";
  delay(1000); 
  dht11.read(pinDHT11, &temperature, &humidity, data);
  temperature = temperature * 1.8 + 32;
  int intTemp = (int) temperature;
  
  //read D1 sensor
  a=sr04.Distance();
  
  //read Temp Probe
  int tempReading = analogRead(tempPin);
  double tempK = log(10000.0 * ((1024.0 / tempReading - 1)));
  tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempK * tempK )) * tempK );       //  Temp Kelvin
  float tempC = tempK - 273.15;            // Convert Kelvin to Celcius
  float tempF = (tempC * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit
  
  //read Photo pin 
  int lux = analogRead(photoPin);
  
  digitalWrite(relayControl1, LOW);
  
  
  while(!Serial.available()) {
    

  }
  
  // Get Commands From PI
  while (Serial.available())
  {
    Serial.readBytesUntil('Z', values , 10);
    //readString = values;
  }  
  
  
  
  delay(100);
  
  Serial.write("ET=");
  Serial.print(temperature);
  
  Serial.write(",ERH=");
  Serial.print(humidity);
  
  Serial.write(",D1=");
  Serial.print(a * 0.3937007874);
  Serial.write("in,");

  Serial.write("TP1=");
  Serial.print(tempF);

  Serial.write(",Light=");
  Serial.print(lux);  
  
  

}









