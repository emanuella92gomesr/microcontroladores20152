//Programa que exibe números de 0 a 9 em um display de sete segmentos, através de conexão com celular via bluetooth

#include "SanUSB1.h" 
short int pisca=0;
unsigned char comando;

#pragma interrupt interrupcao
void interrupcao()
{
 if (serial_interrompeu)  {
     serial_interrompeu=0;
     comando = le_serial();

         switch (comando){
             case '1':
              PORTB = 0b110000; 
             break;

             case '2':
              PORTB = 0b11101101; 
             break;

             case '3':
              PORTB = 0b11111001; 
             break;

             case '4':
              PORTB = 0b10110011; 
             break;

             case '5':
              PORTB = 0b11011011; 
             break;

             case '6':
              PORTB = 0b11011111; 
             break;

             case '7':
              PORTB = 0b11110000; 
             break;

             case '8':
              PORTB = 0b11111111; 
             break;

             case '9':
              PORTB = 0b11111011; 
             break;

             case '0':
              PORTB = 0b11111110; 
             break;

             case 'D':
             pisca=0; nivel_baixo(pin_b7);
             break;

             case 'P':
             pisca=1;nivel_alto(pin_b7);
             break;
         }
   }
}

void main(){
    TRISB = 0;
    clock_int_4MHz();
    habilita_interrupcao(recep_serial);
    taxa_serial(19200);
while(1){

   while (pisca==1){
            inverte_saida(pin_b7);tempo_ms (300);
    }
     tempo_ms (2000);
}
}
