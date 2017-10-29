/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************

  This sketch shows how to read values from Virtual Pins

  App project setup:
    Slider widget (0...100) on Virtual Pin V1
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "<auth>";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "<SSID>";
char pass[] = "<Password>";
int T1=22,T2=50,i=0,Count=1,Start_Button=0,Freerun_Button=0,tickPin=D1,End_time=0,Start_time=0,Run_time=0;

// This function will be called every time Slider Widget
// in Blynk app writes values to the Virtual Pin V1
BLYNK_WRITE(V1)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  T1 = pinValue;
  Serial.print("T1=");
  Serial.println(T1);
  
  // process received value
}

BLYNK_WRITE(V2)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  T2 = pinValue;
  Serial.print("T2=");
  Serial.println(T2);
  
  // process received value
}

BLYNK_WRITE(V3)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  Count = pinValue;
  Serial.print("Count=");
  Serial.println(Count);
  
  // process received value
}


BLYNK_WRITE(V4)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  Start_Button = pinValue;
  Serial.print("Start_Button=");
  Serial.println(Start_Button);
  // process received value
}

BLYNK_WRITE(V5)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  Freerun_Button = pinValue;
  Serial.print("Freerun_Button=");
  Serial.println(Freerun_Button);
  // process received value
}

void tickHigh(){
  tickPin = (tickPin == D1 ? D2: D1);
  digitalWrite(tickPin, HIGH);
  delay(T1);
  digitalWrite(tickPin, LOW);
}

void tickLow(){
  tickPin = (tickPin == D1 ? D2: D1);
  digitalWrite(tickPin, HIGH);
  delay(T1);
  digitalWrite(tickPin, LOW);
}

void Counter()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(6, i);
}

void RunTime(int Run_time)
{
  Blynk.virtualWrite(7,Run_time);
  Serial.println(Run_time);
  
}

void setup()
{
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  // Debug console
  Serial.begin(9600);
//  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);
  Blynk.begin(auth, ssid, pass, IPAddress(<local_IP>), 8442);
}

void loop()
{
  Blynk.run();
  if (Start_Button == 1) {
    Start_time=millis();
    RunTime(0);
    if (Freerun_Button == 1){
        tickHigh();
        delay(T2);
        tickLow();
        delay(T2);
        i=i+1;
        Serial.println(i);
    }
    else
    {
    for (int i=0; i<Count;i++) {  
        tickHigh();
        delay(T2);
        tickLow();
        delay(T2);
        Serial.println(i);
    }
    End_time=millis();
    Run_time=End_time-Start_time;
    RunTime(Run_time);
    Start_Button = 0;
    }
  }
  else
  if (i!=0) {
    Counter();
    End_time=millis();
    Run_time=End_time-Start_time;
    RunTime(Run_time);
    i=0;
  }
}



