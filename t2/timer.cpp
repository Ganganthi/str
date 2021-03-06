#include "timer.h"


void sighandler(int a, siginfo_t* b, void* c){
    if(a == SIGALRM) std::cout<< "Handler do timer." << std::endl;
}

Timer::Timer(const unsigned int period){
    //std::cout<<"dentro do TImer constructor"<<std::endl;
    _period = period;

    //sigevent
    siev.sigev_notify = SIGEV_SIGNAL;
    siev.sigev_signo = SIGALRM;
    siev.sigev_value.sival_ptr = &timerid;

    action.sa_flags = SA_SIGINFO;
    action.sa_sigaction = sighandler;
    sigemptyset(&action.sa_mask);  //nao bloquear nenhum sinal
    sigaction(SIGALRM, &action, NULL);

    its.it_value.tv_sec = 0;
    its.it_value.tv_nsec = _period * 1000000;
    its.it_interval.tv_sec = 0;
    its.it_interval.tv_nsec = _period * 1000000;

    sigemptyset(&sig_ref);
    sigaddset(&sig_ref, SIGALRM);   //bota o sigalarm na lista

    timer_create(CLOCK_REALTIME, &siev, &timerid);
    //liga o timer
    timer_enable();

}

//liga o timer
int Timer::timer_enable(){
    return timer_settime(timerid, 0, &its, NULL);
}
    
int Timer::timer_disable(){
    struct itimerspec disable;
    disable.it_value.tv_sec = 0;
    disable.it_value.tv_nsec = 0;
    disable.it_interval.tv_sec = 0;
    disable.it_interval.tv_nsec = 0;
    return timer_settime(timerid, 0, &disable, NULL);
}

/*
    _period = period;
    _handler = handler;

    timer.it_interval.tv_sec = _period/1000000;
    timer.it_interval.tv_usec = _period%1000000;
    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = 0;

    action.sa_handler = handler;
    action.sa_flags = 0;
    
    sigemptyset(&action.sa_mask);
    sigaction(SIGALRM, &action, NULL);

    setitimer(CLOCK_, &timer, NULL); 

    //sigwait();
    // int sig;
    //sigwait(&mask, &sig);  //pendente 
    // sigaction( SIGALRM, &action, NULL );

    */