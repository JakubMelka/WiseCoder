//
// (c) Jakub Melka 2023
//
// This source file is part of the licensed software between Jakub Melka
// and the users utilizing the software under the specified License Agreement.
// Usage of this source code is subject to the Software License Agreement.
//
// This source code is provided solely for educational, research, or teaching purposes,
// including paid ones. Licensee may modify, adapt, and create derivative works,
// but all modifications must be released as Public Domain or under a license having
// the same legal effect as publishing as Public Domain under US jurisdiction.
//
// The Software is provided "as is," without warranty of any kind. Licensor shall not be liable
// for any damages arising from the use or performance of this source code.
//
// Ownership and intellectual property rights to this source code remain with Licensor.
// It is important for the Licensee to read and understand the complete Software License Agreement.
//

#include "doctest.h"
#include "custom_stack.h"

#include <stack>

void test_stack_equality(const course_l01::stack<int>& v1, const std::stack<int>& v2)
{
    CHECK_EQ(v1.empty(), v2.empty());
    CHECK_EQ(v1.size(), v2.size());

    if (!v1.empty())
    {
        CHECK_EQ(v1.top(), v2.top());
    }
}

TEST_CASE("[stack] default constructor")
{
    course_l01::stack<int> stack1;
    std::stack<int> stack2;

    test_stack_equality(stack1, stack2);
}

TEST_CASE("[stack] stack with 5 elements pushed")
{
    course_l01::stack<int> stack1;
    std::stack<int> stack2;

    for (int i = 0; i < 5; ++i)
    {
        stack1.push(i + 1);
        stack2.push(i + 1);

        test_stack_equality(stack1, stack2);
    }

    while (!stack1.empty())
    {
        stack1.pop();
        stack2.pop();

        test_stack_equality(stack1, stack2);
    }

    test_stack_equality(stack1, stack2);
}

TEST_CASE("[stack] stack with 5 elements emplaced")
{
    course_l01::stack<int> stack1;
    std::stack<int> stack2;

    for (int i = 0; i < 5; ++i)
    {
        stack1.emplace(i + 1);
        stack2.emplace(i + 1);

        test_stack_equality(stack1, stack2);
    }

    while (!stack1.empty())
    {
        stack1.pop();
        stack2.pop();

        test_stack_equality(stack1, stack2);
    }

    test_stack_equality(stack1, stack2);
}

TEST_CASE("[stack] swap stacks")
{
    course_l01::stack<int> stack1;
    std::stack<int> stack2;

    for (int i = 0; i < 5; ++i)
    {
        stack1.emplace(i + 1);
        stack2.emplace(i + 1);

        test_stack_equality(stack1, stack2);
    }

    course_l01::stack<int> stack3;
    std::stack<int> stack4;

    stack3.swap(stack1);
    stack4.swap(stack2);

    while (!stack3.empty())
    {
        stack3.pop();
        stack4.pop();

        test_stack_equality(stack3, stack4);
    }

    test_stack_equality(stack3, stack4);
}
