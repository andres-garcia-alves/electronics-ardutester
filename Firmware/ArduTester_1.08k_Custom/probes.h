#pragma once
#include <Arduino.h>

#define TP1 1
#define TP2 2
#define TP3 3

void allHighZ();
void driveLow(uint8_t tp);
uint8_t tpToLowPin(uint8_t tp);
uint8_t tpToHighPin(uint8_t tp);
uint8_t tpToADC(uint8_t tp);
