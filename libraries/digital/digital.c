#include <avr/io.h>
#include <util/delay.h>

void enablePin(int pin) {
  if (pin < 0 || pin > 2) return;

  if (pin == 0)
    DDRB |= (1 << (PB1 + pin));
  else if (pin == 1)
    DDRD |= (1 << (PD6));
  else if (pin == 2)
    DDRD |= (1 << (PD5));

  pinMode(pin, 1);
}
void enableAllPins() {
  for (int i = 0; i < 3; i++) enablePin(i);
}

void pinMode(int pin, int state) {
  if (pin < 0 || pin > 2) return;

  switch (state) {
    case 0:
      if (pin == 0)
        PORTB &= ~(1 << (PB1));
      else if (pin == 1)
        PORTD &= ~(1 << (PD6));
      else if (pin == 2)
        PORTD |= (1 << (PD5));
      break;

    case 1:
      if (pin == 0)
        PORTB |= (1 << (PB1));
      else if (pin == 1)
        PORTD |= (1 << (PD6));
      else if (pin == 2)
        PORTD |= (1 << (PD5));
      break;
  }
}