#include <DHT.h>
#include "gogu.h"

DHT dht(DHTPIN, DHTTYPE, 11); // 11 works fine for ESP8266
float humidity, temp_f;  // Values read from sensor

boolean gogu_getDHT_data(S_DATA_STRUCT *climate)
{
	boolean lu8_returnValue = 1;
	static byte tub_retry = 0;
	dht.begin();
	delay(500);

	// climate->humidity = dht.readHumidity();
	climate->temperature = dht.readTemperature() + TEMP_ERROR; // or dht.readTemperature(true) for Fahrenheit

	if (isnan(climate->temperature))
	{
		Serial.println("ERROR : DHT11 temperature! Read again!");
		delay(500);
		dht.begin();
		delay(500);

		// climate->humidity = dht.readHumidity();
		climate->temperature = dht.readTemperature() + TEMP_ERROR; // or dht.readTemperature(true) for Fahrenheit
		if (isnan(climate->temperature))
		{
			Serial.println("ERROR : DHT11 temperature!!");
			climate->temperature = 255;
			lu8_returnValue = 0;
			tub_retry = 0;
		}
	}

	return lu8_returnValue;
}

void gogu_dayThermalManagement(S_DATA_STRUCT *s_Data)
{
	static byte lu8_counter = 0;
	if (s_Data->temperature <= TEMP_DAY_LOW )
	{
		if(lu8_counter > TEMP_HISTER_LOW)
		{
			if(digitalRead(TEMP_LIGHT_PIN) == HIGH)
			{
				digitalWrite(TEMP_LIGHT_PIN, LOW);
				s_Data->lightStatus = 1;
				s_Data->tempChanges =  s_Data->tempChanges + 1;
				lu8_counter = 0;
			}
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
			if(digitalRead(TEMP_LIGHT_PIN) == LOW)
			{
				digitalWrite(TEMP_LIGHT_PIN, HIGH);
				s_Data->lightStatus = 0;
				s_Data->tempChanges =  s_Data->tempChanges + 1;
				lu8_counter = 0;
			}
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
	if (s_Data->temperature <= TEMP_NIGHT_LOW )
	{
		if(lu8_counter > TEMP_HISTER_HIGH)
		{
			if(digitalRead(TEMP_LIGHT_PIN) == HIGH)
			{
				digitalWrite(TEMP_LIGHT_PIN, LOW);
				s_Data->tempChanges =  s_Data->tempChanges + 1;
				s_Data->lightStatus = 1;
				lu8_counter = 0;
			}
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
			if(digitalRead(TEMP_LIGHT_PIN) == LOW)
			{
				digitalWrite(TEMP_LIGHT_PIN, HIGH);
				s_Data->lightStatus = 0;
				s_Data->tempChanges =  s_Data->tempChanges + 1;
				lu8_counter = 0;
			}
		}
		else
		{
			lu8_counter = lu8_counter + 1;
		}
	}
}
