#include <DHT.h>
#include "gogu.h"

DHT dht(DHTPIN, DHTTYPE, 11); // 11 works fine for ESP8266
float humidity, temp_f;  // Values read from sensor

boolean gogu_getDHT_data(S_DATA_STRUCT *climate)
{
  boolean lu8_returnValue = 1;
  dht.begin();
  delay(1000);
  
 // climate->humidity = dht.readHumidity();
  climate->temperature = dht.readTemperature() + TEMP_ERROR; // or dht.readTemperature(true) for Fahrenheit

	if (isnan(climate->temperature))
	{
		Serial.println("ERROR : DHT11 temperature!!");
    climate->temperature = 255;
    lu8_returnValue = 0;
	}
	else
	{
		Serial.print("DHT11 temperature : ");
		Serial.println(climate->temperature);
    
	}
	return lu8_returnValue;
}

void gogu_dayThermalManagement(S_DATA_STRUCT *s_Data)
{
   static byte lu8_counter = 0;
   if (s_Data->temperature < TEMP_DAY_LOW ) 
        {
            if(lu8_counter > TEMP_HISTER_LOW)
            {
              digitalWrite(TEMP_LIGHT_PIN, LOW);
              s_Data->lightStatus = HIGH;
//              gogu_statusLED.on();
              lu8_counter = 0;
            }
            else
            {
              lu8_counter = lu8_counter + 1;
            }
        }

        if (s_Data->temperature >= TEMP_DAY_HIGH) 
        {
            if(lu8_counter > TEMP_HISTER_HIGH)
            {
              digitalWrite(TEMP_LIGHT_PIN, HIGH);
              s_Data->lightStatus = LOW;
//                gogu_statusLED.off();
              lu8_counter = 0;
            }
            else
            {
              lu8_counter = lu8_counter + 1;
            }
        }
}

void gogu_nightThermalManagement(S_DATA_STRUCT *s_Data)
{
  static byte lu8_counter = 0;
  if (s_Data->temperature < TEMP_NIGHT_LOW )
        {
            if(lu8_counter > TEMP_HISTER_HIGH)
            {
              digitalWrite(TEMP_LIGHT_PIN, LOW);
              s_Data->lightStatus = HIGH;
//              gogu_statusLED.on();
              lu8_counter = 0;
            }
            else
            {
              lu8_counter = lu8_counter + 1;
            }
        }

        if (s_Data->temperature >= TEMP_NIGHT_HIGH)
        {
            if(lu8_counter > TEMP_HISTER_LOW)
            {
              digitalWrite(TEMP_LIGHT_PIN, HIGH);
              s_Data->lightStatus = LOW;
//              gogu_statusLED.off();
              lu8_counter = 0;
            }
            else
            {
               lu8_counter = lu8_counter + 1;
            }
       }
}
