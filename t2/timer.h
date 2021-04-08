#ifndef timer_h
#define timer_h

#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <iostream>
#include <utility>


class Timer
{
public:
    
    //period in us
    Timer(const unsigned int period);

    Timer(){}

    ~Timer();
    
    int timer_enable();
    int timer_disable();

    // Lista de sinais
    sigset_t sig_ref;

    struct itimerspec its;
    timer_t timerid;   

private:


    struct sigevent siev;   

    struct sigaction action;

    unsigned int _period;
};

#endif
