#include <avr/interrupt.h>
#include <avr/io.h>
#include <button.h>
#include <display.h>
#include <led.h>
#include <digital.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <usart.h>
#include <util/delay.h>

#define BUTTON_PORT PORTC
#define BUTTON_PIN PINC
#define BUTTON_DDR DDRC
#define BUTTON1 PC1
#define BUTTON2 PC2
#define BUTTON3 PC3
#define LED1 PB2
#define LED2 PB3

int seq[5] = {3, 1, 2, 1, 3};
int curIndex = 0;
int checkEntry(int button);
void reset(int button);

void reset(int button) {
  writeNumberToSegment(0, button);
  _delay_ms(250);
  curIndex = 0;
  writeNumberToSegment(3, 0);
}

int checkEntry(int button) {
  if (seq[curIndex] == button) return 1;
  return 0;
}

ISR(PCINT1_vect) {
  if (bit_is_clear(BUTTON_PIN, BUTTON1) || bit_is_clear(BUTTON_PIN, BUTTON2) ||
      bit_is_clear(BUTTON_PIN, BUTTON3)) {
    _delay_us(1000);  // Check for debounce

    int button = 0;
    if (bit_is_clear(BUTTON_PIN, BUTTON1)) button = 1;
    if (bit_is_clear(BUTTON_PIN, BUTTON2)) button = 2;
    if (bit_is_clear(BUTTON_PIN, BUTTON3)) button = 3;

    if(button == 0) return; //Debounce

    if(checkEntry(button) == 0) reset(button); //Entry does not match, reset
    else{
      writeNumberToSegment(0, button);
      if(curIndex == 4) {
        _delay_ms(500);
        curIndex = 0;
        writeNumberToSegment(3, 1);
        pinMode(0, 0);
        _delay_ms(1000);
        pinMode(0, 1);
      }
      else curIndex++;
    }
  }
}

int main() {
  initUSART();
  initDisplay();

  enablePin(0); //Enable the relay
  enableAllButtons();
  enableAllInterrupts();

  while (1) {
    _delay_ms(1000);
  }

  return 0;
}