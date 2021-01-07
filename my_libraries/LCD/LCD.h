/* -----------------------------------------------------------------------------------------------------
 * Autor: Eng. Gustavo Moura 
 * Biblioteca para displays LCD (controlador HD44780U) -> Testado c/ display 4x20
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

#include <xc.h>

// Inicializa display
void LCD_initialize (void);

// Limpa display
void LCD_clear (void);

// Posiciona o cursor
void LCD_pos (unsigned char linha, unsigned char coluna);

// Imprime um único caracter
void LCD_printchar (char character);

// Imprime string
void LCD_printstring(const char *s);