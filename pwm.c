#include "SanUSB1.h"

#pragma interrupt interrupcao 
void interrupcao(){

                  }

unsigned long int resultado, Vresult; 
unsigned char i=0;
const char Tensao[] = "Tensao Result= ";
const char Rn[] = "\r\n";
const char TextoAD[] = "Valor AD= ";

void main(){
    clock_int_4MHz(); 
    taxa_serial(9600);
    habilita_canal_AD(AN0);

    while(1){
        for(i = 0 ; i < 100 ; i=i+5) { SetaPWM1(10000, i);SetaPWM2(10000, 100-i); 

            resultado = le_AD10bits(0);
            Vresult= (resultado * 5000)/1023;

            
            sendsw((char *)Tensao);
            sendnum(Vresult);
            sendsw((char *)Rn);

            inverte_saida(pin_b7);
            tempo_ms(50);
        }

        for(i = 100 ; i > 0 ; i=i-5) { SetaPWM1(1200, i);SetaPWM2(1200, 100-i);

            resultado = le_AD10bits(0);

            sends((char *)TextoAD);
            sendnum(resultado);
            sendsw((char *)Rn);

            inverte_saida(pin_b7);
            tempo_ms(60);
        }
    }
}

