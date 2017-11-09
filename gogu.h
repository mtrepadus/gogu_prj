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
#define TEMP_DAY_LOW    28
#define TEMP_DAY_HIGH   31
#define TEMP_NIGHT_LOW  23
#define TEMP_NIGHT_HIGH 27

#define BLINK_PERIOD  300 //time in ms
#define TEMP_HISTER   5

#define DHTTYPE DHT11

#define TEMP_LIGHT_PIN  0

extern char auth[];

typedef struct
{
  byte  hour;
  byte  minutes;
  float temperature;
  float humidity;
  byte  lightStatus;
}S_DATA_STRUCT;

#endif /* GOGU_H_ */
