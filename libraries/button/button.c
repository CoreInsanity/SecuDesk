#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void enableButton(int button) {
  if (button < 0 || button > 2) return;
  DDRC &= ~(1 << PC1 + button);  // configureer input
  PORTC |= (1 << PC1 + button);  // zet pull-up weerstand aan
}

int buttonPushed(int button) {
  if (PINC & (1 << (PC1 + button))) {
    _delay_us(1000);
    return 0;
  } else {
    return 1;
  }
}

int buttonReleased(int button) { return !buttonPushed(button); }

void enableAllButtons() {
  for (int i = 0; i < 3; i++) {
    enableButton(i);
  }
}

void enableInterrupt(int button) {
  PCICR |= _BV(PCIE1);
  PCMSK1 |= _BV(PC1 + button);

  sei();
}

void enableAllInterrupts() {
  for (int i = 0; i < 3; i++)
  {
    enableInterrupt(i);
  }
}