#include <Arduino.h>

const int BTN_PINS[] = {2, 3, 4, 5, 6};
const int NUM_BTNS   = 5;
const int GREEN_LED  = 8;
const int RED_LED    = 9;
const int BUZZER     = 10;

// Secret code: button numbers 1-5, in order
const int SECRET[]  = {3, 1, 5, 2, 4};
const int CODE_LEN  = 5;

int inputStep = 0;

void playSuccess() {
    tone(BUZZER, 784, 100); delay(120);
    tone(BUZZER, 988, 100); delay(120);
    tone(BUZZER, 1175, 100); delay(120);
    tone(BUZZER, 1568, 300); delay(300);
    noTone(BUZZER);
}

void playFail() {
    tone(BUZZER, 440, 200); delay(220);
    tone(BUZZER, 300, 400); delay(400);
    noTone(BUZZER);
}

void flashLED(int pin, int duration) {
    digitalWrite(pin, HIGH);
    delay(duration);
    digitalWrite(pin, LOW);
}

void setup() {
    for (int i = 0; i < NUM_BTNS; i++) {
        pinMode(BTN_PINS[i], INPUT_PULLUP);
    }
    pinMode(GREEN_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);
    pinMode(BUZZER, OUTPUT);
}

void loop() {
    for (int i = 0; i < NUM_BTNS; i++) {
        if (digitalRead(BTN_PINS[i]) == LOW) {
            delay(50); // debounce
            if (digitalRead(BTN_PINS[i]) != LOW) continue;

            int btnNum = i + 1;

            if (btnNum == SECRET[inputStep]) {
                inputStep++;
                if (inputStep == CODE_LEN) {
                    playSuccess();
                    flashLED(GREEN_LED, 2000);
                    inputStep = 0;
                }
            } else {
                playFail();
                flashLED(RED_LED, 1000);
                inputStep = 0;
            }

            while (digitalRead(BTN_PINS[i]) == LOW) delay(10);
        }
    }
}
