#include "display.h"

void showResistance(long r, uint8_t a, uint8_t b) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0,0);

  if (r < 0 || r > 2000000) {
    display.println("NO COMPONENT");
  } else {
    display.print("R ");
    display.print(a);
    display.print("-");
    display.print(b);
    display.println(":");
    display.print(r);
    display.println(" ohm");
  }
  display.display();
}
