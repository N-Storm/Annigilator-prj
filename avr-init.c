#include <avr/io.h>

void avr_init() {
    DDRC = 0b00100000; // С5 Выход вибратора. 1-работает
    // D3 INT1 - Кнопка на землю
    EICRA = (1 << ISC11) | (0 << ISC10) | (0 << ISC01) | (0 << ISC00); //INT1 интерапт кнопка
    EIMSK = (1 << INT1) | (0 << INT0);
    EIFR = (1 << INTF1) | (0 << INTF0);
    ACSR = (1 << ACD) | (0 << ACBG) | (0 << ACO) | (0 << ACI) | (0 << ACIE) | (0 << ACIC) | (0 << ACIS1) | (0 << ACIS0);


    TCCR1B = (0 << ICNC1) | (0 << ICES1) | (0 << WGM13) | (0 << WGM12) | (1 << CS12) | (0 << CS11) | (0 << CS10); //Таймер 16 сек
}
