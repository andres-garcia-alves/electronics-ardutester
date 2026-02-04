#include "resistors.h"
#include "probes.h"
#include "adc.h"

#define R_LOW 680.0     // ohm
#define VCC   5.0

void dischargeAll() {
  pinMode(8, OUTPUT);  digitalWrite(8, LOW);
  pinMode(9, OUTPUT);  digitalWrite(9, LOW);
  pinMode(10, OUTPUT); digitalWrite(10, LOW);
  pinMode(11, OUTPUT); digitalWrite(11, LOW);
  pinMode(12, OUTPUT); digitalWrite(12, LOW);
  pinMode(13, OUTPUT); digitalWrite(13, LOW);
  delay(50);
  allHighZ();
}


long measureR(uint8_t tpSource, uint8_t tpSense) {

  dischargeAll();
  
  allHighZ();
  driveLow(tpSource);
  delay(50);

  int raw = stableRead(tpToADC(tpSense));
  float vSense = raw * (VCC / 1023.0);

  float i = vSense / R_LOW;
  if (i < 0.0000005) return -1;

  float vComp = VCC - vSense;
  long r = vComp / i;

  // compensate two 680R legs
  r = r - (2 * R_LOW);
  if (r < 0) r = 0;

  return r;
}
