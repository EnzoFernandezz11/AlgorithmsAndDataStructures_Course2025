#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP

class Engine; // Forward declaration of Engine
#include <atomic>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>

#include "visitorFactory.hpp"
class EventManager
{
public:
    // Inicia el hilo que genera eventos aleatorios.
    void start();

    // Detiene el hilo y limpia la cola.
    void stop();

    // Consulta si la cola está vacía.
    bool isEmpty();

    // Vacía la cola de eventos.
    void clearQueue();

    // Eventos
    NPC::VisitanteVariant popEvent();

    void setEngine(Engine* engine)
    {
        m_engine = engine;
    }

    void setFactory(VisitorFactory* factory)
    {
        m_factory = factory;
    }

private:
    std::atomic<bool> m_running {true};
    std::atomic<int> m_eventCount {0}; // Contador de eventos generados
    std::thread m_eventThread;
    std::mutex m_eventMutex;
    std::queue<NPC::VisitanteVariant> m_eventQueue;
    std::condition_variable m_eventCv;
    Engine* m_engine = nullptr;
    VisitorFactory* m_factory = nullptr;
};

#endif // EVENT_MANAGER_HPP
