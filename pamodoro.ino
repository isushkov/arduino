#include <MFShield.h>
// special effects
#define ENABLE_TICK_SOUND    true
#define ENABLE_BUTTON_SOUND  true
#define DISPLAY_LEADING_ZERO false
// timer configuration settings
#define DEFAULT_INTERVAL 2500
#define TIMER_STEP       5
#define TIMER_VALUE_MIN  5
#define TIMER_VALUE_MAX  9999
// alarm settings
#define ALARM_PERIOD_MS  500
#define ALARM_TIMEOUT_MS 10000
// button assignment settings
#define BUTTON_PLUS  3
#define BUTTON_START 2
#define BUTTON_MINUS 1

MFShield mfs;
// countdown flag variable
boolean countdown = false;
// countdown value
uint16_t counter = DEFAULT_INTERVAL;
// a variable for non blocking loop, using millis()
uint32_t t;

/* =================================================== */
void setup() {
    mfs.display(counter, DISPLAY_LEADING_ZERO);
    // assign handler function for buttons
    mfs.onKeyPress(keyAction);
}
void loop() {
    mfs.loop();
    // we're in setup mode
    if (!countdown) {
        // blink numeric display rapidly
        // mfs.showDisplay(millis()/30 %2);
        mfs.showDisplay(millis()/30 %4);
        return;
    }
    // else run this code once every 1000 msec (1 sec.)
    if (millis() - t >= 1000) {
        t = millis();
        // while counter is not 0, decrement it
        if (counter > 0) {
            // decrement counter value
            counter--;
            // blink onboard led
            mfs.setLed (1, !mfs.getLed(1));

            if (ENABLE_TICK_SOUND) {
                // make tick sound if enabled
                // mfs.beep (1);
            }
        // once counter become zero, trigger the alarm
        } else {
            alarm(ALARM_PERIOD_MS, ALARM_TIMEOUT_MS);
        }
        // update numeric value on lcd
        mfs.display(counter, DISPLAY_LEADING_ZERO);
    }
}

void alarm(const uint32_t period_ms, const uint32_t timeout_ms) {
    // make a counter variable for non blocking loop
    uint32_t t_alarm = 0;
    // set alarm timeout
    uint32_t alarm_timeout = millis() + timeout_ms;
    while (true) {
        boolean blink = mfs.getLed(1);
        if (millis() - t_alarm >= period_ms) { 
            // non blocking loop: run this code once every <period_ms>
            t_alarm = millis();
            // blink led
            mfs.setLed(1, !blink);
            // blink display
            mfs.showDisplay(!blink);
            // mfs.beep (period_ms / 2);
        }
        // stop alarm after timeout and return into setup mode
        if (millis() > alarm_timeout) {
            counter = DEFAULT_INTERVAL;
            countdown = false;
            return;
        }
        mfs.loop();
    }
}
void keyAction (uint8_t key) {
    if (countdown) {
        // do nothing if the countdown has begun
        return;
    }
    switch (key) {
        case BUTTON_PLUS:
            counter += TIMER_STEP;
            break;
        case BUTTON_MINUS:
            counter -= TIMER_STEP;
            break;
        case BUTTON_START:
            countdown = true;
            t = millis();
            break;
    }
    // limit counter range between these values (see definitions)
    counter = constrain (counter, TIMER_VALUE_MIN, TIMER_VALUE_MAX);
    if (ENABLE_BUTTON_SOUND) {
        // make button sound if enabled
        // mfs.beep(5); 
    }
    // update counter value on display
    mfs.display(counter, DISPLAY_LEADING_ZERO);
}
