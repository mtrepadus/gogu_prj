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
  static byte lu8_noChange = 0;

	if (s_Data->temperature <= TEMP_DAY_LOW )
	{
		/* temperature lower than normal, must start the heater */
		if(lu8_counter > TEMP_HISTER_LOW)
		{
			  /* start the heater only if a certain time passed */
        if(digitalRead(TEMP_LIGHT_PIN) == HIGH)
        {
  				/* set the pin LOW in order to activate the relay */
  				digitalWrite(TEMP_LIGHT_PIN, LOW);
  				s_Data->lightStatus = 1;
  				s_Data->tempChanges =  s_Data->tempChanges + 1;
  				lu8_counter = 0;
          lu8_noChange = 0;
        }
		}
		else
		{
			lu8_counter = lu8_counter + 1;
		}
	}

	if (s_Data->temperature >= TEMP_DAY_HIGH)
	{
		/* temperature higher than normal, must stop the heater */
		if(lu8_counter > TEMP_HISTER_HIGH)
		{
			  /* stop the heater only if a certain time passed */
				if(digitalRead(TEMP_LIGHT_PIN) == LOW)
        {
  				/* set the pin HIGH in order to deactivate the relay */
  				digitalWrite(TEMP_LIGHT_PIN, HIGH);
  				s_Data->lightStatus = 0;
  				s_Data->tempChanges =  s_Data->tempChanges + 1;
  				lu8_counter = 0;
          lu8_noChange = 0;
        }
		}
		else
		{
			lu8_counter = lu8_counter + 1;
		}
	}

 lu8_noChange++;
 if (lu8_noChange > 100)
 {
      /* start the heater only if a certain time passed */
        /* set the pin LOW in order to activate the relay */
        digitalWrite(TEMP_LIGHT_PIN, LOW);
        s_Data->lightStatus = 1;
        s_Data->tempChanges =  s_Data->tempChanges + 1;
        lu8_counter = 0;
        lu8_noChange = 0;
        
 }
}

void gogu_nightThermalManagement(S_DATA_STRUCT *s_Data)
{
	static byte lu8_counter = 0;
	if (s_Data->temperature <= TEMP_NIGHT_LOW )
	{
		/* temperature lower than normal, must start the heater */
		if(lu8_counter > TEMP_HISTER_HIGH)
		{
			  /* start the heater only if a certain time passed */
        if(digitalRead(TEMP_LIGHT_PIN) == HIGH)
        {
  				/* set the pin LOW in order to activate the relay */
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
		/* temperature higher than normal, must stop the heater */
		if(lu8_counter > TEMP_HISTER_LOW)
		{
			  /* stop the heater only if a certain time passed */
       if(digitalRead(TEMP_LIGHT_PIN) == HIGH)
        {
  				/* set the pin HIGH in order to deactivate the relay */
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
