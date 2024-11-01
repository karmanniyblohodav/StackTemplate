#include "CppUnitTest.h"
#include "../StackTemplate/StackTemplate.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SolverTests
{
    TEST_CLASS(StackTests)
    {
    public:

        TEST_METHOD(TestInitializerListConstructor)
        {
            Stack<int> stack({ 1, 2, 3 });
            Assert::AreEqual(std::string("1 2 3 "), stack.ToString(), L"Стек должен содержать '1 2 3 '.");
        }

        TEST_METHOD(TestPush)
        {
            Stack<int> stack;
            stack.Push(1);
            stack.Push(2);
            stack.Push(3);
            Assert::AreEqual(std::string("1 2 3 "), stack.ToString(), L"Стек должен содержать '1 2 3 '.");
        }

        TEST_METHOD(TestPop)
        {
            Stack<int> stack({ 1, 2, 3 });
            stack.Pop();
            Assert::AreEqual(std::string("1 2 "), stack.ToString(), L"Стек должен содержать '1 2 ' после удаления верхнего элемента.");
        }

        TEST_METHOD(TestPeek)
        {
            Stack<int> stack({ 1, 2, 3 });
            Assert::AreEqual(3, stack.Peek(), L"Головной элемент должен быть 3.");
        }

        TEST_METHOD(TestIsEmpty)
        {
            Stack<int> stack;
            Assert::IsTrue(stack.IsEmpty(), L"Стек должен быть пустым.");
            stack.Push(1);
            Assert::IsFalse(stack.IsEmpty(), L"Стек не должен быть пустым.");
        }

        TEST_METHOD(TestPopEmptyStack)
        {
            Stack<int> stack;
            auto func = [&]() { stack.Pop(); };
            Assert::ExpectException<std::out_of_range>(func, L"Должно выбрасываться исключение std::out_of_range при попытке pop на пустом стеке.");
        }

        TEST_METHOD(TestPeekEmptyStack)
        {
            Stack<int> stack;
            auto func = [&]() { stack.Peek(); };
            Assert::ExpectException<std::out_of_range>(func, L"Должно выбрасываться исключение std::out_of_range при попытке peek на пустом стеке.");
        }
    };
}
