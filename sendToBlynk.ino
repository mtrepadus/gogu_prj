/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).



void gogu_sendDataToBlynk(S_DATA_STRUCT data)
{

  static int counter = 0;
  /* STOP WIFI */
  WiFi.disconnect();
  delay(1000);

  /* START BLYNK */
  Blynk.begin(auth, ssid, password);
  Blynk.run();
 
  /* senda data */
  Blynk.virtualWrite(0,data.temperature);
  Blynk.virtualWrite(1,data.hour * 100 + data.minutes);
  Blynk.virtualWrite(2,counter);
  Blynk.virtualWrite(3,data.lightStatus);
  counter = counter +1;

  /* STOP WIFI */  
  Blynk.disconnect();
}

