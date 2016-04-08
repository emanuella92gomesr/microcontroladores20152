#include "SanUSB1.h" //

#pragma interrupt interrupcao
void interrupcao(){}

long int var_p;
long int var_ad;

void main(){
    clock_int_4MHz();
    taxa_serial(19200);

    while(1){
        inverte_saida(pin_b7);
        tempo_ms(500);

        var_ad = le_AD10bits( 0 );

        if( var_ad <= 100 ) var_ad = 0;
        var_p = ( 100 * var_ad ) / 1023; 

        SetaPWM1(10000, var_p); 
        SetaPWM2(10000, var_p);
    }
}