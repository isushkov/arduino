/* === LURK MORE ================================================== */
/* http://publicatorbar.ru/2017/12/21/arduino-multi-function-shield */

// === LED INDICATOR =======
D8 - SDI    | DATA_DIO  | линия передачи данных               
D7 - SFTCLK | CLK_DIO   | линия тактирования                  
D4 - LCHCLK | LATCH_DIO | линия синхронизации данных, защелка 

/* --- EXAMPLE --------- */
#define LATCH_DIO 4 // линия синхронизации данных, защелка (LCHCLK)
#define CLK_DIO 7   // линия тактирования (SFTCLK)
#define DATA_DIO 8  // линия передачи данных (SDI)
/* байты чисел от 0 до 9 */
const byte SEGMENT_MAP[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0X80, 0X90};
/* Байт-карты для выбора разряда дисплея от 1 до 4 */
const byte SEGMENT_SELECT[] = {0xF1, 0xF2, 0xF4, 0xF8};
 
void setup () {
    /* Установите выходы DIO как выходы */
    pinMode(LATCH_DIO, OUTPUT);
    pinMode(CLK_DIO, OUTPUT);
    pinMode(DATA_DIO, OUTPUT);
}
void loop() {
    /* Обновить дисплей с текущим значением счетчика */
    WriteNumberToSegment(0, 5);
    WriteNumberToSegment(1, 6);
    WriteNumberToSegment(2, 8);
    WriteNumberToSegment(3, 9);
}
/* отправляем десятичное число от 0 до 9 в один из четырех разрядов дисплея */
void WriteNumberToSegment(byte Segment, byte Value)
{
    digitalWrite(LATCH_DIO, LOW);
    shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_MAP[Value]);
    shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_SELECT[Segment]);
    // shiftOut(DATA_PIN, CLK_DIO, bitOrder, value)
    // params
        // DATA_DIO: номер порта вход/выхода, на который выводятся биты (int)
        // CLK_DIO: номер порта по которому производится синхронизация (int)
        // bitOrder: используемая последовательность вывода бит.
            // MSBFIRST — слева
            // LSBFIRST — справа
        // value: значение (байт) для вывода (byte)
    digitalWrite(LATCH_DIO, HIGH);
}




#define LATCH_DIO 4 // линия синхронизации данных, защелка (LCHCLK)
#define CLK_DIO 7   // линия тактирования (SFTCLK)
#define DATA_DIO 8  // линия передачи данных (SDI)
const byte SEGMENT_MAP[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0X80, 0X90};
const byte SEGMENT_SELECT[] = {0xF1, 0xF2, 0xF4, 0xF8};
 
void setup () {
    pinMode(LATCH_DIO, OUTPUT);
    pinMode(CLK_DIO, OUTPUT);
    pinMode(DATA_DIO, OUTPUT);
}
void loop() {
    WriteNumberToSegment(0, 5);
    WriteNumberToSegment(1, 6);
    WriteNumberToSegment(2, 8);
    WriteNumberToSegment(3, 9);
}
void WriteNumberToSegment(byte Segment, byte Value)
{
    digitalWrite(LATCH_DIO, LOW);
    shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_MAP[Value]);
    shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_SELECT[Segment]);
    digitalWrite(LATCH_DIO, HIGH);
    delay(10);
}
