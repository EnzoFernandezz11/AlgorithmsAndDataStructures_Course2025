#include "stack.hpp"
#include <iostream>

class History
{
    private:
    struct Action
    {
        int accion_id;
        std::string type;
        std::string character;

    };
    Stack<Action> m_historialDecisiones;

    public:
    void registerDecision(const Action& accion) 
    {
        m_historialDecisiones.push(accion);
    }

    void history()
    {
        std::cout<< "A continuacion se mostrara las acciones realizadas " << "\n";
        m_historialDecisiones.print();
    }

    //elimina la ultima accione
    void undo()
    {
        m_historialDecisiones.pop();
    }



};