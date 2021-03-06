
#ifndef timer_h
#define timer_h

#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <iostream>
#include <utility>


// int timer_create(clockid_t clockid = CLOCK_REALTIME, struct sigevent *sevp,
                        // timer_t *timerid);


class Timer
{
public:
    // typedef void (Function)(int);

    //period in us
    Timer(const unsigned int period);

    Timer(){}


    
    int timer_enable();

    int timer_disable();

    sigset_t sig_ref;
private:
////---------------------------------
    // clockid_t clockid = CLOCK_REALTIME;
    timer_t timerid;   //(uintmax_t) timerid
    struct sigevent siev;
    struct itimerspec its;

    struct sigaction action;

    // action.sa_flags = SA_SIGINFO;
    // action.sa_sigaction = handler;
    // sigemptyset(&action.sa_mask);

  
/////----------------------------------

    unsigned int _period;
};

// void sighandler(int a, siginfo_t* b, void* c){
//     if(a == SIGALRM) std::cout<< "Handler do timer." << std::endl;
// }


#endif
