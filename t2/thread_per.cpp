#include "thread_per.h"


Thread_per::Thread_per(unsigned int periodo, unsigned int carga){
    period = periodo;
    load = carga;

    new (&timer) Timer(periodo);
    timer.timer_enable();
}

// Calcula e imprime o tempo de resposta
void Thread_per::tempoderesposta(){
    timer_gettime(timer.timerid, &timer.its);
    long v;
    v =  timer.its.it_interval.tv_nsec - timer.its.it_value.tv_nsec;
    
    std::cout<<"Tempo de resposta da tarefa "<< timer.timerid << "  : " << v/1000000 << " ms" <<std::endl;
}

// Funcao que executa dentro da tarefa
void Thread_per::run(){
    int sinal;

    while(1){   
        sigwait(&timer.sig_ref, &sinal); // Espera o sinal chegar
        for ( int i = 0; i < load * 1000; i++) {
        }
        
        tempoderesposta();

    }
}



