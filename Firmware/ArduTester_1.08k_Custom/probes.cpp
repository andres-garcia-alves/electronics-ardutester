#include "probes.h"

// Convert TP number (1-2-3) to LOW-side pin
uint8_t tpToLowPin(uint8_t tp) {
  switch (tp) {
    case TP1: return 8;   // 680R
    case TP2: return 10;
    case TP3: return 12;
  }
  return 8;
}

// HIGH-side pin (470K) — unused in stage 1
uint8_t tpToHighPin(uint8_t tp) {
  switch (tp) {
    case TP1: return 9;   // 470K
    case TP2: return 11;
    case TP3: return 13;
  }
  return 9;
}

// Convert TP to correct ADC pin
uint8_t tpToADC(uint8_t tp) {
  switch (tp) {
    case TP1: return A2;
    case TP2: return A1;
    case TP3: return A0;
  }
  return A0;
}

// Put ALL 6 pins in high-Z
void allHighZ() {
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(12, INPUT);
  pinMode(13, INPUT);
}

// Drive a TP low through *its* 680R
void driveLow(uint8_t tp) {
  allHighZ();
  uint8_t pin = tpToLowPin(tp);
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
}
