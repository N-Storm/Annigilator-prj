#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/cpufunc.h>
#include <util/delay.h>
#include <avr/wdt.h>
#include <string.h>
#include <avr/pgmspace.h>

unsigned char flag_nomer_bileta_gotov = 0;
unsigned char bilet_nomer = 0;
unsigned char otvet_nomer = 0;

#include "otvet.h"
#include "start_test.h" // 3 гудка и сброс flag
#include "basa.h"
#include "avr-init.h"

ISR(INT1_vect) // Кнопка
{
    if (flag_nomer_bileta_gotov == 0) {
        TCNT1 = 0;
        TIMSK1 = (1 << TOIE1); // Вкл. таймер
        bilet_nomer++;
        if (bilet_nomer == 41) {
            TIMSK1 = (0 << TOIE1); //Откл. таймер
            TCNT1 = 0;
            bilet_nomer = 0;
            start_test();
        }
    }
    if (flag_nomer_bileta_gotov == 1) {
        if (bilet_nomer == 1) memcpy_P(b, b1, 21);
        if (bilet_nomer == 2) memcpy_P(b, b2, 21);
        if (bilet_nomer == 3) memcpy_P(b, b3, 21);
        // 40 таких
        otvet_nomer++;
        otvet(otvet_nomer);
    }
}

ISR(TIMER1_OVF_vect) //  16 сек
{
    TIMSK1 = (0 << TOIE1); // Отключить таймер
    TCNT1 = 0;
    flag_nomer_bileta_gotov = 1;
    // Подтверждение
    char i = 0;
    while (i < bilet_nomer) {
        i++;

        _delay_ms(1000);
        PORTC = PORTC | 0b00100000; //Установка
        _delay_ms(1000);
        PORTC &= ~0b00100000; //Сброс
    }

}

int main(void) {
    avr_init();

    start_test(); // 3 звонка

    asm("sei");
    while (1) {
    }
    
    return 0;
}
