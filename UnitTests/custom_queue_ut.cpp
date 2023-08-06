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
#include "custom_queue.h"

#include <queue>

void test_queue_equality(const course_l01::queue<int>& v1, const std::queue<int>& v2)
{
    CHECK_EQ(v1.empty(), v2.empty());
    CHECK_EQ(v1.size(), v2.size());

    if (!v1.empty())
    {
        CHECK_EQ(v1.front(), v2.front());
        CHECK_EQ(v1.back(), v2.back());
    }
}

TEST_CASE("[queue] default constructor")
{
    course_l01::queue<int> queue1;
    std::queue<int> queue2;

    test_queue_equality(queue1, queue2);
}

TEST_CASE("[queue] queue with 5 elements pushed")
{
    course_l01::queue<int> queue1;
    std::queue<int> queue2;

    for (int i = 0; i < 5; ++i)
    {
        queue1.push(i + 1);
        queue2.push(i + 1);

        test_queue_equality(queue1, queue2);
    }

    while (!queue1.empty())
    {
        queue1.pop();
        queue2.pop();

        test_queue_equality(queue1, queue2);
    }

    test_queue_equality(queue1, queue2);
}

TEST_CASE("[queue] queue with 5 elements emplaced")
{
    course_l01::queue<int> queue1;
    std::queue<int> queue2;

    for (int i = 0; i < 5; ++i)
    {
        queue1.emplace(i + 1);
        queue2.emplace(i + 1);

        test_queue_equality(queue1, queue2);
    }

    while (!queue1.empty())
    {
        queue1.pop();
        queue2.pop();

        test_queue_equality(queue1, queue2);
    }

    test_queue_equality(queue1, queue2);
}

TEST_CASE("[queue] swap queues")
{
    course_l01::queue<int> queue1;
    std::queue<int> queue2;

    for (int i = 0; i < 5; ++i)
    {
        queue1.emplace(i + 1);
        queue2.emplace(i + 1);

        test_queue_equality(queue1, queue2);
    }

    course_l01::queue<int> queue3;
    std::queue<int> queue4;

    queue3.swap(queue1);
    queue4.swap(queue2);

    while (!queue3.empty())
    {
        queue3.pop();
        queue4.pop();

        test_queue_equality(queue3, queue4);
    }

    test_queue_equality(queue3, queue4);
}
