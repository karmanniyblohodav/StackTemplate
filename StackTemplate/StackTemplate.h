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

/**
 * @brief Конструктор по умолчанию.
 * Создает стек с начальной емкостью 10 элементов.
 */
template<typename T>
Stack<T>::Stack()
    : capacity{ 10 }, size{ 0 }, data{ new T[capacity] } {}

/**
 * @brief Конструктор с указанием размера.
 * @param size Начальная емкость стека. Должна быть положительным числом.
 * @throw std::logic_error Если размер меньше или равен нулю.
 */
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

/**
 * @brief Конструктор с инициализацией через список.
 * @param list Список инициализации для заполнения стека.
 */
template<typename T>
Stack<T>::Stack(const std::initializer_list<T> list)
    : capacity{ list.size() }, size{ list.size() }, data{ new T[capacity] }
{
    std::copy(list.begin(), list.end(), data);
}

/**
 * @brief Конструктор копирования.
 * @param other Стек, из которого копируются данные.
 */
template<typename T>
Stack<T>::Stack(const Stack& other)
    : capacity{ other.capacity }, size{ other.size }, data{ new T[other.capacity] }
{
    std::copy(other.data, other.data + other.size, data);
}

/**
 * @brief Конструктор перемещения.
 * Перемещает данные из другого стека, не копируя их.
 * @param other Стек, из которого перемещаются данные.
 */
template<typename T>
Stack<T>::Stack(Stack&& other) noexcept
    : capacity{ other.capacity }, size{ other.size }, data{ other.data }
{
    other.data = nullptr;
    other.size = 0;
    other.capacity = 0;
}

/**
 * @brief Деструктор.
 * Освобождает память, выделенную для хранения элементов стека.
 */
template<typename T>
Stack<T>::~Stack()
{
    delete[] data;
}

/**
 * @brief Оператор присваивания копированием.
 * @param other Стек, из которого копируются данные.
 * @return Ссылка на текущий стек.
 */
template<typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other)
{
    if (this != &other)
    {
        Stack<T> temp(other);
        std::swap(capacity, temp.capacity);
        std::swap(size, temp.size);
        std::swap(data, temp.data);
    }
    return *this;
}

/**
 * @brief Оператор присваивания перемещением.
 * @param other Стек, из которого перемещаются данные.
 * @return Ссылка на текущий стек.
 */
template<typename T>
Stack<T>& Stack<T>::operator=(Stack<T>&& other) noexcept
{
    if (this != &other)
    {
        std::swap(capacity, other.capacity);
        std::swap(size, other.size);
        std::swap(data, other.data);
    }
    return *this;
}

/**
 * @brief Проверяет корректность индекса.
 * @param i Индекс для проверки.
 * @throw std::out_of_range Если индекс выходит за пределы стека.
 */
template<typename T>
void Stack<T>::CheckIndex(const size_t i) const
{
    if (i >= size)
    {
        throw std::out_of_range("Неправильное значение индекса!");
    }
}

/**
 * @brief Проверяет корректность индекса.
 * @param i Индекс для проверки.
 * @throw std::out_of_range Если индекс выходит за пределы стека.
 */
template<typename T>
void Stack<T>::Expand()
{
    capacity *= 2;
    T* newData = new T[capacity];
    std::copy(data, data + size, newData);
    delete[] data;
    data = newData;
}

/**
 * @brief Добавляет элемент в стек.
 * @param value Значение, которое нужно добавить.
 */
template<typename T>
void Stack<T>::Push(const T& value)
{
    if (size >= capacity)
    {
        Expand();
    }
    data[size++] = value;
}

/**
 * @brief Удаляет верхний элемент из стека.
 * @throw std::out_of_range Если стек пуст.
 */
template<typename T>
void Stack<T>::Pop()
{
    if (IsEmpty())
    {
        throw std::out_of_range("Стек пуст!");
    }
    --size;
}

/**
 * @brief Возвращает верхний элемент стека.
 * @return Ссылка на верхний элемент.
 * @throw std::out_of_range Если стек пуст.
 */
template<typename T>
const T& Stack<T>::Peek() const
{
    if (IsEmpty())
    {
        throw std::out_of_range("Стек пуст!");
    }
    return data[size - 1];
}

/**
 * @brief Проверяет, пуст ли стек.
 * @return true, если стек пуст, иначе false.
 */
template<typename T>
bool Stack<T>::IsEmpty() const noexcept
{
    return size == 0;
}

/**
 * @brief Возвращает количество элементов в стеке.
 * @return Текущее количество элементов.
 */
template<typename T>
size_t Stack<T>::GetSize() const
{
    return size;
}

/**
 * @brief Возвращает строковое представление содержимого стека.
 * @return Строка, содержащая элементы стека через запятую.
 */
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