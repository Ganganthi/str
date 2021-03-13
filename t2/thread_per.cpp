#include "thread_per.h"


Thread_per::Thread_per(unsigned int periodo, unsigned int carga){
    period = periodo;
    load = carga;

    new (&timer) Timer(periodo);
    timer.timer_enable();
}

void Thread_per::tempoderesposta(){
    timer_gettime(timer.timerid, &timer.its);
    long v;
    v =  timer.its.it_interval.tv_nsec - timer.its.it_value.tv_nsec;
    
    std::cout<<"Tempo de resposta da tarefa "<< timer.timerid << "  : " << v/1000000 << " ms" <<std::endl;
}

void Thread_per::run(){
    int sinal;

    while(1){   
        sigwait(&timer.sig_ref, &sinal);
        for ( int i = 0; i < load * 1000; i++) {
        }
        
        tempoderesposta();

    }
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
    int timer_gettime(timer_t timerid, struct itimerspec *its){}
       The timer_gettime function returns two values: the amount of time before the timer expires and the repetition value set by the last call to the timer_settime function. If the timer is disarmed, a call to the timer with the timer_gettime function returns a zero for the value of the it_value member. To arm the timer again, call the timer_settime function for that timer ID and specify a new expiration value for the timer.

    The SCHED_RR policy differs slightly from the SCHED_FIFO policy. SCHED_RR allocates concurrent processes that have the same priority in a round-robin rotation. In this way, each process is assigned a timeslice. The sched_rr_get_interval() function will report the timeslice that has been allocated to each process.
Even though POSIX requires that this function must work only with SCHED_RR processes, the sched_rr_get_interval() function is able to retrieve the timeslice length of any process on Linux.
The timeslice information is returned as a timespec, or the number of seconds and nanoseconds since the base time of 00:00:00 GMT, 1 January 1970:
*/



