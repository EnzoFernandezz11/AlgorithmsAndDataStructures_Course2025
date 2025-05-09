#include <iostream>
#include "queue.hpp"

class Event 
{
    private:
        struct Evento
        {
            int event_id;
            std::string m_name;
            std::string m_type;
        };

        Queue<Evento> m_eventosPendientes;

    public:
    
        void NewEvent(const Evento& evento) 
        {
            m_eventosPendientes.enqueue(evento);
        }

        void check()
        {
            std::cout<<"Ingrese 1 para ver el evento acutal. 0 para ver todos los eventos";
            int num ;
            std::cin >> num ;

            if(num == 1)
            {
                m_eventosPendientes.printHead();
            }else if(num == 0) 
            {
                m_eventosPendientes.print_all();
                m_eventosPendientes.clear();
            }else
            {
                std::cout<<"Numero ingresado incorrecto" ;
            }

        }
};
