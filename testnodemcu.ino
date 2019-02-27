#include <ESP8266WiFi.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>
#include "DHT.h"
Adafruit_BMP085 bmp;
#define I2C_SCL 14
#define I2C_SDA 12
#define DHTTYPE DHT11
#define dht_dpin 0
DHT dht(dht_dpin, DHTTYPE);
String apiWritekey = "9ER6KGHNTI4KSNOC";
const char* ssid = "Redmi note 4";
const char* password = "anubhav1" ;
const char* server = "api.thingspeak.com";
WiFiClient client;
void setup() {
dht.begin();
Serial.begin(115200);
Wire.begin(I2C_SCL,I2C_SDA);
if (!bmp.begin()) {
Serial.println("Could not find a valid BMP085 sensor, check
wiring!");
while (1) {}
}
WiFi.disconnect();
delay(10);
WiFi.begin(ssid, password);
Serial.println();
Serial.println();
Serial.print("Connecting to ");
Serial.println(ssid);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.print("NodeMcu connected to wifi...");
Serial.println(ssid);
Serial.println();
}
void loop()
{
float h = dht.readHumidity();
int p = bmp.readPressure();
float t = dht.readTemperature();
Serial.print("Current humidity = ");
Serial.print(h);
Serial.print("% ");
Serial.print("temperature = ");
Serial.print(t);
Serial.println("C ");
Serial.print("Pressure = ");
Serial.print(p);
if (client.connect(server,80))
{
String tsData = apiWritekey;
tsData +="&field1=";
tsData += String(t);
tsData +="&field2=";
tsData += String(h);
tsData +="&field3=";
tsData += String(p);
tsData += "\r\n\r\n";
client.print("POST /update HTTP/1.1\n");
client.print("Host: api.thingspeak.com\n");
client.print("Connection: close\n");
client.print("X-THINGSPEAKAPIKEY: "+apiWritekey+"\n");
client.print("Content-Type: application/x-www-formurlencoded\
n");
client.print("Content-Length: ");
client.print(tsData.length());
client.print("\n\n");
client.print(tsData);
Serial.print("Temperature: ");
Serial.print(t);
client.print("\n\n");
Serial.print(h);
client.print("\n\n");
Serial.print(p);
Serial.println("uploaded to Thingspeak server....");
}
client.stop();
Serial.println("Waiting to upload next reading...");
Serial.println();
delay(15000);
}
