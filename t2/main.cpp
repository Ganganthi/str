#include <iostream>
#include "timer.h"
#include <sched.h>

int main(){
    unsigned int x;
    int priori;
    int load;
    int policity;
    std::cout<< "Entre com o período de 1 a 999 (em ms)" << std::endl;
    std::cin >> x ;
    std::cout<<std::endl<< "Prioridade ()" << std::endl;
    std::cin >> priori ;
    std::cout<<std::endl<< "Fator de carga da CPU" << std::endl;
    std::cin >> load;
    std::cout<<std::endl<< "Polı́tica de escalonamento (SCHED FIFO = 0 ou SCHED RR = 1)" << std::endl;
    std::cin >> policity;
    

    class Timer tim(x);
    int sinal;
    int a=9;
    int b=8;
    int c=1;
    while(1){   
        sigwait(&tim.sig_ref, &sinal);
        for ( int i = 0; i < load * 1000; i++) {
            a=a+b;
        }
        c=c*a*b;

        // chamada pra funcao gettime
        // calculo do tempo de resposta 
        // impressao do rta
    }
    
    return 0;
}



