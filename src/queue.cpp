#include "queue.hpp"
#include <iostream>


template<typename TData>
Queue<TData>::Queue()
        : m_front(nullptr)
        , m_rear(nullptr)
        , m_size(0)
    {
    }

template<typename TData> 
Queue<TData>::~Queue()
{
    clear();
}

template<typename TData> 
void Queue<TData>::enqueue(const TData& value)
{
    Node* newNode = new Node(value);
    if (isEmpty())
    {
        m_front = newNode;
        m_rear = newNode;
    }
    else
    {
        m_rear->next = newNode;
        m_rear = newNode;
    }
    ++m_size;
}

template<typename TData> 
void Queue<TData>::dequeue()
{
    if(isEmpty())
    {
        throw std::underflow_error("Queue is empty");
    }
    auto temp = new Node();
    temp = m_front;
    m_front = m_front->next;
    delete temp;
    --m_size;
}

template<typename TData>
TData Queue<TData>::front() const
{
    if (isEmpty())
    {
        throw std::underflow_error("Queue is empty");
    }
    return m_front->data;
}

template<typename TData>
bool Queue<TData>::isEmpty() const
{
    return m_size == 0;
}


template<typename TData>
size_t Queue<TData>::getSize() const
{
    return m_size;
}

template<typename TData>
void Queue<TData>::print_all() 
{
    Node* temp = m_front;
    while (temp != nullptr)
    {
        std::cout << temp->data << "\n";
        temp = temp->next;
    }
}

template<typename TData>
void Queue<TData>::printHead()
{
    if (!isEmpty())
    {
        std::cout << m_front->data << "\n";
    }
}

template<typename TData>
void Queue<TData>::clear()
{
    while (!isEmpty())
    {
        dequeue();
    }

}