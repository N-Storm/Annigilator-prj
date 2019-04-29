#include <avr/io.h>
#include <util/delay.h>

void start_test(void) // 3 вибрации при вкл.
{
    _delay_ms(200);
    PORTC = PORTC | 0b00100000; //Установка
    _delay_ms(200);
    PORTC &= ~0b00100000; //Сброс
    _delay_ms(200);
    PORTC = PORTC | 0b00100000; //Установка
    _delay_ms(200);
    PORTC &= ~0b00100000; //Сброс
    _delay_ms(200);
    PORTC = PORTC | 0b00100000; //Установка
    _delay_ms(200);
    PORTC &= ~0b00100000; //Сброс
    _delay_ms(500);
}
