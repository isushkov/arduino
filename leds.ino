/* === LURK MORE ================================================== */
/* http://publicatorbar.ru/2017/12/21/arduino-multi-function-shield */

/* === LEDS ================ */
D10 - led
D11 - led
D12 - led
D13 - base led
/* --- EXAMPLE --------- */
const byte LED = 10;
void setup() {
    pinMode(LED, OUTPUT);
}
void loop() {
    digitalWrite(LED, LOW);  // вкл
    delay(1000);
    digitalWrite(LED, HIGH); // выкл
    delay(1000);
}
