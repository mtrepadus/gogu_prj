/*
 * gogu.h
 *
 *  Created on: Nov 4, 2017
 *      Author: trepa
 */

#ifndef GOGU_H_
#define GOGU_H_

#define RED_LED     15u
#define GREEN_LED   12u
#define BLUE_LED    13u 
#define DHTPIN      2u

#define TEMP_LIGHT_PIN  0u 

#define TEMP_ERROR      2u 
#define TEMP_DAY_LOW    26
#define TEMP_DAY_HIGH   30
#define TEMP_NIGHT_LOW  23
#define TEMP_NIGHT_HIGH 26

#define BLINK_PERIOD  300 //time in ms
#define TEMP_HISTER_LOW     5
#define TEMP_HISTER_HIGH    10

#define DHTTYPE DHT11

#define TEMP_LIGHT_PIN  0

extern char auth[];

typedef struct
{
  byte  hour;
  byte  minutes;
  byte  sec;
  int   previousTime;
  float temperature;
  float humidity;
  byte  lightStatus;
}S_DATA_STRUCT;

#endif /* GOGU_H_ */
