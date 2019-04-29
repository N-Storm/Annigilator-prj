#include <avr/io.h>
#include <util/delay.h>
#include "otvet.h"

void otvet(unsigned char x) // x - номер ответа
{
    unsigned char i = 1;
    x = b[x];

    while (i <= x) {
        i++;

        _delay_ms(1000);
        PORTC = PORTC | 0b00100000; //Установка
        _delay_ms(1500);
        PORTC &= ~0b00100000; //Сброс
        _delay_ms(2000);
    }
}
