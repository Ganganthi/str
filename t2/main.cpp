#include <iostream>
#include "timer.h"
#include "thread_per.h"
#include <sched.h>

int main(){
    unsigned int per = 0;
    int priori = 0;
    unsigned int load;
    int policy = 0;
    while(per<1 || per>999){
        std::cout<< "Entre com o período de 1 a 999 (em ms)" << std::endl;
        std::cin >> per;
    }
    while (priori<1 || priori>99)
    {
        std::cout<< "Prioridade (1 - menos prioritario - a 99 - mais prioritario -)" << std::endl;
        std::cin >> priori;
    }
    std::cout<< "Fator de carga da CPU" << std::endl;
    std::cin >> load;

    while (policy<1 || policy>2)
    {
        std::cout<< "Polı́tica de escalonamento (SCHED FIFO = 1 ou SCHED RR = 2)" << std::endl;
        std::cin >> policy;
    }
    
    
    if(policy == 1) policy = SCHED_FIFO;
    else policy = SCHED_RR;

    // Configura a politica de escalonamento
    struct sched_param sp = { .sched_priority = priori};
    sched_setscheduler(0, policy, &sp);

    // Cria a tarefa periodica e a executa
    Thread_per *thr = new Thread_per(per*1000000, load);
    thr->run();

    delete thr;
    
    return 0;
}
