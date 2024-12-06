#include "CppUnitTest.h"
#include "../StackTemplate/StackTemplate.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SolverTests
{
    TEST_CLASS(StackTests)
    {
    public:

        TEST_METHOD(Constructor_InitializerList_ElementsAddedCorrectly)
        {
            Stack<int> stack({ 1, 2, 3 });
            Assert::AreEqual(std::string("1 2 3 "), stack.ToString(), L"Стек должен содержать '1 2 3 '.");
        }

        TEST_METHOD(Push_MultipleElements_AddedInOrder)
        {
            Stack<int> stack;
            stack.Push(1);
            stack.Push(2);
            stack.Push(3);
            Assert::AreEqual(std::string("1 2 3 "), stack.ToString(), L"Стек должен содержать '1 2 3 '.");
        }

        TEST_METHOD(Pop_ValidStack_TopElementRemoved)
        {
            Stack<int> stack({ 1, 2, 3 });
            stack.Pop();
            Assert::AreEqual(std::string("1 2 "), stack.ToString(), L"Стек должен содержать '1 2 ' после удаления верхнего элемента.");
        }

        TEST_METHOD(Peek_ValidStack_ReturnsTopElement)
        {
            Stack<int> stack({ 1, 2, 3 });
            Assert::AreEqual(3, stack.Peek(), L"Головной элемент должен быть 3.");
        }

        TEST_METHOD(IsEmpty_EmptyStack_ReturnsTrue)
        {
            Stack<int> stack;
            Assert::IsTrue(stack.IsEmpty(), L"Стек должен быть пустым.");
        }

        TEST_METHOD(IsEmpty_NonEmptyStack_ReturnsFalse)
        {
            Stack<int> stack;
            stack.Push(1);
            Assert::IsFalse(stack.IsEmpty(), L"Стек не должен быть пустым.");
        }

        TEST_METHOD(Pop_EmptyStack_ThrowsOutOfRangeException)
        {
            Stack<int> stack;
            auto func = [&]() { stack.Pop(); };
            Assert::ExpectException<std::out_of_range>(func, L"Должно выбрасываться исключение std::out_of_range при попытке pop на пустом стеке.");
        }

        TEST_METHOD(Peek_EmptyStack_ThrowsOutOfRangeException)
        {
            Stack<int> stack;
            auto func = [&]() { stack.Peek(); };
            Assert::ExpectException<std::out_of_range>(func, L"Должно выбрасываться исключение std::out_of_range при попытке peek на пустом стеке.");
        }

        TEST_METHOD(ToString_IntegerStacks_ReturnsMatchingString)
        {
            Stack<int> stack1{ 0, 1 };
            Stack<int> stack2{ 0, 1 };

            Assert::AreEqual(stack1.ToString(), stack2.ToString(),
                L"Стек stack1 и stack2 должны быть равны по содержимому.");
        }

        TEST_METHOD(ToString_StringStacks_ReturnsMatchingString)
        {
            Stack<std::string> stack1{ "0", "1" };
            Stack<std::string> stack2{ "0", "1" };

            Assert::AreEqual(stack1.ToString(), stack2.ToString(),
                L"Стек stack1 и stack2 должны быть равны по содержимому.");
        }

        TEST_METHOD(ToString_PairStacks_ReturnsMatchingString)
        {
            std::pair<int, int> a(0, 0);
            Stack<std::pair<int, int>> stack1{ a, a };
            Stack<std::pair<int, int>> stack2{ a, a };

            Assert::AreEqual(stack1.ToString(), stack2.ToString(),
                L"Стек stack1 и stack2 должны быть равны по содержимому.");
        }
    };
}
