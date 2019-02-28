//flow. get gps data. send using nodemcu. recieve using thingspeak. move bot usign algorithm
#include <ESP8266WiFi.h>;
#include <WiFiClient.h>;
#include <ThingSpeak.h>;
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
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
int year , month , date, hour , minute , second;
//String date_str , time_str , lat_str , lng_str;
//int pm;
WiFiServer server(80);
//gps pre function ends

//send data pre function begins
//const char* ssid = "POCO F1"; //Your Network SSID
//const char* password = "anubhav1"; //Your Network Password
int lat,lon;
WiFiClient client;
unsigned long myChannelNumber = 714903; //Your Channel Number (Without Brackets)
const char * myWriteAPIKey = "Z6GOD6KR8F2ZBUVG"; //Your Write API Key
//send data pre function ends

//recieve pre function begins
//WiFiServer server(80); 
char   host[] = "api.thingspeak.com"; // ThingSpeak address
String APIkey = "714951";             // Thingspeak Read Key, works only if a PUBLIC viewable channel
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
  static int nb,ob;
  ob=0;
  int dely;
int diffb;
//bot movement end
}
//setup ends

%loop begins
void loop()
{
//gps begin
  while (ss.available() > 0)
    if (gps.encode(ss.read()))
    {
      if (gps.location.isValid())
      {
        latitude = gps.location.lat(); //numerical value(float)
        lat_str = String(latitude , 6);
        longitude = gps.location.lng(); //numerical value (float)
        lng_str = String(longitude , 6);
        Serial.print(latitude);
        Serial.print("Lat\n");
        Serial.print(longitude);
        Serial.print("Lon\n");
        
      }
    }
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client)
  {
    return;
  }

  // Prepare the response
  //String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n <!DOCTYPE html> <html> <head> <title>GPS Interfacing with NodeMCU</title> <style>";
  //s += "a:link {background-color: YELLOW;text-decoration: none;}";
  //s += "table, th, td {border: 1px solid black;} </style> </head> <body> <h1  style=";
  //s += "font-size:300%;";
  //s += " ALIGN=CENTER> GPS Interfacing with NodeMCU</h1>";
  //s += "<p ALIGN=CENTER style=""font-size:150%;""";
  //s += "> <b>Location Details</b></p> <table ALIGN=CENTER style=";
  //s += "width:50%";
  //s += "> <tr> <th>Latitude</th>";
  //s += "<td ALIGN=CENTER >";
  //s += lat_str;
  //s += "</td> </tr> <tr> <th>Longitude</th> <td ALIGN=CENTER >";
  //s += lng_str;
  //s += "</td> </tr> <tr>  <th>Date</th> <td ALIGN=CENTER >";
  //s += date_str;
  //s += "</td></tr> <tr> <th>Time</th> <td ALIGN=CENTER >";
  //s += time_str;
  //s += "</td>  </tr> </table> ";
 
  
  //if (gps.location.isValid())
  //{
    //s += "<p align=center><a style=""color:RED;font-size:125%;"" href=""http://maps.google.com/maps?&z=15&mrt=yp&t=k&q=";
    //s += lat_str;
    //s += "+";
    //s += lng_str;
    //s += """ target=""_top"">Click here!</a> To check the location in Google maps.</p>";
  //}

  //s += "</body> </html> \n";

client.print(s);
delay(100);
//gps end
//send begin
//val1 = 10;
//val2=15;
//analogRead(LDRpin); //Read Analog values and Store in val variable
 Serial.println("Uploading data to thingspeak:")
  Serial.print("Lat:");
Serial.println(latitude);
Serial.print("Lon:");
 Serial.print(longitude);
//Print on Serial Monitor
 
delay(1000);
 
ThingSpeak.writeField(myChannelNumber, 1,latitude, myWriteAPIKey);
ThingSpeak.writeField(myChannelNumber, 2,longitude, myWriteAPIKey);
//Update in ThingSpeak
delay(15000);
 
//send end
//recieve begin
RetrieveTSChannelData();
delay(60000); //Wait before we request again
//recieve end
//bot begin
 nb=atoi(fv);
if(nb>ob)
  {
    diffb=nb-ob;
  }
  else
  {
    diffb=360-(nb-ob);
  }
  dely=((352/360)*(nb-ob))/13.037;
  dely=dely*1000; 
  GolGolDrift();
  delay(dely);
  MotorStop();
  ob=nb;
delay(10000);
//bot end
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
   fv=field1value;
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
