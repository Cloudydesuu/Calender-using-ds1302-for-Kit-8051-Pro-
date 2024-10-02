#include "ds1302.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char sec, min, hour, date, month, year;


// Convert BCD to BIN
unsigned char BCD2BIN(unsigned char bcd) {
    return ((bcd >> 4) * 10) + (bcd & 0x0F);
}
// Convert bin to BCD
unsigned char BIN2BCD(unsigned char bin) {
    return ((bin / 10) << 4) | (bin % 10);
}

void DS1302_Init(void) {
    RST = 0;
    SCLK = 0;
}

void DS1302_WriteByte(unsigned char addr, unsigned char dat) {
    unsigned char i;
    RST = 1;
    for (i = 0; i < 8; i++) {
        IO = addr & 0x01;
        SCLK = 1;
        SCLK = 0;
        addr >>= 1;
    }
    for (i = 0; i < 8; i++) {
        IO = dat & 0x01;
        SCLK = 1;
        SCLK = 0;
        dat >>= 1;
    }
    RST = 0;
}

unsigned char DS1302_ReadByte(unsigned char addr) {
    unsigned char i, dat = 0;
    RST = 1;
    addr |= 0x01;  // Set read bit
    for (i = 0; i < 8; i++) {
        IO = addr & 0x01;
        SCLK = 1;
        SCLK = 0;
        addr >>= 1;
    }
    for (i = 0; i < 8; i++) {
        dat >>= 1;
        if (IO) {
            dat |= 0x80;
        }
        SCLK = 1;
        SCLK = 0;
    }
    RST = 0;
    return dat;
}

void DS1302_SetTime(unsigned char sec, unsigned char min, unsigned char hour, unsigned char date, unsigned char month, unsigned char year) {
    DS1302_WriteByte(0x80, BIN2BCD(sec));
    DS1302_WriteByte(0x82, BIN2BCD(min));
    DS1302_WriteByte(0x84, BIN2BCD(hour));
    DS1302_WriteByte(0x86, BIN2BCD(date));
    DS1302_WriteByte(0x88, BIN2BCD(month));
    DS1302_WriteByte(0x8C, BIN2BCD(year));
}

void DS1302_GetTime(void) {
    sec = BCD2BIN(DS1302_ReadByte(0x81));
    min = BCD2BIN(DS1302_ReadByte(0x83));
    hour = BCD2BIN(DS1302_ReadByte(0x85));
    date = BCD2BIN(DS1302_ReadByte(0x87));
    month = BCD2BIN(DS1302_ReadByte(0x89));
    year = BCD2BIN(DS1302_ReadByte(0x8D));
}

