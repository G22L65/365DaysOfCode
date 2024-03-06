String voice;
#define relay1 7    //Connect relay1 to pin 7
#define relay2 6    //Connect relay2 to pin 6
#define relay3 5   //Connect relay1 to pin 5
#define relay4 4    //Connect relay2 to pin 4
#define pin1 8 //input read from ESP
#define pin2 2 //input read from ESP
#define pin3 12 //input read from ESP
#define pin4 13//input read from ESP
// const int trigPin = 9; //pin setup for ultrasonic sensor
// const int echoPin = 10; //pin setup for ultrasonic sensor
// // defines variables for ultrasonic sensor
// long duration;
// int distance;

void setup()
{
  Serial.begin(9600);            //Set rate for communicating with phone
  pinMode(relay1, OUTPUT);       //Set relay1 as an output
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);      //Set relay2 as an output
  pinMode(relay4, OUTPUT);
  // pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output (ULTRASONIC SENSOR)
  // pinMode(echoPin, INPUT); // Sets the echoPin as an Input  (ULTRASONIC SENSOR)
  pinMode(pin1,INPUT);
  pinMode(pin2,INPUT);
  pinMode(pin3,INPUT);
  pinMode(pin4,INPUT);
  
  digitalWrite(relay1, HIGH);     //Switch relay1 off
  digitalWrite(relay2, HIGH);     //Swtich relay2 off
  digitalWrite(relay3, HIGH);     //Switch relay1 off
  digitalWrite(relay4, HIGH);     //Swtich relay2 off

}
int value1=0;
int value2=0;
int value3=0;
int value4=0;
bool flag=false;

void loop()
{
  //  {
  //   // Clears the trigPin
  //   digitalWrite(trigPin, LOW);
  //   delayMicroseconds(2);
  //   // Sets the trigPin on HIGH state for 10 micro seconds
  //   digitalWrite(trigPin, HIGH);
  //   delayMicroseconds(10);
  //   digitalWrite(trigPin, LOW);
  //   // Reads the echoPin, returns the sound wave travel time in microseconds
  //   duration = pulseIn(echoPin, HIGH);
  //   // Calculating the distance
  //   distance= duration*0.034/2;
  //   // Prints the distance on the Serial Monitor
  //   Serial.print("Distance: ");
  //   Serial.println(distance);
  //   if((distance==2)){
  //     switchoff();
  //   }
  //  }



  delay(500);

  int val1=digitalRead(pin1);
  int val2=digitalRead(pin2);
  int val3=digitalRead(pin3);
  int val4=digitalRead(pin4);

  if(val1!=value1 && flag==true) value1=val1;
  if(val2!=value2 && flag==true) value2=val2;
  if(val3!=value3 && flag==true) value3=val3;
  if(val4!=value4 && flag==true) value4=val4;
  

  Serial.println(value1);
  Serial.println(value2);
  Serial.println(value3);
  Serial.println(value4);
  Serial.println("---------------------------");
  Serial.println("---------------------------");
  Serial.println("---------------------------");

  while (Serial.available())   //Check if there are available bytes to read
  {
    
    delay(10);                 //Delay to make it stable
    char c = Serial.read();    //Conduct a serial read
    if (c == '#') {
      break;                   //Stop the loop once # is detected after a word
    }
    voice += c;                //Means voice = voice + c
  }

  if(value1==1) digitalWrite(relay1,LOW);
  else if(value1==0) digitalWrite(relay1,HIGH);
  
  if(value2==1) digitalWrite(relay2,LOW);
  else if(value2==0) digitalWrite(relay2,HIGH);

  if(value3==1) digitalWrite(relay3,LOW);
  else if(value3==0) digitalWrite(relay3,HIGH);

  if(value4==1) digitalWrite(relay4,LOW);
  else if(value4==0) digitalWrite(relay4,HIGH);


  if (voice.length()>0)
  {
    Serial.println(voice);
    if ((voice == "all on")or(voice=="all one")or(voice=="all 1")or(voice=="all")or(voice=="Sab khol do")or(voice=="call on")or(voice=="orlon")or(voice=="alone")or(voice=="follow")or(voice=="hello")or(voice=="home loan")or(voice=="alarm")or(voice=="Allen")or(voice=="allen")or(voice=="Elan")or(voice=="elan")or(voice=="aur aur")) {
      switchon();value1=1;value2=1;value3=1;value4=1;
    }
    else if ((voice == "all off")or(voice=="all of")or(voice=="call of")or(voice=="call off")or(voice=="alof")or(voice=="alos")or(voice=="Talaash")or(voice=="a loss")or(voice=="band karo")or(voice=="all office")or(voice=="all of us")or(voice=="call office")or(voice=="")or(voice=="all one")or(voice=="all one")or(voice=="all one")) {
      switchoff();value1=0;value2=0;value3=0;value4=0;
    }
    else if ((voice == "relay 1 on")or(voice=="relay 11")or(voice=="relay banaun")or(voice=="relay one on")or(voice=="reliever")or(voice=="11 on")or(voice=="relay 1")or(voice=="11")or(voice=="v11 on")or(voice=="1 ons")or(voice=="nibandh on")or(voice=="11.")or(voice=="release on")or(voice=="Sevan on")or(voice=="anyone on")or(voice=="all of")or(voice=="all of")) {
      digitalWrite(relay1, LOW);
      Serial.println("relay1ison");
      value1=1;
      
    }
    else if ((voice == "relay 1 off")or (voice == "Sri 11 off")or(voice == "relay band off")or(voice == "11 off")or(voice == "velavan off")or(voice == "ralegan off")or(voice == "relay on off")or(voice == "relevance of")or(voice == "give me one of")or(voice == "one of")or(voice == "relay one box")or(voice == "relay one of")or(voice == "relation of")or(voice == "slogan of")) {
      digitalWrite(relay1, HIGH);
      value1=0;
    }
    else if ((voice == "relay 2 on")) {
      digitalWrite(relay2, LOW);
      value2=1;
    }
    else if ((voice == "relay 2 off")) {
      digitalWrite(relay2, HIGH);
      value2=0;
    }
    else if ((voice == "relay 3 on")) {
      digitalWrite(relay3, LOW);
      value3=1;
    }
    else if ((voice == "relay 3 off")) {
      digitalWrite(relay3, HIGH);
      value3=0;
    }
    else if ((voice == "relay 4 on")) {
      digitalWrite(relay4, LOW);
      value4=1;
    }
    else if ((voice == "relay 4 off")) {
      digitalWrite(relay4, HIGH);
      value4=0;
    }

    else if(voice=="internet mode") flag=true;
    else if(voice=="bluetooth mode") flag=false;
    voice = "";
  }
}
void switchon()               //Function for turning on relays
{
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, LOW);
}
void switchoff()              //Function for turning on relays
{
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
}
