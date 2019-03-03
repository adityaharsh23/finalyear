#include <ESP8266WiFi.h>
int leftMotorForward = 12;
int rightMotorForward = 15;
int leftMotorBackward = 10;/* GPIO0(D3) -> IN4   */
int rightMotorBackward = 13;
int nb,ob;
float diffb,dely;
void setup() {
  // put your setup code here, to run once:
  pinMode(leftMotorForward, OUTPUT);
  pinMode(rightMotorForward, OUTPUT); 
  pinMode(leftMotorBackward, OUTPUT);  
  pinMode(rightMotorBackward, OUTPUT);
  Serial.begin(9600);
}

void loop() {
nb=90;
ob=0;
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
  
  Serial.print("Bot will now move::");
  Serial.print(diffb);
  Serial.print("with delay");
  Serial.print(dely);
  khanna(110);
  //delay(11000);
  //Serial.print("Motor stopping");
  MotorStop();
  delay(5000);
  
  
  // put your main code here, to run repeatedly:

}
int n=0;
void khanna(int x)
{
  while(n<x)
  {
  digitalWrite(leftMotorForward,LOW);
  digitalWrite(rightMotorForward,HIGH);
  digitalWrite(rightMotorBackward,LOW);
  digitalWrite(leftMotorBackward,LOW);
  delay(25);
  
  digitalWrite(rightMotorForward,HIGH);
  digitalWrite(rightMotorBackward, LOW);
  digitalWrite(leftMotorBackward, LOW);
  digitalWrite(leftMotorForward,HIGH);
  delay(75);
  n++;
  }
}

void MotorStop(void)   
{
 
  digitalWrite(leftMotorForward,LOW);
  digitalWrite(leftMotorBackward,LOW);
  digitalWrite(rightMotorForward,LOW);
  digitalWrite(rightMotorBackward,LOW);
}
