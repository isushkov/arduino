/* === DRBUG ================= */

// Управление светодиодом с компьютера
int ledPin = 13;

void setup () {
    // Открываем порт на скорости 9600 бод
    Serial.begin(9600);
    // Назначаем пин светодиода выходом
    pinMode(ledPin, OUTPUT);
}
 
void loop () {
    // Ждем данные
    while (Serial.available() == 0);

    // Считываем данные
    int val = Serial.read() - '0';

    // Выполняем дествия в зависимости от данных
    if (val == 1) {
        Serial.println("Led is On");
        digitalWrite(ledPin, HIGH);
    } else if (val == 0) {
        Serial.println("Led is Off");
        digitalWrite(ledPin, LOW);
    } else {
        Serial.println("Invalid!");
    }
    // Очищаем буфер
    Serial.flush();
}
