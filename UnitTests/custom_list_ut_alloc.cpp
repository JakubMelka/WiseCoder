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

#include "custom_list.h"
#include "doctest.h"

#include <list>

class TestInt
{
public:
    TestInt() { ++s_instanceCount; ++s_constructorCalls; }
    ~TestInt() { --s_instanceCount; ++s_destructorCalls; }

    TestInt(int v) : m_value(v) { ++s_instanceCount; ++s_constructorCalls; }
    TestInt(const TestInt& other) : m_value(other.m_value) { ++s_instanceCount; ++s_constructorCalls; }
    TestInt(TestInt&& other) : m_value(other.m_value) { ++s_instanceCount; ++s_constructorCalls; }

    TestInt& operator=(const TestInt& other) { m_value = other.m_value; return *this; }

    int get_value() const { return m_value; }

    bool operator==(const TestInt& other) const { return m_value == other.m_value; }
    bool operator<(const TestInt& other) const { return m_value < other.m_value; }

    static bool is_none_instance_existing() { return s_instanceCount == 0; }

    static int get_constructor_calls() { return s_constructorCalls; }
    static int get_destructor_calls() { return s_destructorCalls; }

private:
    inline static int s_constructorCalls = 0;
    inline static int s_destructorCalls = 0;
    inline static int s_instanceCount = 0;
    int m_value = 0;
};

template<typename T1, typename T2>
void test_iterator_equality(T1 it1, T1 it1End, T2 it2, T2 it2End)
{
    CHECK_EQ(std::distance(it1, it1End), std::distance(it2, it2End));

    for (; it1 != it1End && it2 != it2End; ++it1, ++it2)
    {
        CHECK_EQ(*it1, *it2);
    }
}

void test_list_equality(const course_l01::list<TestInt>& v1, const std::list<TestInt>& v2)
{
    CHECK_EQ(v1.empty(), v2.empty());
    CHECK_EQ(v1.size(), v2.size());

    CHECK_EQ(std::distance(v1.begin(), v1.end()), std::distance(v2.begin(), v2.end()));

    test_iterator_equality(v1.begin(), v1.end(), v2.begin(), v2.end());
    test_iterator_equality(v1.cbegin(), v1.cend(), v2.cbegin(), v2.cend());
    test_iterator_equality(v1.rbegin(), v1.rend(), v2.rbegin(), v2.rend());
    test_iterator_equality(v1.crbegin(), v1.crend(), v2.crbegin(), v2.crend());
}

TEST_SUITE_BEGIN("list");

TEST_CASE("[list] default constructor")
{
    course_l01::list<TestInt> list1;
    std::list<TestInt> list2;

    test_list_equality(list1, list2);

    CHECK(TestInt::is_none_instance_existing());
    CHECK_EQ(TestInt::get_constructor_calls(), TestInt::get_destructor_calls());
}

TEST_CASE("[list] constructor with 5 elements")
{
    {
        course_l01::list<TestInt> list1(5);
        std::list<TestInt> list2(5);

        test_list_equality(list1, list2);
    }

    CHECK(TestInt::is_none_instance_existing());
    CHECK_EQ(TestInt::get_constructor_calls(), TestInt::get_destructor_calls());
}

TEST_CASE("[list] constructor with iterator")
{
    {
        std::list<TestInt> list2 = { 1, 2, 3, 4, 5 };
        course_l01::list<TestInt> list1(list2.begin(), list2.end());

        test_list_equality(list1, list2);
    }

    CHECK(TestInt::is_none_instance_existing());
    CHECK_EQ(TestInt::get_constructor_calls(), TestInt::get_destructor_calls());
}

TEST_CASE("[list] copy constructor")
{
    {
        std::list<TestInt> list2 = { 1, 2, 3, 4, 5 };
        course_l01::list<TestInt> list1(list2.begin(), list2.end());
        course_l01::list<TestInt> list3(list1);

        test_list_equality(list3, list2);
    }

    CHECK(TestInt::is_none_instance_existing());
    CHECK_EQ(TestInt::get_constructor_calls(), TestInt::get_destructor_calls());
}

TEST_CASE("[list] move constructor")
{
    {
        std::list<TestInt> list2 = { 1, 2, 3, 4, 5 };
        course_l01::list<TestInt> list1(list2.begin(), list2.end());
        course_l01::list<TestInt> list3(std::move(list1));

        test_list_equality(list3, list2);
    }

    CHECK(TestInt::is_none_instance_existing());
    CHECK_EQ(TestInt::get_constructor_calls(), TestInt::get_destructor_calls());
}

TEST_CASE("[list] initializer list")
{
    {
        course_l01::list<TestInt> list1({ 1, 2, 3, 4, 5});
        std::list<TestInt> list2 = { 1, 2, 3, 4, 5 };

        test_list_equality(list1, list2);
    }

    CHECK(TestInt::is_none_instance_existing());
    CHECK_EQ(TestInt::get_constructor_calls(), TestInt::get_destructor_calls());
}

TEST_CASE("[list] assignment copy operator")
{
    {
        std::list<TestInt> list2 = { 1, 2, 3, 4, 5 };
        course_l01::list<TestInt> list1(list2.begin(), list2.end());
        course_l01::list<TestInt> list3;
        list3 = list1;

        test_list_equality(list3, list2);
    }

    CHECK(TestInt::is_none_instance_existing());
    CHECK_EQ(TestInt::get_constructor_calls(), TestInt::get_destructor_calls());
}

TEST_CASE("[list] assignment move operator")
{
    {
        std::list<TestInt> list2 = { 1, 2, 3, 4, 5 };
        course_l01::list<TestInt> list1(list2.begin(), list2.end());
        course_l01::list<TestInt> list3;
        list3 = std::move(list1);

        test_list_equality(list3, list2);
    }

    CHECK(TestInt::is_none_instance_existing());
    CHECK_EQ(TestInt::get_constructor_calls(), TestInt::get_destructor_calls());
}

TEST_CASE("[list] assign")
{
    {
        course_l01::list<TestInt> list1 = { 1, 2, 3, 4, 5 };
        std::list<TestInt> list2 = { 1, 2, 3, 4, 5 };

        list1.assign(7, 9);
        list2.assign(7, 9);

        test_list_equality(list1, list2);

        list1.assign({ 10, 11, 12, 13, 14, 15 });
        list2.assign({ 10, 11, 12, 13, 14, 15 });

        test_list_equality(list1, list2);

        std::list<TestInt> list3 = { 20, 21, 22, 23, 24 };

        list1.assign(list3.cbegin(), list3.cend());
        list2.assign(list3.cbegin(), list3.cend());

        test_list_equality(list1, list2);
    }

    CHECK(TestInt::is_none_instance_existing());
    CHECK_EQ(TestInt::get_constructor_calls(), TestInt::get_destructor_calls());
}

TEST_CASE("[list] front/back")
{
    {
        course_l01::list<TestInt> list1 = { 1, 2, 3, 4, 5 };
        std::list<TestInt> list2 = { 1, 2, 3, 4, 5 };

        test_list_equality(list1, list2);

        CHECK_EQ(list1.front(), list2.front());
        CHECK_EQ(list1.back(), list2.back());

        list1.front() = 30;
        list2.front() = 30;
        list1.back() = 40;
        list2.back() = 40;

        test_list_equality(list1, list2);

        CHECK_EQ(list1.front(), list2.front());
        CHECK_EQ(list1.back(), list2.back());
    }

    CHECK(TestInt::is_none_instance_existing());
    CHECK_EQ(TestInt::get_constructor_calls(), TestInt::get_destructor_calls());
}

TEST_CASE("[list] max_size")
{
    course_l01::list<TestInt> list1;

    CHECK_GE(list1.max_size(), course_l01::list<TestInt>::size_type(1));
    CHECK(TestInt::is_none_instance_existing());
    CHECK_EQ(TestInt::get_constructor_calls(), TestInt::get_destructor_calls());
}

TEST_CASE("[list] resize")
{
    {
        course_l01::list<TestInt> list1 = { 1, 2, 3, 4, 5 };
        std::list<TestInt> list2 = { 1, 2, 3, 4, 5 };

        list1.resize(15);
        list2.resize(15);

        test_list_equality(list1, list2);

        list1.resize(3);
        list2.resize(3);

        test_list_equality(list1, list2);

        list1.resize(7, 7);
        list2.resize(7, 7);

        test_list_equality(list1, list2);
    }

    CHECK(TestInt::is_none_instance_existing());
    CHECK_EQ(TestInt::get_constructor_calls(), TestInt::get_destructor_calls());
}

TEST_CASE("[list] clear")
{
    {
        course_l01::list<TestInt> list1 = { 1, 2, 3, 4, 5 };
        std::list<TestInt> list2 = { 1, 2, 3, 4, 5 };

        test_list_equality(list1, list2);

        list1.clear();
        list2.clear();

        test_list_equality(list1, list2);
    }

    CHECK(TestInt::is_none_instance_existing());
    CHECK_EQ(TestInt::get_constructor_calls(), TestInt::get_destructor_calls());
}

TEST_CASE("[list] push/pop")
{
    {
        course_l01::list<TestInt> list1;
        std::list<TestInt> list2 ;

        list1.push_back(1);
        list2.push_back(1);
        test_list_equality(list1, list2);

        list1.push_back(2);
        list2.push_back(2);
        test_list_equality(list1, list2);

        list1.push_back(3);
        list2.push_back(3);
        test_list_equality(list1, list2);

        list1.push_back(4);
        list2.push_back(4);
        test_list_equality(list1, list2);

        list1.pop_back();
        list2.pop_back();
        test_list_equality(list1, list2);

        list1.push_back(4);
        list2.push_back(4);
        test_list_equality(list1, list2);

        course_l01::list<TestInt> list3 = { 1, 2, 3, 4, 5 };
        std::list<TestInt> list4 = { 1, 2, 3, 4, 5 };

        list1.swap(list3);
        list2.swap(list4);

        test_list_equality(list1, list2);
        test_list_equality(list3, list4);
    }

    CHECK(TestInt::is_none_instance_existing());
    CHECK_EQ(TestInt::get_constructor_calls(), TestInt::get_destructor_calls());
}

TEST_CASE("[list] insert")
{
    {
        course_l01::list<TestInt> list1;
        std::list<TestInt> list2 ;

        auto it1 = list1.insert(list1.end(), 1);
        auto it2 = list2.insert(list2.end(), 1);
        test_list_equality(list1, list2);
        CHECK_EQ(std::distance(it1, list1.end()), std::distance(it2, list2.end()));

        it1 = list1.insert(list1.begin(), 2);
        it2 = list2.insert(list2.begin(), 2);
        test_list_equality(list1, list2);
        CHECK_EQ(std::distance(it1, list1.end()), std::distance(it2, list2.end()));

        it1 = list1.insert(std::next(list1.begin()), 3);
        it2 = list2.insert(std::next(list2.begin()), 3);
        test_list_equality(list1, list2);
        CHECK_EQ(std::distance(it1, list1.end()), std::distance(it2, list2.end()));

        it1 = list1.insert(list1.end(), 3, 4);
        it2 = list2.insert(list2.end(), 3, 4);
        test_list_equality(list1, list2);
        CHECK_EQ(std::distance(it1, list1.end()), std::distance(it2, list2.end()));

        it1 = list1.insert(list1.begin(), 3, 5);
        it2 = list2.insert(list2.begin(), 3, 5);
        test_list_equality(list1, list2);
        CHECK_EQ(std::distance(it1, list1.end()), std::distance(it2, list2.end()));

        it1 = list1.insert(std::next(list1.begin()), 3, 6);
        it2 = list2.insert(std::next(list2.begin()), 3, 6);
        test_list_equality(list1, list2);
        CHECK_EQ(std::distance(it1, list1.end()), std::distance(it2, list2.end()));

        it1 = list1.insert(list1.end(), { 7, 8, 9 });
        it2 = list2.insert(list2.end(), { 7, 8, 9 });
        test_list_equality(list1, list2);
        CHECK_EQ(std::distance(it1, list1.end()), std::distance(it2, list2.end()));

        it1 = list1.insert(list1.begin(), { 10, 11, 12 });
        it2 = list2.insert(list2.begin(), { 10, 11, 12 });
        test_list_equality(list1, list2);
        CHECK_EQ(std::distance(it1, list1.end()), std::distance(it2, list2.end()));

        it1 = list1.insert(std::next(list1.begin()), { 13, 14, 15 });
        it2 = list2.insert(std::next(list2.begin()), { 13, 14, 15 });
        test_list_equality(list1, list2);
        CHECK_EQ(std::distance(it1, list1.end()), std::distance(it2, list2.end()));

        std::list<TestInt> test1 = { 16, 17, 18 };
        it1 = list1.insert(list1.end(), test1.cbegin(), test1.cend());
        it2 = list2.insert(list2.end(), test1.cbegin(), test1.cend());
        test_list_equality(list1, list2);
        CHECK_EQ(std::distance(it1, list1.end()), std::distance(it2, list2.end()));

        std::list<TestInt> test2 = { 19, 20, 21 };
        it1 = list1.insert(list1.begin(), test2.cbegin(), test2.cend());
        it2 = list2.insert(list2.begin(), test2.cbegin(), test2.cend());
        test_list_equality(list1, list2);
        CHECK_EQ(std::distance(it1, list1.end()), std::distance(it2, list2.end()));

        std::list<TestInt> test3 = { 22, 23, 24 };
        it1 = list1.insert(std::next(list1.begin()), test3.cbegin(), test3.cend());
        it2 = list2.insert(std::next(list2.begin()), test3.cbegin(), test3.cend());
        test_list_equality(list1, list2);
        CHECK_EQ(std::distance(it1, list1.end()), std::distance(it2, list2.end()));
    }

    CHECK(TestInt::is_none_instance_existing());
    CHECK_EQ(TestInt::get_constructor_calls(), TestInt::get_destructor_calls());
}

TEST_CASE("[list] erase single")
{
    {
        course_l01::list<TestInt> list1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
        std::list<TestInt> list2 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

        test_list_equality(list1, list2);

        auto it1 = list1.erase(list1.begin());
        auto it2 = list2.erase(list2.begin());
        CHECK_EQ(std::distance(it1, list1.end()), std::distance(it2, list2.end()));

        test_list_equality(list1, list2);

        it1 = list1.erase(std::prev(list1.end()));
        it2 = list2.erase(std::prev(list2.end()));
        CHECK_EQ(std::distance(it1, list1.end()), std::distance(it2, list2.end()));

        test_list_equality(list1, list2);

        it1 = list1.erase(std::next(list1.begin()));
        it2 = list2.erase(std::next(list2.begin()));
        CHECK_EQ(std::distance(it1, list1.end()), std::distance(it2, list2.end()));

        test_list_equality(list1, list2);
    }

    CHECK(TestInt::is_none_instance_existing());
    CHECK_EQ(TestInt::get_constructor_calls(), TestInt::get_destructor_calls());
}

TEST_CASE("[list] erase multi")
{
    {
        course_l01::list<TestInt> list1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
        std::list<TestInt> list2 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

        test_list_equality(list1, list2);

        auto it1 = list1.erase(list1.begin(), list1.begin());
        auto it2 = list2.erase(list2.begin(), list2.begin());
        CHECK_EQ(std::distance(it1, list1.end()), std::distance(it2, list2.end()));

        test_list_equality(list1, list2);

        it1 = list1.erase(list1.end(), list1.end());
        it2 = list2.erase(list2.end(), list2.end());
        CHECK_EQ(std::distance(it1, list1.end()), std::distance(it2, list2.end()));

        test_list_equality(list1, list2);

        it1 = list1.erase(list1.begin(), list1.end());
        it2 = list2.erase(list2.begin(), list2.end());
        CHECK_EQ(std::distance(it1, list1.end()), std::distance(it2, list2.end()));

        test_list_equality(list1, list2);

        list1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
        list2 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

        it1 = list1.erase(list1.begin(), std::next(list1.begin(), 3));
        it2 = list2.erase(list2.begin(), std::next(list2.begin(), 3));
        CHECK_EQ(std::distance(it1, list1.end()), std::distance(it2, list2.end()));

        test_list_equality(list1, list2);

        it1 = list1.erase(std::prev(list1.end(), 3), list1.end());
        it2 = list2.erase(std::prev(list2.end(), 3), list2.end());
        CHECK_EQ(std::distance(it1, list1.end()), std::distance(it2, list2.end()));

        test_list_equality(list1, list2);

        list1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
        list2 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

        it1 = list1.erase(std::next(list1.begin(), 1), std::prev(list1.end(), 2));
        it2 = list2.erase(std::next(list2.begin(), 1), std::prev(list2.end(), 2));
        CHECK_EQ(std::distance(it1, list1.end()), std::distance(it2, list2.end()));

        test_list_equality(list1, list2);
    }

    CHECK(TestInt::is_none_instance_existing());
    CHECK_EQ(TestInt::get_constructor_calls(), TestInt::get_destructor_calls());
}

TEST_CASE("[list] emlace/emplace_back")
{
    {
        course_l01::list<TestInt> list1;
        std::list<TestInt> list2 ;

        list1.emplace_back(1);
        list2.emplace_back(1);
        test_list_equality(list1, list2);

        list1.emplace_back(2);
        list2.emplace_back(2);
        test_list_equality(list1, list2);

        list1.emplace_back(3);
        list2.emplace_back(3);
        test_list_equality(list1, list2);

        list1.emplace_back(4);
        list2.emplace_back(4);
        test_list_equality(list1, list2);

        list1.pop_back();
        list2.pop_back();
        test_list_equality(list1, list2);

        list1.emplace_back(4);
        list2.emplace_back(4);
        test_list_equality(list1, list2);

        auto it1 = list1.emplace(list1.begin(), 6);
        auto it2 = list2.emplace(list2.begin(), 6);
        test_list_equality(list1, list2);
        CHECK_EQ(std::distance(it1, list1.end()), std::distance(it2, list2.end()));

        it1 = list1.emplace(list1.end(), 7);
        it2 = list2.emplace(list2.end(), 7);
        test_list_equality(list1, list2);
        CHECK_EQ(std::distance(it1, list1.end()), std::distance(it2, list2.end()));

        it1 = list1.emplace(std::next(list1.begin()), 8);
        it2 = list2.emplace(std::next(list2.begin()), 8);
        test_list_equality(list1, list2);
        CHECK_EQ(std::distance(it1, list1.end()), std::distance(it2, list2.end()));

        course_l01::list<TestInt> list3 = { 1, 2, 3, 4, 5 };
        std::list<TestInt> list4 = { 1, 2, 3, 4, 5 };

        list1.swap(list3);
        list2.swap(list4);

        test_list_equality(list1, list2);
        test_list_equality(list3, list4);
    }

    CHECK(TestInt::is_none_instance_existing());
    CHECK_EQ(TestInt::get_constructor_calls(), TestInt::get_destructor_calls());
}

TEST_CASE("[list] merge")
{
    {
        course_l01::list<TestInt> list1 = { 2, 6, 7, 10 };
        course_l01::list<TestInt> list2 = { 1, 3, 5, 9, };
        std::list<TestInt> list3 = { 2, 6, 7, 10 };
        std::list<TestInt> list4 = { 1, 3, 5, 9, };

        list1.merge(list2);
        list3.merge(list4);

        test_list_equality(list1, list3);
        test_list_equality(list2, list4);
    }

    CHECK(TestInt::is_none_instance_existing());
    CHECK_EQ(TestInt::get_constructor_calls(), TestInt::get_destructor_calls());
}

TEST_CASE("[list] splice1")
{
    {
        course_l01::list<TestInt> list1 = { 2, 6, 7, 10 };
        course_l01::list<TestInt> list2 = { 1, 3, 5, 9, };
        std::list<TestInt> list3 = { 2, 6, 7, 10 };
        std::list<TestInt> list4 = { 1, 3, 5, 9, };

        list1.splice(list1.end(), list2);
        list3.splice(list3.end(), list4);

        test_list_equality(list1, list3);
        test_list_equality(list2, list4);
    }

    CHECK(TestInt::is_none_instance_existing());
    CHECK_EQ(TestInt::get_constructor_calls(), TestInt::get_destructor_calls());
}

TEST_CASE("[list] splice2")
{
    {
        course_l01::list<TestInt> list1 = { 2, 6, 7, 10 };
        course_l01::list<TestInt> list2 = { 1, 3, 5, 9, };
        std::list<TestInt> list3 = { 2, 6, 7, 10 };
        std::list<TestInt> list4 = { 1, 3, 5, 9, };

        list1.splice(list1.begin(), list2, list2.begin());
        list3.splice(list3.begin(), list4, list4.begin());

        test_list_equality(list1, list3);
        test_list_equality(list2, list4);

        list1.splice(list1.begin(), list2, std::next(list2.begin()));
        list3.splice(list3.begin(), list4, std::next(list4.begin()));

        test_list_equality(list1, list3);
        test_list_equality(list2, list4);
    }

    CHECK(TestInt::is_none_instance_existing());
    CHECK_EQ(TestInt::get_constructor_calls(), TestInt::get_destructor_calls());
}


TEST_CASE("[list] splice3")
{
    {
        course_l01::list<TestInt> list1 = { 2, 6, 7, 10 };
        course_l01::list<TestInt> list2 = { 1, 3, 5, 9, };
        std::list<TestInt> list3 = { 2, 6, 7, 10 };
        std::list<TestInt> list4 = { 1, 3, 5, 9, };

        list1.splice(list1.begin(), list2, list2.begin(), list2.end());
        list3.splice(list3.begin(), list4, list4.begin(), list4.end());

        test_list_equality(list1, list3);
        test_list_equality(list2, list4);
    }

    CHECK(TestInt::is_none_instance_existing());
    CHECK_EQ(TestInt::get_constructor_calls(), TestInt::get_destructor_calls());
}

TEST_CASE("[list] splice4")
{
    {
        course_l01::list<TestInt> list1 = { 2, 6, 7, 10 };
        course_l01::list<TestInt> list2 = { 1, 3, 5, 9, };
        std::list<TestInt> list3 = { 2, 6, 7, 10 };
        std::list<TestInt> list4 = { 1, 3, 5, 9, };

        list1.splice(list1.begin(), list2, std::next(list2.begin()), list2.end());
        list3.splice(list3.begin(), list4, std::next(list4.begin()), list4.end());

        test_list_equality(list1, list3);
        test_list_equality(list2, list4);
    }

    CHECK(TestInt::is_none_instance_existing());
    CHECK_EQ(TestInt::get_constructor_calls(), TestInt::get_destructor_calls());
}

TEST_CASE("[list] splice5")
{
    {
        course_l01::list<TestInt> list1 = { 2, 6, 7, 10 };
        course_l01::list<TestInt> list2 = { 1, 3, 5, 9, };
        std::list<TestInt> list3 = { 2, 6, 7, 10 };
        std::list<TestInt> list4 = { 1, 3, 5, 9, };

        list1.splice(list1.begin(), list2, std::next(list2.begin()), std::prev(list2.end()));
        list3.splice(list3.begin(), list4, std::next(list4.begin()), std::prev(list4.end()));

        test_list_equality(list1, list3);
        test_list_equality(list2, list4);
    }

    CHECK(TestInt::is_none_instance_existing());
    CHECK_EQ(TestInt::get_constructor_calls(), TestInt::get_destructor_calls());
}

TEST_CASE("[list] splice6")
{
    {
        course_l01::list<TestInt> list1 = { 2, 6, 7, 10 };
        course_l01::list<TestInt> list2 = { 1, 3, 5, 9, };
        std::list<TestInt> list3 = { 2, 6, 7, 10 };
        std::list<TestInt> list4 = { 1, 3, 5, 9, };

        list1.splice(list1.begin(), list2, list2.begin(), std::prev(list2.end()));
        list3.splice(list3.begin(), list4, list4.begin(), std::prev(list4.end()));

        test_list_equality(list1, list3);
        test_list_equality(list2, list4);
    }

    CHECK(TestInt::is_none_instance_existing());
    CHECK_EQ(TestInt::get_constructor_calls(), TestInt::get_destructor_calls());
}

TEST_CASE("[list] remove")
{
    {
        course_l01::list<TestInt> list1 = { 2, 6, 7, 10 };
        std::list<TestInt> list2 = { 2, 6, 7, 10 };

        list1.remove(TestInt(3));
        list2.remove(TestInt(3));
        test_list_equality(list1, list2);

        list1.remove(TestInt(2));
        list2.remove(TestInt(2));
        test_list_equality(list1, list2);

        list1.remove(TestInt(7));
        list2.remove(TestInt(7));
        test_list_equality(list1, list2);

        list1.remove(TestInt(10));
        list2.remove(TestInt(10));
        test_list_equality(list1, list2);

        list1.remove(TestInt(6));
        list2.remove(TestInt(6));
        test_list_equality(list1, list2);
    }

    CHECK(TestInt::is_none_instance_existing());
    CHECK_EQ(TestInt::get_constructor_calls(), TestInt::get_destructor_calls());
}

TEST_CASE("[list] reverse")
{
    {
        course_l01::list<TestInt> list1 = { 2, 6, 7, 10 };
        std::list<TestInt> list2 = { 2, 6, 7, 10 };

        list1.reverse();
        list2.reverse();
        test_list_equality(list1, list2);

        list1.reverse();
        list2.reverse();
        test_list_equality(list1, list2);
    }

    CHECK(TestInt::is_none_instance_existing());
    CHECK_EQ(TestInt::get_constructor_calls(), TestInt::get_destructor_calls());
}

TEST_CASE("[list] unique")
{
    {
        course_l01::list<TestInt> list1 = { 2, 2, 6, 7, 7, 7, 7, 10 };
        std::list<TestInt> list2 = { 2, 2, 6, 7, 7, 7, 7, 10 };

        list1.unique();
        list2.unique();
        test_list_equality(list1, list2);

        list1.unique();
        list2.unique();
        test_list_equality(list1, list2);
    }

    CHECK(TestInt::is_none_instance_existing());
    CHECK_EQ(TestInt::get_constructor_calls(), TestInt::get_destructor_calls());
}

TEST_CASE("[list] sort")
{
    {
        course_l01::list<TestInt> list1 = { 2, 6, 7, 10 };
        std::list<TestInt> list2 = { 2, 6, 7, 10 };

        list1.sort();
        list2.sort();
        test_list_equality(list1, list2);

        list1.reverse();
        list2.reverse();
        test_list_equality(list1, list2);

        list1.sort();
        list2.sort();
        test_list_equality(list1, list2);
    }

    CHECK(TestInt::is_none_instance_existing());
    CHECK_EQ(TestInt::get_constructor_calls(), TestInt::get_destructor_calls());
}

TEST_SUITE_END();
