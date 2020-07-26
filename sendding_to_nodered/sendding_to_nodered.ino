
#include "AIS_NB_BC95.h"
#include <Wire.h>
#include <string.h>
#include <avr/wdt.h>

String udpData = ""; //ค่าที่จะส่ง
String serverIP = "34.87.188.142"; // Your Server IP Nord-red
String serverPort = "2468"; // Your Server Port
String all_notlast;
bool check_udp = true;

AIS_NB_BC95 AISnb;
const int interval = 1000;
unsigned long previousMillis = 0;

#define pinresponse 12

void setup()
{
  pinMode(pinresponse , OUTPUT);
  digitalWrite(pinresponse , HIGH);
  
  AISnb.debug = true;
  Serial.begin(9600);
  AISnb.setupDevice(serverPort);
  String ip1 = AISnb.getDeviceIP();
  delay(1000); // เหมือนว่ามันจะทำงานที่ setup ทุกครั้งที่ได้ค่ามา มันอาจดีเลย์เพราะ NB setting ได้
  pingRESP pingR = AISnb.pingIP(serverIP);
  previousMillis = millis(); // เพื่อเริ่มนับเวลา

  wdt_enable(WDTO_2S);
}

void receiveEvent()
{
  while (1 < Wire.available()) // loop through all but the last
  {
    char c = Wire.read(); // receive byte as a character
    //Serial.print(all_notlast);         // print the character
    all_notlast += c;
  }
  char last = Wire.read();    // receive byte as an integer
  while(Wire.available() > 0){
    Wire.read();
  }
  //Serial.println(last);         // print the integer
  udpData += "," + all_notlast +  last;
  
  check_udp = true;

  all_notlast = "";
  last = NULL;
}

void loop()
{
  unsigned long currentMillis = millis();

  //if (strlen(udpData.c_str()) >= 102 ){
  if (currentMillis - previousMillis >= interval) {
    digitalWrite(pinresponse , LOW);
    previousMillis = currentMillis;
    UDPSend udp = AISnb.sendUDPmsgStr(serverIP, serverPort,udpData);
    udpData = "";
 
    check_udp = false;
    Serial.flush();
  }
  digitalWrite(pinresponse , HIGH);
  if ( check_udp == true ){
    Wire.begin(4);
    Wire.onReceive(receiveEvent);
  }
  wdt_reset();
}
