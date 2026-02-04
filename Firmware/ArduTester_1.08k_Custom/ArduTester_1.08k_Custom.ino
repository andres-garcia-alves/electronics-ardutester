#include <Wire.h>
#include "probes.h"
#include "resistors.h"
#include "display.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH    128
#define SCREEN_HEIGHT   64
#define SCREEN_ADDRESS  0x3C   // Dirección I2C (0x3C/0x3D)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


void setup() {
  Serial.begin(9600);

  // inicializar el display
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("Error al inicializar SSD1306"));
    for(;;); // Detener si hay error
  }

  // limpiar buffer
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE); // Color blanco

  // bienvenida
  display.setCursor(0,0);
  display.println("R-TEST");
  display.display();
  
  delay(1000);
}

void loop() {

  long r12 = measureR(TP1, TP2);
  long r23 = measureR(TP2, TP3);
  long r13 = measureR(TP1, TP3);

  long best = -1;
  uint8_t A=0, B=0;

  long v[3] = {r12, r23, r13};
  uint8_t ta[3] = {1, 2, 1};
  uint8_t tb[3] = {2, 3, 3};

  for(int i=0; i<3; i++){
    if(v[i] > 0 && (best < 0 || v[i] < best)){
      best = v[i];
      A = ta[i];
      B = tb[i];
    }
  }

  showResistance(best, A, B);
  delay(300);
}
