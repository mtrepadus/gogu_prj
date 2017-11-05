#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "gogu.h"

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "cc52b581c0254520a61b504bdf7c3709";

//void gogu_sendDataToBlynk(S_BLYBK_STRUCT s_blynkData)
//{
//  static byte i = 0;
//  Blynk.run();
//  delay(300);
//  Blynk.virtualWrite(V0, i);
//  i = i +1;
//  delay(1000);
//  Blynk.virtualWrite(V1, i);
//  delay(1000);
//
//}



