#include "timer.h"


void sighandler(int a, siginfo_t* b, void* c){
    //if(a == SIGALRM) std::cout<< "Handler do timer." << std::endl;
    std::cout<< "Handler do timer." << std::endl;
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

Timer::~Timer(){
    timer_delete(timerid);
}

/*
timer_gettime() returns the time until next expiration, and the
       interval, for the timer specified by timerid, in the buffer
       pointed to by curr_value.  The time remaining until the next
       timer expiration is returned in curr_value->it_value; this is
       always a relative value, regardless of whether the TIMER_ABSTIME
       flag was used when arming the timer.  If the value returned in
       curr_value->it_value is zero, then the timer is currently
       disarmed.  The timer interval is returned in
       curr_value->it_interval.  If the value returned in
       curr_value->it_interval is zero, then this is a "one-shot" timer.
*/