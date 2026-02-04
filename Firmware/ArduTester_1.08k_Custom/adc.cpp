#include "adc.h"

int stableRead(int adcPin) {
  delay(2);
  analogRead(adcPin);         // dummy
  return analogRead(adcPin);  // real
}
