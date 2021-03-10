#include <iostream>
#include "timer.h"
#include "thread_per.h"
#include <sched.h>

int main(){
    unsigned int per = 0;
    int priori;
    unsigned int load;
    int policy;
    while(x<1 || x>999){
        std::cout<< "Entre com o período de 1 a 999 (em ms)" << std::endl;
        std::cin >> per;
    }
    while (priori<1 || priori>99)
    {
        std::cout<<std::endl<< "Prioridade (1 - mais prioritario - a 99 - menos prioritario -)" << std::endl;
        std::cin >> priori;
    }
    std::cout<<std::endl<< "Fator de carga da CPU" << std::endl;
    std::cin >> load;
    std::cout<<std::endl<< "Polı́tica de escalonamento (SCHED FIFO = 1 ou SCHED RR = 2)" << std::endl;
    std::cin >> policy;
    
    if(policy == 1) policy = SCHED_FIFO;
    else policy = SCHED_RR;

    
    struct sched_param sp = { .sched_priority = priori};
    std::cout<< "----------" << sp.sched_priority << "---------";
    sched_setscheduler(0, policy, &sp);
    // Thread_per *thr = new Thread_per(per, load);
    // thr->run();

    // delete thr;

    /*

           int    sched_get_priority_max(int);
           int    sched_get_priority_min(int);
           *int    sched_getparam(pid_t, struct sched_param *);
           *int    sched_getscheduler(pid_t);
           *int    sched_rr_get_interval(pid_t, struct timespec *);
           *int    sched_setparam(pid_t, const struct sched_param *);
           *int    sched_setscheduler(pid_t, int, const struct sched_param *);
           int    sched_yield(void);

           //sched_get_priority_min(policy),
    //sched_get_priority_max(policy);s
    */


    // class Timer tim(x);
    // int sinal;
    // int a=9;
    // int b=8;
    // int c=1;
    // while(1){   
    //     sigwait(&tim.sig_ref, &sinal);
    //     for ( int i = 0; i < load * 1000; i++) {
    //         a=a+b;
    //     }
    //     c=c*a*b;

    //     // chamada pra funcao gettime
    //     // calculo do tempo de resposta 
    //     // impressao do rta
    // }
    
    return 0;
}
