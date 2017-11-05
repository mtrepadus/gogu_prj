#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "gogu.h"


const char* ssid     = "DIGI-8N2x";
const char* password = "salem2015";

byte gu8_PreviousGoodHour = 8;
byte gu8_NbOfErrors = 0;


void setup() {
  // put your setup code here, to run once:
  gogu_InitSerial();
  gogu_WifiConnect();
  gogu_setPinDirection(RED_LED, OUTPUT);
  gogu_setPinDirection(GREEN_LED, OUTPUT);
}

void loop()
{
  byte lu8_localHour = 0;
  S_DATA_STRUCT s_Data;

  if (  WiFi.status() == WL_CONNECTED)
  {
    Serial.print("\n Still Connected!\n");
  }
  else
  {
    gogu_WifiConnect();
  }

  lu8_localHour = gogu_ReturnCurentHour(&s_Data);


  Serial.print("Local Hour : ");
  if (lu8_localHour != 0)
  {
    gu8_NbOfErrors = 0;
    gu8_PreviousGoodHour = s_Data.hour;
    Serial.print(s_Data.hour);
    Serial.println(s_Data.minutes);
  }
  else
  {
    gu8_NbOfErrors++;
    if (gu8_NbOfErrors > 6)
    {
      gu8_PreviousGoodHour = 8;
      //ESP.restart();
    }
    Serial.print(" Error, no hour received; previous hour was: ");
    Serial.println(gu8_PreviousGoodHour);
  }

  if(gogu_getDHT_data(&s_Data))
  {
    gogu_blinkLed(GREEN_LED,s_Data.temperature );
  }
  else
  {
    gogu_blinkLed(RED_LED, 3 );
  }

  if((lu8_localHour >= 8) && (lu8_localHour >= 22))
  {

  }
  else
  {

  }

  //gogu_sendDataToBlynk(s_blynkData);
  // wait ten seconds before asking for the time again
  delay(20000);

}
