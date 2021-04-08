// EPOS Semaphore Abstraction Declarations

#ifndef __semaphore_h
#define __semaphore_h

#include <utility/list.h>
#include <utility/handler.h>
#include <synchronizer.h>



__BEGIN_SYS

class Semaphore: protected Synchronizer_Common
{
public:
    Semaphore(int v = 1);
    ~Semaphore();

    void p();
    void v();

protected:
    volatile int _value;
};

// Semaforo para uso com SRP, com uma unica unidade
class Semaphore_SRP: public Semaphore
{
public:
    typedef List<Semaphore_SRP> Queue;
    typedef List_Elements::Doubly_Linked<Semaphore_SRP> Element;

    Semaphore_SRP(int max);
    ~Semaphore_SRP();

    void p();
    void v();


    void testando(){
        db<Synchronizer>(INF) << "Max ceiling = " << _max_ceiling << endl;
        db<Synchronizer>(INF) << "_ceiling = " << _ceiling << endl;
        db<Synchronizer>(INF) << "_system_ceiling = " << _system_ceiling << endl;
    }

private:
    // calcula o teto do semaforo
    void calculate_ceiling();

    // calcula o teto de todos os semaforos
    static void calculate_system_ceiling();

    // teto atual do semaforo
    volatile int _ceiling;

    // teto maximo do semaforo
    const int _max_ceiling;

    // teto do sistema atual
    static volatile int _system_ceiling;

    // fila contendo todos os semaforos SRP, para calculo do teto do sistema
    static Queue _srp_queue;

    // no da lista que contem o semaforo
    Element _link;


};


// An event handler that triggers a semaphore (see handler.h)
class Semaphore_Handler: public Handler
{
public:
    Semaphore_Handler(Semaphore * h) : _handler(h) {}
    ~Semaphore_Handler() {}

    void operator()() { _handler->v(); }

private:
    Semaphore * _handler;
};

__END_SYS

#endif
