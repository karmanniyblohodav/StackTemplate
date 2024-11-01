#include <iostream>
#include "..\StackTemplate\StackTemplate.h"
int main() {
    Stack<int> stack({ 1, 2, 3, 4, 5 });
    std::cout << "Начальный стек: " << stack.ToString() << std::endl;

    stack.Push(6);
    std::cout << "После Push(6): " << stack.ToString() << std::endl;

    stack.Pop();
    std::cout << "После Pop(): " << stack.ToString() << std::endl;

    std::cout << "Головной элемент (Peek): " << stack.Peek() << std::endl;
    std::cout << "Стек пуст? " << (stack.IsEmpty() ? "Yes" : "No") << std::endl;

    return 0;
}