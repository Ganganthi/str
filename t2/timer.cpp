#include "timer.h"

// Handler do timer
void sighandler(int a, siginfo_t* b, void* c){
    std::cout<< "Perdeu deadline." << std::endl;
}

Timer::Timer(const unsigned int period){

    _period = period;

    // Indica qual sinal o timer usa
    siev.sigev_notify = SIGEV_SIGNAL;
    siev.sigev_signo = SIGALRM;
    siev.sigev_value.sival_ptr = &timerid;

    // Configura como o timer reage no final do periodo
    action.sa_flags = SA_SIGINFO;
    action.sa_sigaction = sighandler;
    sigemptyset(&action.sa_mask);  
    sigaction(SIGALRM, &action, NULL);

    sigemptyset(&sig_ref);
    sigaddset(&sig_ref, SIGALRM);   // Coloca o SIGALARM na lista sig_ref

    timer_create(CLOCK_REALTIME, &siev, &timerid);

    timer_enable();

}

// Inicia o timer
int Timer::timer_enable(){
    its.it_value.tv_sec = _period / 1000000000;
    its.it_value.tv_nsec = _period % 1000000000;
    its.it_interval.tv_sec = _period / 1000000000;
    its.it_interval.tv_nsec = _period % 1000000000;
    return timer_settime(timerid, 0, &its, NULL);
}

// Para o timer
int Timer::timer_disable(){
    its.it_value.tv_sec = 0;
    its.it_value.tv_nsec = 0;
    its.it_interval.tv_sec = 0;
    its.it_interval.tv_nsec = 0;
    return timer_settime(timerid, 0, &its, NULL);
}

Timer::~Timer(){
    timer_delete(timerid);
}
