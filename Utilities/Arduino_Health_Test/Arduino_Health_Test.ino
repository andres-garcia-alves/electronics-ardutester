// -----------------------------------------------------------
// SKETCH DIAGNÓSTICO PARA NANO
// Prueba A: Entrada flotante en PB (D8–D13)
// Prueba B: Conmutación digital LOW/HIGH en PB
// Prueba C: ADC en vacío (A0-A1-A2)
// Autor: armado especialmente para validar ArduTester
// -----------------------------------------------------------
void printBanner(const char *msg) {
    Serial.println();
    Serial.println(F("================================"));
    Serial.println(msg);
    Serial.println(F("================================"));
}
// -----------------------------------------------------------
// PRUEBA A — PB como entradas, lectura flotante
// -----------------------------------------------------------
void testA() {
    printBanner("PRUEBA A - Entrada flotante PB0-PB5");
    DDRB = 0x00; // D8-D13 como entradas
    for (int i = 0; i < 6; i++) {
        Serial.print("PINB = ");
        Serial.println(PINB & 0x3F, BIN);
        delay(300);
    }
}
// -----------------------------------------------------------
// PRUEBA B — PB como salida, alternando LOW/HIGH
// -----------------------------------------------------------
void testB() {
    printBanner("PRUEBA B - Conmutación PB0-PB5");
    DDRB = 0x3F; // D8-D13 como salidas
    for (int i = 0; i < 6; i++) {
        PORTB = 0x00;
        Serial.print("LOW -> ");
        Serial.println(PINB & 0x3F, BIN);
        delay(300);
        PORTB = 0x3F;
        Serial.print("HIGH -> ");
        Serial.println(PINB & 0x3F, BIN);
        delay(300);
    }
}
// -----------------------------------------------------------
// PRUEBA C — ADC en vacío A0/A1/A2
// -----------------------------------------------------------
void testC() {
    printBanner("PRUEBA C - Lectura ADC A0/A1/A2");
    for (int i = 0; i < 20; i++) {
        Serial.print(analogRead(A0));
        Serial.print("\t");
        Serial.print(analogRead(A1));
        Serial.print("\t");
        Serial.println(analogRead(A2));
        delay(300);
    }
}
void setup() {
    Serial.begin(9600);
    delay(1000);
    Serial.println();
    Serial.println(F("=== TEST COMPLETO DE ARDUINO NANO ==="));
    Serial.println(F("Ejecutando las 3 pruebas en bucle..."));
    Serial.println();
}
void loop() {
    testA();
    delay(800);
    testB();
    delay(800);
    testC();
    delay(1500);
    printBanner("FIN CICLO - Repitiendo");
    delay(5000);
}
