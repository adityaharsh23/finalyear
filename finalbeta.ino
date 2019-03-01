//flow. get gps data. send using nodemcu. recieve using thingspeak. move bot usign algorithm
#include <ESP8266WiFi.h>;
#include <WiFiClient.h>;
#include <ThingSpeak.h>;
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>  //ver 5.13.4 only
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
//pre functions start
float fv; //fieldvalue
//gps pre function begin
TinyGPSPlus gps;  // The TinyGPS++ object
SoftwareSerial ss(4, 5); // The serial connection to the GPS device
const char* ssid = "POCO F1";
const char* password = "anubhav1";
float latitude , longitude;
//int year , month , date, hour , minute , second;
int nb;
int ob=0;
//ob=10;
float dely;
float diffb;
int counter=0;
//String date_str , time_str , lat_str , lng_str;
//int pm;
WiFiServer server(80);
//gps pre function ends

//send data pre function begins
//const char* ssid = "POCO F1"; //Your Network SSID
//const char* password = "anubhav1"; //Your Network Password
int lat,lon;
WiFiClient client;
unsigned long myChannelNumber = 716675; //Your Channel Number (Without Brackets)
const char * myWriteAPIKey = "3F0X694HYNGO5PJ9"; //Your Write API Key
//send data pre function ends

//recieve pre function begins
//WiFiServer server(80); 
char   host[] = "api.thingspeak.com"; // ThingSpeak address
String APIkey = "716643";             // Thingspeak Read Key, works only if a PUBLIC viewable channel
const int httpPort = 80; 
//const char *ssid     = "POCO F1"; 
//const char *password = "anubhav1"; 
//WiFiClient client;
const unsigned long HTTP_TIMEOUT = 10000; // max respone time from server
//recieve pre function ends

//bot movement pre fucntion begins
/* define L298N or L293D motor control pins */
//int leftMotorForward = 2;     /* GPIO2(D4) -> IN3   */
int leftMotorForward = 12;
int rightMotorForward = 15;   /* GPIO15(D8) -> IN1  */
//int leftMotorBackward = 0;
int leftMotorBackward = 10;/* GPIO0(D3) -> IN4   */
int rightMotorBackward = 13;  /* GPIO13(D7) -> IN2  */
/* define L298N or L293D enable pins */
int rightMotorENB = 14; /* GPIO14(D5) -> Motor-A Enable */
int leftMotorENB = 12; /* GPIO12(D6) -> Motor-B Enable */
//bot movement pre function ends

//pre functions end

//setup begins
void setup()
{
//gps begin
Serial.begin(115200);
Serial.print("prefunction");
  ss.begin(9600);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());

//gps end
//send data start
//Serial.begin(9600);
 delay(10);
 // Connect to WiFi network 
//WiFi.begin(ssid, password);
ThingSpeak.begin(client);
Serial.print("thingspeak started");
 //send data end
//recieve data begin
//Serial.begin(115200);
//WiFi.begin(ssid,password);
//recieve data end
//bot movement start
  /* initialize motor control pins as output */
  pinMode(leftMotorForward, OUTPUT);
  pinMode(rightMotorForward, OUTPUT); 
  pinMode(leftMotorBackward, OUTPUT);  
  pinMode(rightMotorBackward, OUTPUT);

  /* initialize motor enable pins as output */
  pinMode(leftMotorENB, OUTPUT); 
  pinMode(rightMotorENB, OUTPUT);
  
  ob=0;
  
//bot movement end
}
//setup ends

//loop begins
void loop()
{
//gps begin
//Serial.print("loop begins");
  //while (ss.available() > 0 && counter<1){
    if (gps.encode(ss.read()))
    {
      if (gps.location.isValid())
      {
        latitude = gps.location.lat(); //numerical value(float)
        //lat_str = String(latitude , 6);
        longitude = gps.location.lng(); //numerical value (float)
        //lng_str = String(longitude , 6);
        Serial.print(latitude);
        Serial.print("Lat\n");
        Serial.print(longitude);
        Serial.print("Lon\n");
        counter++;
        
      }
    }
  
  //Serial.print("While ends");
  // Check if a client has connected
//  WiFiClient client = server.available();
//  if (!client)
//  {
//    return;
//  }

 Serial.println("Uploading data to thingspeak:");
  Serial.print("Lat:");
Serial.println(latitude);
Serial.print("Lon:");
 Serial.print(longitude);
//Print on Serial Monitor
 
delay(1000);
 
ThingSpeak.writeField(myChannelNumber, 1,latitude, myWriteAPIKey);
delay(15000);
ThingSpeak.writeField(716686, 1,longitude, "GJXBTXZVVZ1HKPI0");
Serial.print("upload done");
//Update in ThingSpeak
delay(15000);
 
//send end
//recieve begin
Serial.print("recieving data");
RetrieveTSChannelData();
delay(60000);
Serial.print("recieved");//Wait before we request again
//recieve end
//bot begin
 nb=fv;
if(nb>ob)
  {
    diffb=nb-ob;
  }
  else
  {
    diffb=360-(nb-ob);
  }
  dely=(0.97*diffb)/13.037;
  dely=dely*1000; 
  delay(15000);
  Serial.print("Bot will now move::");
  Serial.print(diffb);
  Serial.print("with delay");
  Serial.print(dely);
  GolGolDrift();
  delay(dely);
  MotorStop();
  ob=nb;
delay(10000);
//bot end
  delay(30000);
}
//loop ends

//post function
void RetrieveTSChannelData() {  // Receive data from Thingspeak
  static char responseBuffer[3*1024]; // Buffer for received data
  client = server.available(); 
  if (!client.connect(host, httpPort)) { 
    Serial.println("connection failed"); 
    return; 
  } 
  String url = "/channels/" + APIkey; // Start building API request string
  url += "/fields/1.json?results=5";  // 5 is the results request number, so 5 are returned, 1 woudl return the last result received
  client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
  while (!skipResponseHeaders());                      // Wait until there is some data and skip headers
  while (client.available()) {                         // Now receive the data
    String line = client.readStringUntil('\n');
    if ( line.indexOf('{',0) >= 0 ) {                  // Ignore data that is not likely to be JSON formatted, so must contain a '{'
      Serial.println(line);                            // Show the text received
      line.toCharArray(responseBuffer, line.length()); // Convert to char array for the JSON decoder
      decodeJSON(responseBuffer);                      // Decode the JSON text
    }
  }
  client.stop();
}

bool skipResponseHeaders() { 
  char endOfHeaders[] = "\r\n\r\n"; // HTTP headers end with an empty line 
  client.setTimeout(HTTP_TIMEOUT); 
  bool ok = client.find(endOfHeaders); 
  if (!ok) { Serial.println("No response or invalid response!"); } 
  return ok; 
} 

bool decodeJSON(char *json) {
  StaticJsonBuffer <3*1024> jsonBuffer;
  char *jsonstart = strchr(json, '{'); // Skip characters until first '{' found and ignore length, if present
  if (jsonstart == NULL) {
    Serial.println("JSON data missing");
    return false;
  }
  json = jsonstart;
  JsonObject& root = jsonBuffer.parseObject(json); // Parse JSON
  if (!root.success()) {
    Serial.println(F("jsonBuffer.parseObject() failed"));
    return false;
  }
  JsonObject& root_data = root["channel"]; // Begins and ends within first set of { }
  String id   = root_data["id"];
  String name = root_data["name"];
  String field1_name = root_data["field1"];
  String datetime    = root_data["updated_at"];
  Serial.println("\n\n Channel id: "+id+" Name: "+ name);
  Serial.println(" Readings last updated at: "+datetime);
  
  for (int result = 0; result < 5; result++){
    JsonObject& channel = root["feeds"][result]; // Now we can read 'feeds' values and so-on
    String entry_id     = channel["entry_id"];
    String field1value  = channel["field1"];
    Serial.print(" Field1 entry number ["+entry_id+"] had a value of: ");
    Serial.println(field1value);
    //enter max value
   fv=field1value.toInt(); //*8888888888888888888888888888888888888888888888888888888888888
  }
}
void GolGolDrift(void)
{
  digitalWrite(leftMotorENB,HIGH);
  digitalWrite(rightMotorENB,HIGH);
  digitalWrite(leftMotorForward,LOW);
  digitalWrite(rightMotorForward,HIGH);
  digitalWrite(rightMotorBackward,LOW);
  digitalWrite(leftMotorBackward,LOW);
  delay(50);
  digitalWrite(leftMotorENB,HIGH);
  digitalWrite(rightMotorENB,HIGH);
  digitalWrite(rightMotorForward,HIGH);
  digitalWrite(leftMotorForward,HIGH);
  delay(75);
}
void MotorStop(void)   
{
  digitalWrite(leftMotorENB,HIGH);
  digitalWrite(rightMotorENB,HIGH);
  digitalWrite(leftMotorForward,LOW);
  digitalWrite(leftMotorBackward,LOW);
  digitalWrite(rightMotorForward,LOW);
  digitalWrite(rightMotorBackward,LOW);
}
