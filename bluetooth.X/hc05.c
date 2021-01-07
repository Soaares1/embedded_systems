/* -----------------------------------------------------------------------------------------------------
 * Autor: Eng. Gustavo Moura 
 * Biblioteca para displays LCD (controlador HD44780U) -> Testado c/ display 4x20
 * Versão 1.0 (17/12/2020)
 * -----------------------------------------------------------------------------------------------------

 * -----------------------------------------------------------------------------------------------------
 * Mapeamento de hardware: 

 * -----------------------------------------------------------------------------------------------------
 * Configurado p/ 20MHz -> Alterar conforme a frequência
 * -----------------------------------------------------------------------------------------------------
 */

#include "gm_lcd.h"
#include "eusart1.h"

#define mcu_tx PORTCbits.RC0 // TX do microcontrolador
#define mcu_rx PORTCbits.RC1 // RX do microcontrolador
#define EN PORTCbits.RC2 // Deve ser utilizado um divisor resistivo para fornecer 3,3V ao módulo

char HC05_configure()
 {  
     char data = 0;
     
     EN = 1;
     // Inicializa Serial p/ baud rate de 38400
     EUSART1_Write_Text("AT\r\n");
     data = EUSART1_Read();   // Captura a resposta do módulo
     
        // Se a resposta não for "OK"   
        // return 0;
        // break;
          
     EUSART1_Write_Text("AT+NAME=HC-05\r\n");
     EUSART1_Write_Text("AT+PSWD=1234\r\n");
     EUSART1_Write_Text("AT+UART=115200,0,0\r\n"); // Baud rate de 115200
     EUSART1_Write_Text("AT+RESET\r\n");    // Reseta o módulo após configuração do modo de operação
     EN = 0;
     
     return 1;
 }