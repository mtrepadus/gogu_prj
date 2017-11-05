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

#define BLINK_PERIOD  300 //time in ms

#define DHTTYPE DHT11
#define DHTPIN  2

extern char auth[];

typedef struct
{
  byte  hour;
  byte  minutes;
  float temperature;
  float humidity;
}S_DATA_STRUCT;

#endif /* GOGU_H_ */
