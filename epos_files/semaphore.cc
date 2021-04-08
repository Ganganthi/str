// EPOS Semaphore Abstraction Implementation

#include <semaphore.h>

__BEGIN_SYS

// typedef List<Semaphore_SRP> Queue;
Semaphore_SRP::Queue Semaphore_SRP::_srp_queue;
volatile int Semaphore_SRP::_system_ceiling=0;

Semaphore::Semaphore(int v): _value(v)
{
    db<Synchronizer>(TRC) << "Semaphore(value=" << _value << ") => " << this << endl;
}


Semaphore::~Semaphore()
{
    db<Synchronizer>(TRC) << "~Semaphore(this=" << this << ")" << endl;
}


void Semaphore::p()
{
    db<Synchronizer>(TRC) << "Semaphore::p(this=" << this << ",value=" << _value << ")" << endl;

    begin_atomic();
    if(fdec(_value) < 1)
        sleep(); // implicit end_atomic()
    else
        end_atomic();
}


void Semaphore::v()
{
    db<Synchronizer>(TRC) << "Semaphore::v(this=" << this << ",value=" << _value << ")" << endl;

    begin_atomic();
    if(finc(_value) < 0)
        wakeup();  // implicit end_atomic()
    else
        end_atomic();
}

// Implementacao do semaforo para uso com o SRP

Semaphore_SRP::Semaphore_SRP(int max):_max_ceiling(max), _link(this)
{
    db<Synchronizer>(TRC) << "Semaphore_SRP(value=" << max << ") => " << this << endl;
    
    _srp_queue.insert(&_link);
    _ceiling=0;

}

Semaphore_SRP::~Semaphore_SRP()
{
    db<Synchronizer>(TRC) << "~Semaphore_SRP(this=" << this << ")" << endl;
    _srp_queue.remove(&_link);
}

// calcula o teto do sistema
void Semaphore_SRP::calculate_system_ceiling(){
    Semaphore_SRP::Element *aux;
    aux = _srp_queue.head();
    int max=0;

    while(aux!=0){
        if(max < aux->object()->_ceiling) max = aux->object()->_ceiling;
        aux = aux->next();
    }

    _system_ceiling = max;
}

// calcula o teto do semaforo
void Semaphore_SRP::calculate_ceiling(){
    if(_value == 1) _ceiling=0;
    else _ceiling = _max_ceiling;
}


void Semaphore_SRP::p()
{
    db<Synchronizer>(TRC) << "Semaphore_SRP::p(this=" << this << ",value=" << _value << ")" << endl;

    begin_atomic();
    fdec(_value);
    calculate_ceiling();
    if(_ceiling > Semaphore_SRP::_system_ceiling) Semaphore_SRP::_system_ceiling = _ceiling;
    end_atomic();
}


void Semaphore_SRP::v()
{
    db<Synchronizer>(TRC) << "Semaphore_SRP::v(this=" << this << ",value=" << _value << ")" << endl;

    begin_atomic();
    finc(_value);
    if(_ceiling == Semaphore_SRP::_system_ceiling){
        calculate_ceiling();
        calculate_system_ceiling();
    }else{
        calculate_ceiling();
    }
    end_atomic();
}


__END_SYS
