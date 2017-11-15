#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "gogu.h"

const char* ssid     = "DIGI-8N2x";
const char* password = "salem2015";
char auth[] = "cc52b581c0254520a61b504bdf7c3709";

byte gu8_PreviousGoodHour = 8;
byte gu8_NbOfErrors = 0;
S_DATA_STRUCT s_Data;
//WidgetLED gogu_statusLED(V3);

void setup() {
	// put your setup code here, to run once:
	gogu_InitSerial();
	gogu_WifiConnect();

	gogu_initGogu(&s_Data);
	gogu_sendDataToBlynk(s_Data);

}

void loop()
{
	byte lu8_localHour = 0;


	if (  WiFi.status() == WL_CONNECTED)
	{
		Serial.print("\n Still Connected!\n");
	}
	else
	{
		gogu_WifiConnect();
	}

	s_Data.previousTime = s_Data.hour * 10000 + s_Data.minutes * 100 + s_Data.sec;


	if(gogu_ReturnCurentHour(&s_Data))
	{
		lu8_localHour = s_Data.hour;
		/* Reset s_Data.tempChanges at midnight */
		if ((s_Data.hour < 1 ) && (s_Data.minutes < 5))
		{
			s_Data.tempChanges = 0;
		}
	}
	else
	{
		lu8_localHour = 8;
		gogu_blinkLed(BLUE_LED, 3 );
	}

	if(gogu_getDHT_data(&s_Data))
	{
		gogu_blinkLed(GREEN_LED, 3 );
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
			gogu_dayThermalManagement(&s_Data);
		}
		else
		{
			gogu_nightThermalManagement(&s_Data);
		}
	}
	else
	{
		s_Data.tempError = s_Data.tempError + 1;
	}

	gogu_sendDataToBlynk(s_Data);

	// wait
	delay(75000);
}

void gogu_initGogu(S_DATA_STRUCT *s_data)
{
	gogu_setPinDirection(RED_LED,   OUTPUT);
	gogu_setPinDirection(GREEN_LED, OUTPUT);
	gogu_setPinDirection(TEMP_LIGHT_PIN, OUTPUT);

	// Light the heating lamp;
	digitalWrite(TEMP_LIGHT_PIN, LOW);

	//  gogu_statusLED.on();

	s_data->hour     = 0;
	s_data->minutes  = 0;
	s_data->sec      = 0;
	s_data->previousTime  = 0;
	s_data->temperature  = 0;
	s_data->humidity  = 0;
	s_data->lightStatus = 1;
	s_data->tempError = 0;
	s_data->tempChanges = 0;
}

