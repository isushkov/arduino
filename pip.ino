/* === LURK MORE ================================================== */
/* http://publicatorbar.ru/2017/12/21/arduino-multi-function-shield */

/* === PIP ================= */
D3 - pip
/* --- EXAMPLE --------- */
#define BUZZER 3 // подключаем зуммер к пину 3
void setup() {
    pinMode(BUZZER, OUTPUT); // зуммер 3 как выход
    digitalWrite(BUZZER, HIGH); // выключаем звук зуммера
}
void loop() {
    digitalWrite(BUZZER, LOW); //зуммер включен
    digitalWrite(BUZZER, HIGH); //зуммер выключен
}
/* --- EXAMPLE --------- */
#define ON LOW   // задаем включение зуммера
#define OFF HIGH // задаем выключение зуммера
#define BUZZER 3 // подключаем зуммер к пину 3
#define KEY1 A1  // подключаем кнопку к пину А1
void setup() {
    pinMode(KEY1, INPUT); // кнопка А1 как вход
    pinMode(BUZZER, OUTPUT); // зуммер 3 как выход
    digitalWrite(BUZZER, OFF); // выключаем звук зуммера
}
void loop() {
    //нажимаем кнопку KEY1
    if (digitalRead(KEY1) == ON) {
        digitalWrite(BUZZER, ON); //зуммер включен
    } else {
        digitalWrite(BUZZER, OFF); //зуммер выключен
    }
}
