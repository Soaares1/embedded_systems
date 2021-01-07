/* -----------------------------------------------------------------------------------------------------
 * Autor: Eng. Gustavo Moura 
 * Biblioteca para displays LCDs (controlador HD44780U) -> Testado c/ display 4x20
 * Versão 1.0 (17/12/2020)
 * -----------------------------------------------------------------------------------------------------
 * Posicionamento no display (DDRAM):
 * | 01 | 02 | 03 | 04 | 05 | 06 | 07 | 08 | 09 | 10 | 11 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 | 20 |
 * | 64 | 65 | 66 | 67 | 68 | 69 | 70 | 71 | 72 | 73 | 74 | 75 | 76 | 77 | 78 | 79 | 80 | 81 | 82 | 83 |
 * | 20 | 21 | 22 | 23 | 24 | 25 | 26 | 27 | 28 | 29 | 30 | 31 | 32 | 33 | 34 | 35 | 36 | 37 | 38 | 39 |
 * | 84 | 85 | 86 | 87 | 88 | 89 | 90 | 91 | 92 | 93 | 94 | 95 | 96 | 97 | 98 | 99 | 100| 101| 102| 103|
 * -----------------------------------------------------------------------------------------------------
 * Mapeamento de hardware: 
 * en: RC0 
 * rs: RC1 
 * D0 a D7: PORTDbits.RD0 a PORTDbits.RD7
 * -----------------------------------------------------------------------------------------------------
 * Configurado p/ 20MHz -> Alterar conforme a frequência
 * -----------------------------------------------------------------------------------------------------
 */

#include "gm_lcd.h"

#define en PORTCbits.RC0
#define rs PORTCbits.RC1

void LCD_initialize (void){
    unsigned int i = 0;
    
    // Configura saídas
    TRISD = 0x00; 
    TRISCbits.RC0 = 0;
    TRISCbits.RC1 = 0; 
    
    // Inicializa saídas
    PORTD = 0x00;
    rs = 0;
    en = 0;
    for (i = 0; i < 100; i++); // Ocupa 20 us -> n_ciclos = (20E-6) / t_ciclo, onde t_ciclo = 4*[(1)/(20E6)]  
    
    // Limpa LCD
    PORTD = 0x01; 
    rs = 0;
    en = 1; 
    for (i = 0; i < 100; i++); 
    en = 0;
    for (i = 0; i < 10000; i++); // Ocupa 2 ms -> n_ciclos = (2E-3) / t_ciclo, onde t_ciclo = 4*[(1)/(20E6)]
    
    // Modo de 8 bits
    PORTD = 0x38; // 0b 0011 1000
    rs = 0;
    en = 1;
    for (i = 0; i < 100; i++); 
    en = 0;
    for (i = 0; i < 200; i++); // Ocupa 40 us -> n_ciclos = (40E-6) / t_ciclo, onde t_ciclo = 4*[(1)/(20E6)]    
    
    // Liga LCD, Liga cursor, desliga blink
    PORTD = 0x0E; // 0b 0000 1110
    rs = 0;
    en = 1;
    for (i = 0; i < 100; i++); 
    en = 0;
    for (i = 0; i < 200; i++); 
    
    // Habilita incremento, desliga scroll
    PORTD = 0x06; // 0b 0000 0110
    rs = 0;
    en = 1;
    for (i = 0; i < 100; i++); 
    en = 0;
    for (i = 0; i < 200; i++); 
}

void LCD_clear (void){  // Limpa LCD
    unsigned int i = 0;
    
    PORTD = 0x01; // 0b 000 0001
    rs = 0;
    en = 1;
    for (i = 0; i < 100; i++); 
    en = 0;
    for (i = 0; i < 200; i++);
}

void LCD_pos (unsigned char linha, unsigned char coluna) { // Posiciona dados segundo o formato (linha, coluna)
    unsigned int i = 0;
    unsigned char cte, pos;
    
    cte = 0; pos = 0;
    
    if (linha == 1) cte = 0;
    else if (linha == 2) cte = 64;
    else if (linha == 3) cte = 20;
    else if (linha == 4) cte = 84;
    
    pos = cte + coluna - 1;
    
    PORTD = pos | 0x80 ; // 0b 1xxx xxxx
    rs = 0;
    en = 1;
    for (i = 0; i < 100; i++); 
    en = 0;
    for (i = 0; i < 200; i++);
}

void LCD_printchar (char character){ //Imprime Caracteres
    unsigned int i = 0;
    
    PORTD = character;
    rs = 1;
    en = 1;
    for (i = 0; i < 100; i++); 
    en = 0;
    for (i = 0; i < 200; i++);
}

//void LCD_printstring (char *string, unsigned char length){
//    unsigned char i = 0;
//    
//    for (i = 0; i < (length - 1); i++){
//        LCD_printchar (*(string + i));
//    }
//}

 void LCD_printstring(const char *s)
 {
     while(*s)
     {
         LCD_printchar(*s);
         s++;
     }
 }