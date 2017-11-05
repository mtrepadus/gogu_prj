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
  climate->temperature = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

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
