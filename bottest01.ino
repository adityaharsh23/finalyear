/* WIFI settings */
//const char* ssid = "saattvik";
//const char* password = "phantom1412";

/* data received from application */
//String  data =""; 

/* define L298N or L293D motor control pins */
//int leftMotorForward = 2;     /* GPIO2(D4) -> IN3   */
int leftMotorForward = 12;
int rightMotorForward = 15;   /* GPIO15(D8) -> IN1  */
//int leftMotorBackward = 0;

int leftMotorBackward = 10;/* GPIO0(D3) -> IN4   */
int rightMotorBackward = 13;  /* GPIO13(D7) -> IN2  */


/* define L298N or L293D enable pins */
int rightMotorENB = 14; /* GPIO14(D5) -> Motor-A Enable */
int leftMotorENB = 12;  /* GPIO12(D6) -> Motor-B Enable */

void setup()
{
  /* initialize motor control pins as output */
  pinMode(leftMotorForward, OUTPUT);
  pinMode(rightMotorForward, OUTPUT); 
  pinMode(leftMotorBackward, OUTPUT);  
  pinMode(rightMotorBackward, OUTPUT);

  /* initialize motor enable pins as output */
  pinMode(leftMotorENB, OUTPUT); 
  pinMode(rightMotorENB, OUTPUT);

  /* start server communication */
  //server.begin();
}

void loop()
{
    /* If the server available, run the "checkClient" function */  
   // client = server.available();
   // if (!client) return; 
    //data = checkClient ();

/******** Run function according to incoming data from application *********/

    /* If the incoming data is "forward", run the "MotorForward" function */
  //  if (data == "forward") MotorForward();
    /* If the incoming data is "backward", run the "MotorBackward" function */
    //else if (data == "backward") MotorBackward();
    /* If the incoming data is "left", run the "TurnLeft" function */
   // else if (data == "left") TurnLeft();
    /* If the incoming data is "right", run the "TurnRight" function */
   // else if (data == "right") TurnRight();
    /* If the incoming data is "stop", run the "MotorStop" function */
    //else if (data == "stop") MotorStop();
   //char ch;
   //ch=Serial.read();
   //if(ch=='1') MotorForward();
   //else if (ch=='2') MotorBackward();
  GolGol();
  GolGolAndar();
  
  
 
} 

/*************** FORWARD *******************/
void MotorForward(void)   
{
  digitalWrite(leftMotorENB,HIGH);
  digitalWrite(rightMotorENB,HIGH);
  digitalWrite(leftMotorForward,HIGH);
  digitalWrite(rightMotorForward,HIGH);
  digitalWrite(leftMotorBackward,LOW);
  digitalWrite(rightMotorBackward,LOW);
  
}
void GolGol(void)
{
   //digitalWrite(leftMotorENB,HIGH);
  //digitalWrite(rightMotorENB,HIGH); 
  
  analogWrite(leftMotorENB,254);
  analogWrite(rightMotorENB,254);
  digitalWrite(leftMotorForward,LOW);
  digitalWrite(rightMotorForward,HIGH);
  digitalWrite(rightMotorBackward,LOW);
  digitalWrite(leftMotorBackward,LOW);
  delay(500);
  digitalWrite(leftMotorENB,LOW);
  digitalWrite(rightMotorENB,LOW); 
  digitalWrite(leftMotorForward,LOW);
  digitalWrite(rightMotorForward,LOW);
  digitalWrite(rightMotorBackward,LOW);
  digitalWrite(leftMotorBackward,LOW);
}
void GolGolAndar(void)
{
  //digitalWrite(leftMotorENB,HIGH);
  //digitalWrite(rightMotorENB,HIGH);
  analogWrite(leftMotorENB,254);
  analogWrite(rightMotorENB,254);
  digitalWrite(leftMotorForward,HIGH);
  digitalWrite(rightMotorForward,LOW);
  digitalWrite(rightMotorBackward,LOW);
  digitalWrite(leftMotorBackward,LOW);
  delay(250);
  digitalWrite(leftMotorENB,LOW);
  digitalWrite(rightMotorENB,LOW); 
  digitalWrite(leftMotorForward,LOW);
  digitalWrite(rightMotorForward,LOW);
  digitalWrite(rightMotorBackward,LOW);
  digitalWrite(leftMotorBackward,LOW);
}
/*************** BACKWARD *******************/
void MotorBackward(void)   
{
  digitalWrite(leftMotorENB,HIGH);
  digitalWrite(rightMotorENB,HIGH);
  digitalWrite(leftMotorBackward,HIGH);
  digitalWrite(rightMotorBackward,HIGH);
  digitalWrite(leftMotorForward,LOW);
  digitalWrite(rightMotorForward,LOW);
}

/*************** TURN LEFT *******************/
void TurnLeft(void)   
{
  digitalWrite(leftMotorENB,HIGH);
  digitalWrite(rightMotorENB,HIGH); 
  digitalWrite(leftMotorForward,LOW);
  digitalWrite(rightMotorForward,HIGH);
  digitalWrite(rightMotorBackward,LOW);
  digitalWrite(leftMotorBackward,HIGH);  
}

/*************** TURN RIGHT *******************/
void TurnRight(void)   
{
  digitalWrite(leftMotorENB,HIGH);
  digitalWrite(rightMotorENB,HIGH);
  digitalWrite(leftMotorForward,HIGH);
  digitalWrite(rightMotorForward,LOW);
  digitalWrite(rightMotorBackward,HIGH);
  digitalWrite(leftMotorBackward,LOW);
}

/*************** STOP *******************/
void MotorStop(void)   
{
  digitalWrite(leftMotorENB,HIGH);
  digitalWrite(rightMotorENB,HIGH);
  digitalWrite(leftMotorForward,LOW);
  digitalWrite(leftMotorBackward,LOW);
  digitalWrite(rightMotorForward,LOW);
  digitalWrite(rightMotorBackward,LOW);
}

/************ RECEIVE DATA FROM the APP **************/
//String checkClient (void)
//{
  //while(!client.available()) delay(1); 
  //String request = client.readStringUntil('\r');
  //request.remove(0, 5);
  //request.remove(request.length()-9,9);
  //return request;
//}
