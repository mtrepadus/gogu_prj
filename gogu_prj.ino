#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "gogu.h"


const char* ssid     = "DIGI-8N2x";
const char* password = "salem2015";
char auth[] = "cc52b581c0254520a61b504bdf7c3709";

byte gu8_PreviousGoodHour = 8;
byte gu8_NbOfErrors = 0;


void setup() {
  // put your setup code here, to run once:
  gogu_InitSerial();
  gogu_WifiConnect();
  gogu_setPinDirection(RED_LED,   OUTPUT);
  gogu_setPinDirection(GREEN_LED, OUTPUT);
  gogu_setPinDirection(TEMP_LIGHT_PIN, OUTPUT);
  //digitalWrite(TEMP_LIGHT_PIN, HIGH);
  digitalWrite(TEMP_LIGHT_PIN, LOW);
  
}

void loop()
{
  byte lu8_localHour = 0;
  S_DATA_STRUCT s_Data;
  static byte lu8_counter = 0;

  if (  WiFi.status() == WL_CONNECTED)
  {
    Serial.print("\n Still Connected!\n");
  }
  else
  {
    gogu_WifiConnect();
  }


  if(gogu_ReturnCurentHour(&s_Data))
  {
    lu8_localHour = s_Data.hour;
  }
  else
  {
    lu8_localHour = 8;
    gogu_blinkLed(BLUE_LED, 3 );
  }

  if(gogu_getDHT_data(&s_Data))
  {
    gogu_blinkLed(GREEN_LED,s_Data.temperature );
  }
  else
  {
    gogu_blinkLed(RED_LED, 3 );
  }

  /* Verify that the read temperature is OK */
  if(s_Data.temperature != 255)
  {
    if((lu8_localHour >= 8) && (lu8_localHour < 22))
    {
        if (s_Data.temperature < TEMP_DAY_LOW ) 
        {
            if(lu8_counter > TEMP_HISTER)
            {
              //digitalWrite(TEMP_LIGHT_PIN, HIGH);
              digitalWrite(TEMP_LIGHT_PIN, LOW);
              s_Data.lightStatus = HIGH;
              lu8_counter = 0;
            }
            else
            {
              lu8_counter = lu8_counter + 1;
            }
        }

        if (s_Data.temperature > TEMP_DAY_HIGH) 
        {
            if(lu8_counter > TEMP_HISTER)
            {
              //digitalWrite(TEMP_LIGHT_PIN, LOW);
              digitalWrite(TEMP_LIGHT_PIN, HIGH);
              s_Data.lightStatus = LOW;
              lu8_counter = 0;
            }
            else
            {
              lu8_counter = lu8_counter + 1;
            }
        }
    }
    else
    {
        if (s_Data.temperature < TEMP_NIGHT_LOW )
        {
            if(lu8_counter > TEMP_HISTER)
            {
              //digitalWrite(TEMP_LIGHT_PIN, HIGH);
              digitalWrite(TEMP_LIGHT_PIN, LOW);
              s_Data.lightStatus = HIGH;
              lu8_counter = 0;
            }
            else
            {
              lu8_counter = lu8_counter + 1;
            }
        }

        if (s_Data.temperature > TEMP_NIGHT_HIGH)
        {
            if(lu8_counter > TEMP_HISTER)
            {
              //digitalWrite(TEMP_LIGHT_PIN, LOW);
              digitalWrite(TEMP_LIGHT_PIN, HIGH);
              s_Data.lightStatus = LOW;
              lu8_counter = 0;
            }
            else
            {
               lu8_counter = lu8_counter + 1;
            }
       }
    }
  }
  else
  {
      digitalWrite(TEMP_LIGHT_PIN, HIGH);
      s_Data.lightStatus = LOW;
  }

  gogu_sendDataToBlynk(s_Data);

  // wait ten seconds before asking for the time again
  delay(20000);
}
