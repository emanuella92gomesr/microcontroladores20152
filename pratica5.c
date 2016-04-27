
#include "SanUSB1.h"

#define DIGIT1 PORTCbits.RC0
#define DIGIT2 PORTCbits.RC1

#define VERDEP pin_a1
#define VERMEP pin_a2
#define VERDEC pin_a3
#define AMAREC pin_a4
#define VERMEC pin_a5

unsigned int i;
unsigned char flag = 0;
unsigned char count = 10;
unsigned char button = 0;
unsigned char display(unsigned char);

void verificar_botao();

#pragma interrupt interrupcao

void interrupcao() {
    unsigned char Msd, Lsd;
    TMR0L = 100; 
    INTCON = 0x20; 
    flag = ~flag; 

    if (flag == 0) { 
        DIGIT2 = 0; 
        Msd = count / 10; 
        PORTB = display(Msd); 
        DIGIT1 = 1; 
    }
    else { // Do digit 2
        DIGIT1 = 0; 
        Lsd = count % 10; 
        PORTB = display(Lsd); 
        DIGIT2 = 1;
    }
}

void verificar_botao() {
    if (!entrada_pin_e3) {
        button = 1;
    }
}

unsigned char display(unsigned char i) {
    unsigned char SEGMENT[ ] = { 0xBF, 0x86, 0xDB, 0xCF, 0xE6, 0xED, 0xFD, 0x87, 0xFF, 0xEF };
    unsigned char Pattern = SEGMENT[i]; // Pattern to return
    return Pattern;
}

void main() {
    clock_int_4MHz();
    TRISB = 0;
    TRISC = 0;
    DIGIT1 = 0;

    while (1) {
        if (button == 1) {
            button = 0;
            nivel_baixo(VERDEC);
            nivel_alto(VERMEP);  
            nivel_alto(AMAREC);  
            tempo_ms(3000);
            nivel_baixo(AMAREC); 
            nivel_baixo(VERMEP); 
            nivel_alto(VERDEP);  
            nivel_alto(VERMEC);  

            T0CON = 0xC4;
            TMR0L = 100;
            INTCON = 0xA0;

            for (count = 10; count > 0; count--) {
                tempo_ms(1000);
            }

            T0CON = 0x00;
            PORTB = 0x00; // Apaga Display

            nivel_baixo(VERMEC);  
            nivel_baixo(VERDEP);  
        }
        else {
            nivel_alto(VERDEC);   
            nivel_alto(VERMEP);   
            verificar_botao();
        }
    }
}
