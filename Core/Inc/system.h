#ifndef SYSTEM_H
#define SYSTEM_H

#include "main.h"
#include "system.h"
#include "def.h"
#include "crc.h"
#include "LoRa.h"
#include "spi.h"
#include "stdio.h"
#include "usart.h"

extern Gps gps;

void ParseArtamLoRaData();
void initLoRa();
void initLoRaT();
void loraArtamRecevice();
void loraAkuRecevice();
void artamErrorLed();
void akuErrorLed();

#endif // SYSTEM_H
