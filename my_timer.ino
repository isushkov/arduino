#define LATCH_DIO 4 // линия синхронизации данных, защелка (LCHCLK)
#define CLK_DIO 7   // линия тактирования (SFTCLK)
#define DATA_DIO 8  // линия передачи данных (SDI)
const byte SEGMENT_MAP[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0X80, 0X90};
const byte SEGMENT_SELECT[] = {0xF1, 0xF2, 0xF4, 0xF8};
 
int minutes = 1;
int dSecond = 7;
int seconds = 3;
int miliSec = 5;

void setup () {
    pinMode(LATCH_DIO, OUTPUT);
    pinMode(CLK_DIO, OUTPUT);
    pinMode(DATA_DIO, OUTPUT);
    if ((dSecond == 6 && seconds != 0) || dSecond > 6) {
        dSecond = 5;
        seconds = 9;
    }
}
void loop() {
    /* WriteNumberToSegment(0, minutes); */
    /* WriteNumberToSegment(1, dSecond); */
    /* WriteNumberToSegment(2, seconds); */
    /* WriteNumberToSegment(3, miliSec); */
    
    WriteNumber0(minutes);
    WriteNumber1(dSecond);
    WriteNumber2(seconds);
    WriteNumber3(miliSec);

    if (miliSec != 0) {
        miliSec--;
    } else {
        miliSec = 9;
        if (seconds != 0) {
            seconds--;
        } else {
            seconds = 9;
            if (dSecond != 0) {
                dSecond--;
            } else {
                dSecond = 6;

                if (minutes != 0) {
                    minutes--;
                }
            }
        }
    }
    delay(100);
}

/* void WriteNumberToSegment(byte Segment, byte value) */
/* { */
/*     digitalWrite(LATCH_DIO, LOW); */
/*         shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_MAP[value]); */
/*         shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_SELECT[Segment]); */
/*     digitalWrite(LATCH_DIO, HIGH); */
/* } */

void WriteNumber0(byte value)
{
    digitalWrite(LATCH_DIO, LOW);
        shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_MAP[value]);
        shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_SELECT[0]);
    digitalWrite(LATCH_DIO, HIGH);
}
void WriteNumber1(byte value)
{
    digitalWrite(LATCH_DIO, LOW);
        shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_MAP[value]);
        shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_SELECT[1]);
    digitalWrite(LATCH_DIO, HIGH);
}
void WriteNumber2(byte value)
{
    digitalWrite(LATCH_DIO, LOW);
        shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_MAP[value]);
        shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_SELECT[2]);
    digitalWrite(LATCH_DIO, HIGH);
}
void WriteNumber3(byte value)
{
    digitalWrite(LATCH_DIO, LOW);
        shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_MAP[value]);
        shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_SELECT[3]);
    digitalWrite(LATCH_DIO, HIGH);

}
