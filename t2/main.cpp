#include <iostream>
#include "timer.h"

int main(){
    int x;
    std::cin >> x ;
    class Timer tim(x);
    int sinal;
    while(1){
        sinal = 0;
        sigwait(&tim.sig_ref, &sinal);
        if(sinal == SIGALRM) std::cout << "Recebido sinal"<<std::endl;
        else std::cout << "----------"<<std::endl;
        // for ( int i = 0; i < load * 1000; i++) {
            
        // }
    }
    
    return 0;
}



