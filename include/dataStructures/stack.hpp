#ifndef STACK_HPP
#define STACK_HPP

#include <stdexcept>
#include <iostream>

/**
 * @brief Estructura de datos tipo Pila (LIFO - Last In, First Out)
 *
 * @tparam TData Tipo de dato almacenado en la pila
 */
template<typename TData>
class Stack
{
private:
    /**
     * @brief Nodo de la pila
     */
    struct Node
    {
        TData data; ///< Valor almacenado
        Node* next; ///< Puntero al siguiente nodo

        Node(const TData& data, Node* next = nullptr)
            : data(data)
            , next(next)
        {
        }
    };

    Node* m_top;   ///< Puntero al nodo superior (cima)
    size_t m_size; ///< Cantidad de elementos en la pila

public:
    /**
     * @brief Constructor por defecto
     */
    Stack();

    /**
     * @brief Destructor: libera todos los nodos
     */
    ~Stack();

    /**
     * @brief Agrega un elemento en la cima de la pila
     *
     * @param value Valor a insertar
     */
    void push(const TData& value);

    /**
     * @brief Elimina el elemento superior de la pila
     *
     * @throws std::underflow_error si la pila está vacía
     */
    void pop();

    /**
     * @brief Devuelve una referencia al elemento superior (mutable)
     *
     * @return TData& referencia al valor
     * @throws std::underflow_error si la pila está vacía
     */
    TData& top();

    /**
     * @brief Devuelve una referencia constante al elemento superior
     *
     * @return const TData& referencia constante al valor
     * @throws std::underflow_error si la pila está vacía
     */
    const TData& top() const;

    /**
     * @brief Verifica si la pila está vacía
     *
     * @return true si no hay elementos
     * @return false si hay al menos un elemento
     */
    bool isEmpty() const;

    /**
     * @brief Devuelve la cantidad de elementos en la pila
     *
     * @return size_t tamaño de la pila
     */
    size_t size() const;

    void print();
};

#endif // STACK_HPP