/* === LURK MORE ================================================== */
/* http://publicatorbar.ru/2017/12/21/arduino-multi-function-shield */

/* === BUTTONS ============= */
A1 (D15) - button 1
A2 (D16) - button 2
A3 (D17) - button 3
RESET    - ---
/* --- EXAMPLE --------- */
void loop() {
    if (!digitalRead(A1)) {
        // this your code...
    }
}
/* --- EXAMPLE --------- */
int button = A1;
int val;
void setup() {
    pinMode(button, INPUT);
}
void loop() {
    val = digitalRead(button);
    if (val == LOW) {
        // this your code...
    } else {
        // this your code...
    }
}
/* --- EXAMPLE --------- */
const byte LED = 10;
void setup() {
    pinMode(LED, OUTPUT);
}
void loop() {
    if (!digitalRead(A1)) {
        digitalWrite(LED, HIGH);
    }
    if (!digitalRead(A2)) {
        digitalWrite(LED, LOW);
    }
}
