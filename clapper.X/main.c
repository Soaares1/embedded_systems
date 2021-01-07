#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gm_lcd.h"

#define _XTAL_FREQ 20000000
#define LED PORTCbits.RC2

char batidas = 0;
char centena, dezena, unidade;

void __interrupt() interrupcao() {
        
    if (INTCONbits.INT0IF){
        
        unsigned int i = 0, j = 0;
        
        LED ^= 1; 
        batidas = batidas + 1;
        centena = batidas / 100;
        dezena = (batidas % 100) / 10;
        unidade = (batidas % 100) % 10;
        LCD_pos (3,9);
        LCD_printchar(centena+48);
        LCD_printchar(dezena+48);
        LCD_printchar(unidade+48);
        
        __delay_ms(500);
        INTCONbits.INT0IF = 0;
    }
}

void main(void) {
        
    // Configura todos os pinos como digitais, exceto AN0.
    ANSELA = 0x01; // 0b 0000 0001 
    ANSELB = 0x00; // 0b 0000 0000
    ANSELC = 0x00; // 0b 0000 0000
    ANSELD = 0x00; // 0b 0000 0000

    INTCONbits.INT0IF = 1; // Limpa flag de interrupção do INT0
    INTCONbits.INT0IE = 1; // Habilita interrupção externa INT0
    INTCON2bits.INTEDG0 = 1; // Interrupção por borda de subida
    //INTCON2bits.RBPU = 0; // Interrupção por borda de subida
    //INTCONbits.RBIE = 1; // Habilita interrupção externa INT0
    
    TRISBbits.RB0 = 1; // Entrada
    TRISCbits.RC2 = 0;  
    
    PORTCbits.RC2 = 0;  
    
    // Inicializa saídas
    LED = 0;

    LCD_initialize();

    LCD_pos (1,1);
    LCD_printstring("Contador de palmas:", sizeof("Contador de palmas:"));
     
    __delay_ms(1000);
    
    RCONbits.IPEN = 0; // Desabilita prioridade na interrupção
    INTCONbits.GIE = 1; // Habilita interrupção global
    INTCONbits.PEIE = 1; // Habilita interrupção por periféricos

    while (1) {

      
    }
}




