## 🧪 Prueba A - Lectura de PINB (Entrada flotante)

📌 Objetivo

Verificar que los pines digitales D8–D13 (PB0–PB5) funcionen como entradas de alta impedancia cuando no hay nada conectado.

Sirve para detectar:
- Pull-ups internos activados permanentemente
- Puentes internos entre pines
- Fuga hacia GND o VCC
- PUERTO B dañado

🧠 Comportamiento esperado

En un Arduino sano:
- Los bits cambian continuamente
- No hay patrón fijo
- Algunos HIGH, otros LOW
- Excepción: pueden dat todos LOW según el Arduino (0)

En un Arduino dañado:
- Todo HIGH (111111)
- Patrón fijo que nunca cambia

🧾 Código:
<pre>
void setup() {
    Serial.begin(9600);
    DDRB = 0x00; // PB0–PB5 como entradas
}

void loop() {
    Serial.println(PINB & 0x3F, BIN);   // Lee solo PB0–PB5 delay(300);
}
</pre>

&nbsp;

## 🔁 Prueba B — PORTB salida → entrada (Test de conmutación digital)

📌 Objetivo:

Confirmar que los pines D8–D13 pueden:
- Conducir correctamente LOW y HIGH.
- Reflejar ese estado al leer PINB.

Detecta:
- Transistores MOSFET de salida quemados
- Pines pegados HIGH o LOW
- Puentes internos
- Fallo parcial de lógica digital

🧠 Comportamiento esperado

En un Arduino sano:
000000  
111111  
000000  
111111  
...

En un Arduino dañado:
- No cambia entre 0 y 1
- Bits faltantes (101011)
- Siempre HIGH o siempre LOW

🧾 Código
<pre>
void setup() {
    Serial.begin(9600);
    DDRB = 0x3F; // PB0–PB5 como salidas
}

void loop() {
    PORTB = 0x00;
    Serial.println(PINB & 0x3F, BIN);
    delay(300);
    PORTB = 0x3F;
    Serial.println(PINB & 0x3F, BIN);
    delay(300);
}
</pre>

&nbsp;

## 🎯 Prueba C — ADC A0/A1/A2 en vacío (Diagnóstico Analógico)

📌 Objetivo

Validar el sistema analógico completo:
- Multiplexor ADC (MUX)
- Capacitor Sample & Hold
- Comparador interno
- Referencia y acople entre canales

Detecta:
- ADC quemado por sobrevoltaje
- Fuga interna al VCC/GND
- MUX corrompido
- Diodos de protección dañados

🧠 Comportamiento esperado

En un Arduino sano:
- Números aleatorios
- Diferentes entre sí
- Rango típico: 50–600
- Cambian frame a frame

Ejemplo válido:
80   140  210
300   70  400
55   350  120

En un Arduino dañado:
- valores pegados a ~1023 → fuga a VCC
- valores pegados a ~0 → fuga a GND
- los tres iguales → crosstalk permanente

🧾 Código
<pre>
void setup() {
    Serial.begin(9600);
}

void loop() {
    Serial.print(analogRead(A0));
    Serial.print("\t");
    Serial.print(analogRead(A1));
    Serial.print("\t");
    Serial.println(analogRead(A2));
    delay(300);
}
</pre>

&nbsp;

## 🏁 Cómo usar los tres tests

1️⃣ Cargar Prueba A
✔ caos de bits → OK
✘ patrón fijo → no sirve para ArduTester

2️⃣ Si pasó, cargar Prueba B
✔ 0 ↔ 1 alterna completo → OK
✘ bits clavados → puerto digital dañado

3️⃣ Si pasó, cargar Prueba C
✔ ruido analógico variable → Nano apto
✘ todos iguales / 0 / 1023 → ADC dañado

&nbsp;

## 🏆 Conclusión

Si un Nano pasa los tres diagnósticos, está 100% apto para:
- ArduTester
- Medición analógica seria
- Proyectos con sensores
- Cualquier diseño donde se necesite precisión
- Si falla solo C, pero pasa A/B → podés usarlo para proyectos digitales solamente.

&nbsp;

## 🚀 Secuencia Automática

<pre>
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

</pre>
