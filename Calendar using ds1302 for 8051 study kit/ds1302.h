#ifndef DS1302_H
#define DS1302_H

#include <reg51.h>

// Pin definitions
sbit RST= P3^5; // Reset pin for DS1302
sbit IO = P3^4; // Data line for DS1302
sbit SCLK = P3^6; // Clock line for DS1302

// Function
void DS1302_Init(void);
void DS1302_WriteByte(unsigned char addr, unsigned char dat);
unsigned char DS1302_ReadByte(unsigned char addr);
void DS1302_SetTime(unsigned char sec, unsigned char min, unsigned char hour, unsigned char date, unsigned char month, unsigned char year);
void DS1302_GetTime(void);

// Global variables to store time and date
extern unsigned char sec, min, hour, date, month, year;

#endif