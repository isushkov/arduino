#include <MFShield.h>
// special effects
#define ENABLE_TICK_SOUND    true
#define ENABLE_BUTTON_SOUND  true
#define DISPLAY_LEADING_ZERO false
// timer configuration settings
#define DEFAULT_INTERVAL 30
#define TIMER_STEP       5
#define TIMER_VALUE_MIN  5
#define TIMER_VALUE_MAX  6000
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
uint32_t counter = DEFAULT_INTERVAL;
// a variable for non blocking loop, using millis()
uint32_t t;

/* =================================================== */
void setup() {
    mfs.display(counter, DISPLAY_LEADING_ZERO);
    mfs.onKeyPress(keyAction);
}
void loop() {
    mfs.loop();
    // we're in setup mode
    if (!countdown) {
        // blink numeric display
        mfs.showDisplay(millis()/30 %4);
        return;
    }
    // else run this code once every 100 msec (0.1 sec.)
    if (millis() - t >= 100) {
        t = millis();

        // while counter is not 0, decrement it
        if (counter > 0) {

			// counter
			int miliSec = counter % 10;
			int seconds = (counter % 1000)/10;
			int minutes = (counter % 10000)/1000;
			// check seconds
			if (seconds > 59) {
				seconds = 59;
				counter = (minutes * 1000) + (seconds * 10) + miliSec;
			// decrement counter value
			} else {
				counter--;
			}

			// led && beep
			if (counter < 250 && counter >= 200 && miliSec == 0 && ENABLE_TICK_SOUND) {
				mfs.beep(10);
			}
			boolean  blink = mfs.getLed(1);
			if (counter < 200 && counter >= 100) {
				if (counter > 150 && miliSec == 0) {
					mfs.setLed(1, !blink);
				} else if (counter < 150) {
					mfs.setLed(1, !blink);
				}

				if (ENABLE_TICK_SOUND && miliSec == 0) {
					mfs.beep(10);
				}
			}
			if (counter < 100 && counter >= 50) {
				mfs.setLed(1, !blink);
				mfs.setLed(2, blink);
				if (ENABLE_TICK_SOUND && miliSec == 0) {
					mfs.beep(50);
				}
			}
			if (counter < 50 && counter >= 30) {
				mfs.setLed(1, !blink);
				mfs.setLed(2, blink);
				mfs.setLed(3, !blink);
				if (ENABLE_TICK_SOUND) {
					mfs.beep(50);
				}
			}
			if (counter < 30) {
				mfs.setLed(1, !blink);
				mfs.setLed(2, blink);
				mfs.setLed(3, blink);
				mfs.setLed(4, !blink);
				if (ENABLE_TICK_SOUND) {
					mfs.beep();
				}
			}
        // once counter become zero, trigger the alarm
        } else {
            alarm(ALARM_PERIOD_MS, ALARM_TIMEOUT_MS);
        }
        // update numeric value on lcd
        mfs.display(counter, DISPLAY_LEADING_ZERO);
    }
}

void keyAction (uint8_t key) {
	// do nothing if the countdown has begin
    if (countdown) {
        return;
    }
	int seconds = counter % 100;
	int minutes = (counter % 1000)/100;

    switch (key) {
        case BUTTON_PLUS:
			// fix counter
			if (seconds == 55) {
				minutes++;
				seconds = 0;
				counter = (minutes * 100) + seconds;
			// decrement counter value
			} else {
				counter += TIMER_STEP;
			}
			
            break;
        case BUTTON_MINUS:
			// fix counter
			if (seconds == 0) {
				minutes--;
				seconds = 55;
				counter = (minutes * 100) + seconds;
			// increment counter value
			} else {
				counter -= TIMER_STEP;
			}
            break;
        case BUTTON_START:
            countdown = true;
			counter *= 10;
            t = millis();
            break;
    }
    // limit counter range between these values (see definitions)
    counter = constrain (counter, TIMER_VALUE_MIN, TIMER_VALUE_MAX);
    if (ENABLE_BUTTON_SOUND) {
        // make button sound if enabled
        mfs.beep(5); 
    }
    // update counter value on display
    mfs.display(counter, DISPLAY_LEADING_ZERO);
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
            mfs.setLed(2, !blink);
            mfs.setLed(3, !blink);
            mfs.setLed(4, !blink);
            // blink display
            mfs.showDisplay(!blink);
            mfs.beep(period_ms / 2);
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
