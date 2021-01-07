#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gm_lcd.h"

#define _XTAL_FREQ 20000000

#define LED PORTCbits.RC2

void main(void) {
    
    unsigned char i = 0;
    
    // Configura todos os pinos como digitais, exceto AN0.
    ANSELA = 0x01; // 0b 0000 0001 
    ANSELB = 0x00; // 0b 0000 0000
    ANSELC = 0x00; // 0b 0000 0000
    ANSELD = 0x00; // 0b 0000 0000
    
    // Configura saídas
    TRISCbits.RC2 = 0;  
    
    // Inicializa saídas
    LED = 0;

    LCD_initialize();

    LCD_pos (1,4);
    LCD_printstring("Gustavo Soares", sizeof("Gustavo Soares"));
    
    while (1) {
        LED ^= 1; 
        __delay_ms(1000);
    }
}




