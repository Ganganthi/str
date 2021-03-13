#ifndef thread_per_h
#define thread_per_h

#include "timer.h"

class Thread_per
{
public:
    Thread_per(unsigned int, unsigned int);
    Thread_per();

    void run();
    Timer timer;
    
    void tempoderesposta();
    
private:
    int period;
    int priority;
    int load;
    
    
    
};

#endif 