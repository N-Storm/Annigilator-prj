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
        if (bilet_nomer == 4) memcpy_P(b, b4, 21);
        if (bilet_nomer == 5) memcpy_P(b, b5, 21);
        if (bilet_nomer == 6) memcpy_P(b, b6, 21);
        if (bilet_nomer == 7) memcpy_P(b, b7, 21);
        if (bilet_nomer == 8) memcpy_P(b, b8, 21);
        if (bilet_nomer == 9) memcpy_P(b, b9, 21);
        if (bilet_nomer == 10) memcpy_P(b, b10, 21);
        if (bilet_nomer == 11) memcpy_P(b, b11, 21);
        if (bilet_nomer == 12) memcpy_P(b, b12, 21);
        if (bilet_nomer == 13) memcpy_P(b, b13, 21);
        if (bilet_nomer == 14) memcpy_P(b, b14, 21);
        if (bilet_nomer == 15) memcpy_P(b, b15, 21);
        if (bilet_nomer == 16) memcpy_P(b, b16, 21);
        if (bilet_nomer == 17) memcpy_P(b, b17, 21);
        if (bilet_nomer == 18) memcpy_P(b, b18, 21);
        if (bilet_nomer == 19) memcpy_P(b, b19, 21);
        if (bilet_nomer == 20) memcpy_P(b, b20, 21);
        if (bilet_nomer == 21) memcpy_P(b, b21, 21);
        if (bilet_nomer == 22) memcpy_P(b, b22, 21);
        if (bilet_nomer == 23) memcpy_P(b, b23, 21);
        if (bilet_nomer == 24) memcpy_P(b, b24, 21);
        if (bilet_nomer == 25) memcpy_P(b, b25, 21);
        if (bilet_nomer == 26) memcpy_P(b, b26, 21);
        if (bilet_nomer == 27) memcpy_P(b, b27, 21);
        if (bilet_nomer == 28) memcpy_P(b, b28, 21);
        if (bilet_nomer == 29) memcpy_P(b, b29, 21);
        if (bilet_nomer == 30) memcpy_P(b, b30, 21);
        if (bilet_nomer == 31) memcpy_P(b, b31, 21);
        if (bilet_nomer == 32) memcpy_P(b, b32, 21);
        if (bilet_nomer == 33) memcpy_P(b, b33, 21);
        if (bilet_nomer == 34) memcpy_P(b, b34, 21);
        if (bilet_nomer == 35) memcpy_P(b, b35, 21);
        if (bilet_nomer == 36) memcpy_P(b, b36, 21);
        if (bilet_nomer == 37) memcpy_P(b, b37, 21);
        if (bilet_nomer == 38) memcpy_P(b, b38, 21);
        if (bilet_nomer == 39) memcpy_P(b, b39, 21);
        if (bilet_nomer == 40) memcpy_P(b, b40, 21);
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
