#include "SanUSB48.h"
#pragma interrupt interrupcao 
void interrupcao() {
}
#byte port_b = 0xf81;
unsigned char set_seg[] ={0x10,0x00,0x78,0x02,0x12,0x19,0x30,0x24,0x79,0x40};

typedef enum {
    CATODO = 0, ANODO = 1
} comum;

void imprime_display(unsigned int numero, comum tipo)  {
    unsigned char caractere = set_seg[numero];
    if (tipo == CATODO)
        caractere = ~caractere;
    PORTB = caractere;
}

void liga_display(unsigned int pino, comum tipo)  {
    boolean isAlto = tipo == ANODO;
    saida_pino(pino, isAlto);
}

void desliga_display(unsigned int pino, comum tipo)  {
    boolean isAlto = tipo == ANODO;
    saida_pino(pino, !isAlto);
}

void conta99a0Displayde7Seg() {
    unsigned int i, z, dezena, unidade;
    unsigned int display_dezena = pin_c0;
    unsigned int display_unidade = pin_c1;

    for(i=0;i<99;i++) {
        dezena = i/10;
        unidade= i%10;

        for (z=0;z<15;z++) {
            desliga_display(display_unidade, CATODO);
            liga_display(display_dezena, ANODO);
            imprime_display(dezena, ANODO);

            tempo_ms(5);

            desliga_display(display_dezena, ANODO);
            liga_display(display_unidade, CATODO);
            imprime_display(unidade, CATODO);

            tempo_ms(5);
        }
    }
}
int flag = 0;
void tempo(int n) {
    int i=0;

    for(i ; i < n; i++) {
        if(!entrada_pin_e3)
            flag =1;
        tempo_ms(10);
    }
}
void pedestre(){
            nivel_baixo(pin_a0);
            tempo_ms(500);
            nivel_alto(pin_a1);
            tempo_ms(500);
            nivel_baixo(pin_a1);
            tempo_ms(500);
            nivel_alto(pin_a2);
            nivel_baixo(pin_a4);
            tempo_ms(500);
            nivel_alto(pin_a3);
            conta99a0Displayde7Seg();
}

void main(){
clock_int_48MHz();
TRISB = 0b00000000;

    while(1)
    {
        if(flag == 1){
            pedestre();
            flag= 0;

        }
        else {
            PORTB=0b01000000;
            nivel_alto(pin_c0);
            nivel_alto(pin_c1);

            nivel_baixo(pin_a3);
            tempo(50);
            nivel_baixo(pin_a2);
            tempo(50);
            nivel_alto(pin_a4);
            tempo(50);
            nivel_alto(pin_a0);

            
        }
    }
}

