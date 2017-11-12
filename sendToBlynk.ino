/* Comment this out to disable prints and save space */
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
  Blynk.virtualWrite(1,data.hour * 10000 + data.minutes  * 100 + data.sec);
  Blynk.virtualWrite(2,counter);
  Blynk.virtualWrite(3,data.lightStatus);
  Blynk.virtualWrite(4,data.previousTime);
  counter = counter +1;
  

  /* STOP WIFI */  
  Blynk.disconnect();
}

