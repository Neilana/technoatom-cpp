#include "gtest/gtest.h"
#include "Stack.h"

using MyNamespace::Stack;
//using namespace std;

// FIXME: Обычно пишут тесты ко всем методам. Иначе от них мало толку. Так что допиши.
TEST(StackTest, CheckEmpty)
{
    Stack <int> stack1;
    bool isEmpty = stack1.empty();
    ASSERT_EQ(isEmpty, true);

    stack1.push(1);
    stack1.push(2);
    stack1.push(3);
    isEmpty = stack1.empty();
    ASSERT_EQ(isEmpty, false);

    stack1.pop();
    stack1.pop();
    stack1.pop();
    isEmpty = stack1.empty();
    ASSERT_EQ(isEmpty, true);
}

TEST (StackTest, BasicMethods)
{
    Stack <int> stack1;
    stack1.push(1);
    stack1.push(2);
    stack1.push(3);
    stack1.push(4);

    int n = stack1.top();
    ASSERT_EQ(n, 4);

    stack1.pop();
    n = stack1.top();
    ASSERT_EQ(n, 3);

    Stack <int> stack2(stack1);
    stack2.pop();
    n = stack2.top();
    ASSERT_EQ(n, 2);

    /*Stack <int> stack3;
    n = stack3.top();
    ASSERT_EQ(n, 666); */
}
