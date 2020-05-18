#define __DELAY_BACKWARD_COMPATIBLE__
#include <avr/io.h>
#include <util/delay.h>

// ge-enabled leds staan ook aan
void enableLed(int led) {  // 0..3
  if (led < 0 || led > 3) return;
  DDRB |= (1 << (PB2 + led));
}

void enableAllLeds() {
  for (int i = 0; i < 4; i++) {
    enableLed(i);
  }
}

void enableLeds(uint8_t leds) {
  leds &= 0B00001111;
  PORTB |= ~(leds << PB2);
}

void lightUpLed(int led) {
  if (led < 0 || led > 3) return;
  PORTB &= ~(1 << (PB2 + led));
}

void lightUpLeds(uint8_t leds) {
  leds &= 0B00001111;
  PORTB &= ~(leds << PB2);
}

void lightUpAllLeds() {
  for (int i = 0; i < 4; i++) {
    lightUpLed(i);
  }
}

void lightDownLed(int led) {
  if (led < 0 || led > 3) return;
  PORTB |= (1 << (PB2 + led));  // op 1 = UIT
}

void lightDownLeds(uint8_t leds) {
  leds &= 0B00001111;
  PORTB |= (leds << PB2);
}

void lightDownAllLeds() {
  for (int i = 3; i >= 0; i--) {
    lightDownLed(i);
  }
}

void flipLed(int led) {
  if (bit_is_set(PORTB, PB2 + led)) {
    lightUpLed(led);
  } else {
    lightDownLed(led);
  }
}

void flashLed(int led, int duration) {
  lightUpLed(led);
  _delay_ms(duration);
  lightDownLed(led);
  _delay_ms(duration);
}

void dimLed(int led, int percentage, int duration) {
  for (int i = 0; i < duration; i++) {
    lightUpLed(led);
    _delay_ms(percentage / 10);
    lightDownLed(led);
    _delay_ms(10 - (percentage / 10));
  }
}

void fadeInLed(int led, int duration) {
  for (int i = 0; i < 10; i++) {
    dimLed(led, i * 10, duration / 10);
  }
}

void fadeInLeds(uint8_t leds, int duration) {
  for (int i = 0; i < 10; i++) {
    dimLed(leds, i * 10, duration / 10);
  }
}

void fadeOutLed(int led, int duration) {
  for (int i = 9; i > 0; i--) {
    dimLed(led, i * 10, duration / 10);
  }
}

void fadeOutLeds(uint8_t leds, int duration) {
  for (int i = 9; i > 0; i--) {
    dimLed(leds, i * 10, duration / 10);
  }
}

void dimLeds(uint8_t leds, int percentage, int duration) {
  for (int i = 0; i < duration; i++) {
    lightUpLed(leds);
    _delay_ms(percentage / 10);
    lightDownLed(leds);
    _delay_ms(10 - (percentage / 10));
  }
}