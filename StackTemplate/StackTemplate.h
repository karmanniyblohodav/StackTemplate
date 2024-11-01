#pragma once
#include <ostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <initializer_list>
#include <algorithm>

template<typename T>
class Stack final
{
private:
    size_t capacity;
    size_t size;
    T* data;

    void CheckIndex(const size_t i) const;
    void Expand();

public:
    Stack();
    explicit Stack(const int size);
    Stack(const std::initializer_list<T> list);
    Stack(const Stack& other);
    Stack(Stack&& other) noexcept;
    ~Stack();

    Stack& operator=(const Stack& other);
    Stack& operator=(Stack&& other) noexcept;

    const T& operator[](size_t i) const;
    T& operator[](size_t i);

    size_t GetSize() const;
    void Push(const T& value);
    void Pop();
    const T& Peek() const;
    bool IsEmpty() const noexcept;
    std::string ToString() const;
};

template<typename T>
Stack<T>::Stack()
    : capacity{ 10 }, size{ 0 }, data{ new T[capacity] } {}

template<typename T>
Stack<T>::Stack(const int size)
{
    if (size <= 0)
    {
        throw std::logic_error("Размер стека должен быть положительным!");
    }

    this->capacity = size;
    this->size = 0;
    this->data = new T[capacity];
}

template<typename T>
Stack<T>::Stack(const std::initializer_list<T> list)
    : capacity{ list.size() }, size{ list.size() }, data{ new T[capacity] }
{
    std::copy(list.begin(), list.end(), data);
}

template<typename T>
Stack<T>::Stack(const Stack& other)
    : capacity{ other.capacity }, size{ other.size }, data{ new T[other.capacity] }
{
    std::copy(other.data, other.data + other.size, data);
}

template<typename T>
Stack<T>::Stack(Stack&& other) noexcept
    : capacity{ other.capacity }, size{ other.size }, data{ other.data }
{
    other.data = nullptr;
    other.size = 0;
    other.capacity = 0;
}

template<typename T>
Stack<T>::~Stack()
{
    delete[] data;
}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other)
{
    if (this != &other)
    {
        delete[] data;
        capacity = other.capacity;
        size = other.size;
        data = new T[capacity];
        std::copy(other.data, other.data + size, data);
    }
    return *this;
}

template<typename T>
Stack<T>& Stack<T>::operator=(Stack<T>&& other) noexcept
{
    if (this != &other)
    {
        delete[] data;
        capacity = other.capacity;
        size = other.size;
        data = other.data;

        other.data = nullptr;
        other.size = 0;
        other.capacity = 0;
    }
    return *this;
}

template<typename T>
void Stack<T>::CheckIndex(const size_t i) const
{
    if (i >= size)
    {
        throw std::out_of_range("Неправильное значение индекса!");
    }
}

template<typename T>
void Stack<T>::Expand()
{
    capacity *= 2;
    T* newData = new T[capacity];
    std::copy(data, data + size, newData);
    delete[] data;
    data = newData;
}

template<typename T>
void Stack<T>::Push(const T& value)
{
    if (size >= capacity)
    {
        Expand();
    }
    data[size++] = value;
}

template<typename T>
void Stack<T>::Pop()
{
    if (IsEmpty())
    {
        throw std::underflow_error("Стек пуст!");
    }
    --size;
}

template<typename T>
const T& Stack<T>::Peek() const
{
    if (IsEmpty())
    {
        throw std::underflow_error("Стек пуст!");
    }
    return data[size - 1];
}

template<typename T>
bool Stack<T>::IsEmpty() const noexcept
{
    return size == 0;
}

template<typename T>
size_t Stack<T>::GetSize() const
{
    return size;
}

template<typename T>
std::string Stack<T>::ToString() const
{
    std::stringstream buffer;
    for (size_t i = 0; i < size; ++i)
    {
        buffer << data[i];
        if (i < size - 1)
        {
            buffer << ", ";
        }
    }
    return buffer.str();
}