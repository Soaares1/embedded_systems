#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gm_lcd.h"
#include "eusart1.h"

#define _XTAL_FREQ 20000000
#define LED PORTCbits.RC2

uint8_t rcvdata[5] = {};
unsigned char k = 0;

void __interrupt() interrupcao() {
    
    uint8_t data;
        
    if (PIR1bits.RC1IF){
        
        data = EUSART1_Read();
        LED ^= 1;   
        LCD_printchar(data);

        if (data == 'L'){
            LCD_clear();
            __delay_ms(2);
            LCD_pos(3,1);
            LCD_printstring("Ligado !");
            EUSART1_Write_Text("Ligado !\r\n");
        }
        
        if (data == 'D'){
            LCD_clear();
            __delay_ms(2);
            LCD_pos(3,1);
            LCD_printstring("Desligado !");
            EUSART1_Write_Text("Desligado !\r\n");
        }
    }
}

void main(void) {
    
    unsigned char i = 0;
    
    // Configura todos os pinos como digitais, exceto AN0.
    ANSELA = 0x01; // 0b 0000 0001 
    ANSELB = 0x00; // 0b 0000 0000
    ANSELC = 0x00; // 0b 0000 0000
    ANSELD = 0x00; // 0b 0000 0000
    
    // Configura saídas
    TRISCbits.RC2 = 0; 
    
    // Configuração UART
    TRISCbits.RC6 = 1;
    TRISCbits.RC7 = 1;
    
    EUSART1_Initialize();
    LCD_initialize();
        
    OSCCON = 0x3C; // 0b 0011 1100
    OSCCON2 = 0x07; // 0b 0000 0111
    OSCTUNE = 0x00; //0b 0000 0000
    
    RCONbits.IPEN = 0; // Desabilita prioridade na interrupção
    INTCONbits.GIE = 1; // Habilita interrupção global
    INTCONbits.PEIE = 1; // Habilita interrupção por periféricos
    PIE1bits.RC1IE = 1; // Habilita interrupção do RX1
    
    LCD_pos(1,1); 

    while (1) {
        //EUSART1_Write_Text("Hello World!\n");
//        LCD_pos(1,4);        
//        LCD_printchar(data+48);
        
    }
}




