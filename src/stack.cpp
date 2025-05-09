#include "stack.hpp"


template<typename TData>
Stack<TData>::Stack()
    : m_top(nullptr)
    , m_size(0)
{
}

template<typename TData>
Stack<TData>::~Stack()
{
    while (!isEmpty())
    {
        pop();
    }
}

template<typename TData>
void Stack<TData>::push(const TData& value)
{
    Node* newNode = new Node(value, m_top);
    m_top = newNode;
    ++m_size;
}

template<typename TData>
void Stack<TData>::pop()
{
    if (isEmpty())
    {
        throw std::underflow_error("Stack is empty");
    }
    Node* temp = m_top;
    m_top = m_top->next;
    delete temp;
    --m_size;
}

template<typename TData>
TData& Stack<TData>::top()
{
    if (isEmpty())
    {
        throw std::underflow_error("Stack is empty");
    }
    return m_top->data;
}

template<typename TData>
const TData& Stack<TData>::top() const
{
    if (isEmpty())
    {
        throw std::underflow_error("Stack is empty");
    }
    return m_top->data;
}

template<typename TData>
bool Stack<TData>::isEmpty() const
{
    return m_size == 0;
}

template<typename TData>
size_t Stack<TData>::size() const
{
    return m_size;
}

template<typename TData>
void Stack<TData>::print()
{
    Node* temp = m_top;
    while(temp != nullptr)
    {
        std::cout<< temp->data << "\n";
        temp = temp->next;
    }
}
