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
    // typedef void (Function)(int);

    //period in us
    Timer(const unsigned int period);

    Timer(){}

    ~Timer();
    
    int timer_enable();
    int timer_disable();

    // lista de sinais
    sigset_t sig_ref;

    timer_t timerid;   //(uintmax_t) timerid

    struct itimerspec its;
private:
////---------------------------------

    struct sigevent siev;
    

    struct sigaction action;

    
    //
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
