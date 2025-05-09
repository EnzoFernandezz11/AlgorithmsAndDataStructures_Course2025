#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <stdexcept>


/**
 * @brief Estructura de datos tipo Cola (FIFO - First In, First Out)
 *
 * @tparam TData Tipo de dato almacenado en la cola
 */
template<typename TData>
class Queue
{
private:
    /**
     * @brief Nodo de la cola
     */
    struct Node
    {
        TData data;     ///< Dato almacenado
        Node* next; ///< Puntero al siguiente nodo

        explicit Node(const TData& value)
            : data(value)
            , next(nullptr)
        {
        }
    };

    Node* m_front; ///< Puntero al primer elemento
    Node* m_rear;  ///< Puntero al último elemento
    size_t m_size; ///< Cantidad de elementos en la cola

public:
    /**
     * @brief Constructor por defecto
     */
    Queue();

    /**
     * @brief Destructor: libera todos los nodos de la cola
     */
    ~Queue();

    /**
     * @brief Inserta un elemento al final de la cola
     *
     * @param value Valor a insertar
     */
    void enqueue(const TData& value);
    /**
     * @brief Elimina el primer elemento de la cola
     *
     * @throws std::underflow_error si la cola está vacía
     */
    void dequeue();

    /**
     * @brief Devuelve el primer elemento sin eliminarlo
     *
     * @return TData Primer valor en la cola
     * @throws std::underflow_error si la cola está vacía
     */
    TData front() const;

    /**
     * @brief Verifica si la cola está vacía
     *
     * @return true si no hay elementos
     * @return false si hay al menos un elemento
     */
    bool isEmpty() const;
    /**
     * @brief Devuelve la cantidad de elementos en la cola
     *
     * @return size_t tamaño de la cola
     */
    size_t getSize() const;

    void print_all();

    void printHead();

    void clear();                     
};

#endif // QUEUE_HPP
