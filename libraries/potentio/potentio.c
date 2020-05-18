#include <avr/io.h>
#include <util/delay.h>

void enablePotentiometer() {
  ADMUX |= (1 << REFS0)| (1 << REFS1);  // instellen van de reference voltage 5V
  ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
  ADCSRA |= (1 << ADEN); //Enable de ADC
}
uint16_t readPotentiometer(){
    ADCSRA |= (1 << ADSC); //start de conversie analoog >> digitaal
    loop_until_bit_is_clear(ADCSRA,ADSC); //wacht tot conversie gebeurd is
    return ADC;//lees het resultaat uit
}