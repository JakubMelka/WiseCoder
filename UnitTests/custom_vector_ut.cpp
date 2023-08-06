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

#include "custom_vector.h"
#include "doctest.h"

#include <vector>

template<typename T1, typename T2>
void test_iterator_equality(T1 it1, T1 it1End, T2 it2, T2 it2End)
{
    CHECK_EQ(std::distance(it1, it1End), std::distance(it2, it2End));

    for (; it1 != it1End && it2 != it2End; ++it1, ++it2)
    {
        CHECK_EQ(*it1, *it2);
    }
}

void test_vector_equality(const course_l01::vector<int>& v1, const std::vector<int>& v2)
{
    CHECK_EQ(v1.empty(), v2.empty());
    CHECK_EQ(v1.size(), v2.size());

    CHECK_EQ(std::distance(v1.begin(), v1.end()), std::distance(v2.begin(), v2.end()));

    for (size_t i = 0; i < std::min(v1.size(), v2.size()); ++i)
    {
        CHECK_EQ(v1[i], v2[i]);
        CHECK_EQ(v1.at(i), v2.at(i));
    }

    test_iterator_equality(v1.begin(), v1.end(), v2.begin(), v2.end());
    test_iterator_equality(v1.cbegin(), v1.cend(), v2.cbegin(), v2.cend());
    test_iterator_equality(v1.rbegin(), v1.rend(), v2.rbegin(), v2.rend());
    test_iterator_equality(v1.crbegin(), v1.crend(), v2.crbegin(), v2.crend());
}

TEST_SUITE_BEGIN("vector");

TEST_CASE("[vector] default constructor")
{
    course_l01::vector<int> vector1;
    std::vector<int> vector2;

    test_vector_equality(vector1, vector2);
}

TEST_CASE("[vector] constructor with 5 elements")
{
    course_l01::vector<int> vector1(5);
    std::vector<int> vector2(5);

    test_vector_equality(vector1, vector2);
}

TEST_CASE("[vector] constructor with iterator")
{
    std::vector<int> vector2 = { 1, 2, 3, 4, 5 };
    course_l01::vector<int> vector1(vector2.begin(), vector2.end());

    test_vector_equality(vector1, vector2);
}

TEST_CASE("[vector] copy constructor")
{
    std::vector<int> vector2 = { 1, 2, 3, 4, 5 };
    course_l01::vector<int> vector1(vector2.begin(), vector2.end());
    course_l01::vector<int> vector3(vector1);

    test_vector_equality(vector3, vector2);
}

TEST_CASE("[vector] move constructor")
{
    std::vector<int> vector2 = { 1, 2, 3, 4, 5 };
    course_l01::vector<int> vector1(vector2.begin(), vector2.end());
    course_l01::vector<int> vector3(std::move(vector1));

    test_vector_equality(vector3, vector2);
}

TEST_CASE("[vector] initializer list")
{
    course_l01::vector<int> vector1({ 1, 2, 3, 4, 5});
    std::vector<int> vector2 = { 1, 2, 3, 4, 5 };

    test_vector_equality(vector1, vector2);
}

TEST_CASE("[vector] assignment copy operator")
{
    std::vector<int> vector2 = { 1, 2, 3, 4, 5 };
    course_l01::vector<int> vector1(vector2.begin(), vector2.end());
    course_l01::vector<int> vector3;
    vector3 = vector1;

    test_vector_equality(vector3, vector2);
}

TEST_CASE("[vector] assignment move operator")
{
    std::vector<int> vector2 = { 1, 2, 3, 4, 5 };
    course_l01::vector<int> vector1(vector2.begin(), vector2.end());
    course_l01::vector<int> vector3;
    vector3 = std::move(vector1);

    test_vector_equality(vector3, vector2);
}

TEST_CASE("[vector] assign")
{
    course_l01::vector<int> vector1 = { 1, 2, 3, 4, 5 };
    std::vector<int> vector2 = { 1, 2, 3, 4, 5 };

    vector1.assign(7, 9);
    vector2.assign(7, 9);

    test_vector_equality(vector1, vector2);

    vector1.assign({ 10, 11, 12, 13, 14, 15 });
    vector2.assign({ 10, 11, 12, 13, 14, 15 });

    test_vector_equality(vector1, vector2);

    std::vector<int> vector3 = { 20, 21, 22, 23, 24 };

    vector1.assign(vector3.cbegin(), vector3.cend());
    vector2.assign(vector3.cbegin(), vector3.cend());

    test_vector_equality(vector1, vector2);
}

TEST_CASE("[vector] operator[]")
{
    course_l01::vector<int> vector1 = { 1, 2, 3, 4, 5 };
    std::vector<int> vector2 = { 1, 2, 3, 4, 5 };

    test_vector_equality(vector1, vector2);

    CHECK_EQ(vector1.front(), vector2.front());
    CHECK_EQ(vector1.back(), vector2.back());

    vector1[0] = 10;
    vector2[0] = 10;
    vector1[4] = 20;
    vector2[4] = 20;

    test_vector_equality(vector1, vector2);

    CHECK_EQ(vector1.front(), vector2.front());
    CHECK_EQ(vector1.back(), vector2.back());

    vector1.front() = 30;
    vector2.front() = 30;
    vector1.back() = 40;
    vector2.back() = 40;

    test_vector_equality(vector1, vector2);

    CHECK_EQ(vector1.front(), vector2.front());
    CHECK_EQ(vector1.back(), vector2.back());
}

TEST_CASE("[vector] max_size")
{
    course_l01::vector<int> vector1;

    CHECK_GE(vector1.max_size(), course_l01::vector<int>::size_type(1));
}

TEST_CASE("[vector] reserve")
{
    course_l01::vector<int> vector1;

    vector1.reserve(500);
    CHECK_GE(vector1.capacity(), 500);

    vector1.reserve(750);
    CHECK_GE(vector1.capacity(), 750);
}

TEST_CASE("[vector] shrink_to_fit")
{
    course_l01::vector<int> vector1 = { 1, 2, 3, 4, 5 };
    std::vector<int> vector2 = { 1, 2, 3, 4, 5 };

    vector1.reserve(500);
    CHECK_GE(vector1.capacity(), 500);
    test_vector_equality(vector1, vector2);

    vector1.reserve(750);
    CHECK_GE(vector1.capacity(), 750);
    test_vector_equality(vector1, vector2);

    vector1.shrink_to_fit();
    vector2.shrink_to_fit();

    test_vector_equality(vector1, vector2);
}

TEST_CASE("[vector] resize")
{
    course_l01::vector<int> vector1 = { 1, 2, 3, 4, 5 };
    std::vector<int> vector2 = { 1, 2, 3, 4, 5 };

    vector1.resize(15);
    vector2.resize(15);

    test_vector_equality(vector1, vector2);

    vector1.resize(3);
    vector2.resize(3);

    test_vector_equality(vector1, vector2);

    vector1.resize(7, 7);
    vector2.resize(7, 7);

    test_vector_equality(vector1, vector2);
}

TEST_CASE("[vector] clear")
{
    course_l01::vector<int> vector1 = { 1, 2, 3, 4, 5 };
    std::vector<int> vector2 = { 1, 2, 3, 4, 5 };

    test_vector_equality(vector1, vector2);

    vector1.clear();
    vector2.clear();

    test_vector_equality(vector1, vector2);

    CHECK_GE(vector1.capacity(), 5);
    CHECK_GE(vector2.capacity(), 5);
}

TEST_CASE("[vector] clear")
{
    course_l01::vector<int> vector1;
    std::vector<int> vector2 ;

    vector1.push_back(1);
    vector2.push_back(1);
    test_vector_equality(vector1, vector2);

    vector1.push_back(2);
    vector2.push_back(2);
    test_vector_equality(vector1, vector2);

    vector1.push_back(3);
    vector2.push_back(3);
    test_vector_equality(vector1, vector2);

    vector1.push_back(4);
    vector2.push_back(4);
    test_vector_equality(vector1, vector2);

    vector1.pop_back();
    vector2.pop_back();
    test_vector_equality(vector1, vector2);

    vector1.push_back(4);
    vector2.push_back(4);
    test_vector_equality(vector1, vector2);

    course_l01::vector<int> vector3 = { 1, 2, 3, 4, 5 };
    std::vector<int> vector4 = { 1, 2, 3, 4, 5 };

    vector1.swap(vector3);
    vector2.swap(vector4);

    test_vector_equality(vector1, vector2);
    test_vector_equality(vector3, vector4);
}

TEST_CASE("[vector] insert")
{
    course_l01::vector<int> vector1;
    std::vector<int> vector2 ;

    auto it1 = vector1.insert(vector1.end(), 1);
    auto it2 = vector2.insert(vector2.end(), 1);
    test_vector_equality(vector1, vector2);
    CHECK_EQ(std::distance(it1, vector1.end()), std::distance(it2, vector2.end()));

    it1 = vector1.insert(vector1.begin(), 2);
    it2 = vector2.insert(vector2.begin(), 2);
    test_vector_equality(vector1, vector2);
    CHECK_EQ(std::distance(it1, vector1.end()), std::distance(it2, vector2.end()));

    it1 = vector1.insert(std::next(vector1.begin()), 3);
    it2 = vector2.insert(std::next(vector2.begin()), 3);
    test_vector_equality(vector1, vector2);
    CHECK_EQ(std::distance(it1, vector1.end()), std::distance(it2, vector2.end()));

    it1 = vector1.insert(vector1.end(), 3, 4);
    it2 = vector2.insert(vector2.end(), 3, 4);
    test_vector_equality(vector1, vector2);
    CHECK_EQ(std::distance(it1, vector1.end()), std::distance(it2, vector2.end()));

    it1 = vector1.insert(vector1.begin(), 3, 5);
    it2 = vector2.insert(vector2.begin(), 3, 5);
    test_vector_equality(vector1, vector2);
    CHECK_EQ(std::distance(it1, vector1.end()), std::distance(it2, vector2.end()));

    it1 = vector1.insert(std::next(vector1.begin()), 3, 6);
    it2 = vector2.insert(std::next(vector2.begin()), 3, 6);
    test_vector_equality(vector1, vector2);
    CHECK_EQ(std::distance(it1, vector1.end()), std::distance(it2, vector2.end()));

    it1 = vector1.insert(vector1.end(), { 7, 8, 9 });
    it2 = vector2.insert(vector2.end(), { 7, 8, 9 });
    test_vector_equality(vector1, vector2);
    CHECK_EQ(std::distance(it1, vector1.end()), std::distance(it2, vector2.end()));

    it1 = vector1.insert(vector1.begin(), { 10, 11, 12 });
    it2 = vector2.insert(vector2.begin(), { 10, 11, 12 });
    test_vector_equality(vector1, vector2);
    CHECK_EQ(std::distance(it1, vector1.end()), std::distance(it2, vector2.end()));

    it1 = vector1.insert(std::next(vector1.begin()), { 13, 14, 15 });
    it2 = vector2.insert(std::next(vector2.begin()), { 13, 14, 15 });
    test_vector_equality(vector1, vector2);
    CHECK_EQ(std::distance(it1, vector1.end()), std::distance(it2, vector2.end()));

    std::vector<int> test1 = { 16, 17, 18 };
    it1 = vector1.insert(vector1.end(), test1.cbegin(), test1.cend());
    it2 = vector2.insert(vector2.end(), test1.cbegin(), test1.cend());
    test_vector_equality(vector1, vector2);
    CHECK_EQ(std::distance(it1, vector1.end()), std::distance(it2, vector2.end()));

    std::vector<int> test2 = { 19, 20, 21 };
    it1 = vector1.insert(vector1.begin(), test2.cbegin(), test2.cend());
    it2 = vector2.insert(vector2.begin(), test2.cbegin(), test2.cend());
    test_vector_equality(vector1, vector2);
    CHECK_EQ(std::distance(it1, vector1.end()), std::distance(it2, vector2.end()));

    std::vector<int> test3 = { 22, 23, 24 };
    it1 = vector1.insert(std::next(vector1.begin()), test3.cbegin(), test3.cend());
    it2 = vector2.insert(std::next(vector2.begin()), test3.cbegin(), test3.cend());
    test_vector_equality(vector1, vector2);
    CHECK_EQ(std::distance(it1, vector1.end()), std::distance(it2, vector2.end()));
}

TEST_CASE("[vector] erase single")
{
    course_l01::vector<int> vector1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
    std::vector<int> vector2 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

    test_vector_equality(vector1, vector2);

    auto it1 = vector1.erase(vector1.begin());
    auto it2 = vector2.erase(vector2.begin());
    CHECK_EQ(std::distance(it1, vector1.end()), std::distance(it2, vector2.end()));

    test_vector_equality(vector1, vector2);

    it1 = vector1.erase(std::prev(vector1.end()));
    it2 = vector2.erase(std::prev(vector2.end()));
    CHECK_EQ(std::distance(it1, vector1.end()), std::distance(it2, vector2.end()));

    test_vector_equality(vector1, vector2);

    it1 = vector1.erase(std::next(vector1.begin()));
    it2 = vector2.erase(std::next(vector2.begin()));
    CHECK_EQ(std::distance(it1, vector1.end()), std::distance(it2, vector2.end()));

    test_vector_equality(vector1, vector2);
}

TEST_CASE("[vector] erase multi")
{
    course_l01::vector<int> vector1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
    std::vector<int> vector2 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

    test_vector_equality(vector1, vector2);

    auto it1 = vector1.erase(vector1.begin(), vector1.begin());
    auto it2 = vector2.erase(vector2.begin(), vector2.begin());
    CHECK_EQ(std::distance(it1, vector1.end()), std::distance(it2, vector2.end()));

    test_vector_equality(vector1, vector2);

    it1 = vector1.erase(vector1.end(), vector1.end());
    it2 = vector2.erase(vector2.end(), vector2.end());
    CHECK_EQ(std::distance(it1, vector1.end()), std::distance(it2, vector2.end()));

    test_vector_equality(vector1, vector2);

    it1 = vector1.erase(vector1.begin(), vector1.end());
    it2 = vector2.erase(vector2.begin(), vector2.end());
    CHECK_EQ(std::distance(it1, vector1.end()), std::distance(it2, vector2.end()));

    test_vector_equality(vector1, vector2);

    vector1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
    vector2 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

    it1 = vector1.erase(vector1.begin(), std::next(vector1.begin(), 3));
    it2 = vector2.erase(vector2.begin(), std::next(vector2.begin(), 3));
    CHECK_EQ(std::distance(it1, vector1.end()), std::distance(it2, vector2.end()));

    test_vector_equality(vector1, vector2);

    it1 = vector1.erase(std::prev(vector1.end(), 3), vector1.end());
    it2 = vector2.erase(std::prev(vector2.end(), 3), vector2.end());
    CHECK_EQ(std::distance(it1, vector1.end()), std::distance(it2, vector2.end()));

    test_vector_equality(vector1, vector2);

    vector1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
    vector2 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

    it1 = vector1.erase(std::next(vector1.begin(), 1), std::prev(vector1.end(), 2));
    it2 = vector2.erase(std::next(vector2.begin(), 1), std::prev(vector2.end(), 2));
    CHECK_EQ(std::distance(it1, vector1.end()), std::distance(it2, vector2.end()));

    test_vector_equality(vector1, vector2);
}

TEST_CASE("[vector] emlace/emplace_back")
{
    course_l01::vector<int> vector1;
    std::vector<int> vector2 ;

    vector1.emplace_back(1);
    vector2.emplace_back(1);
    test_vector_equality(vector1, vector2);

    vector1.emplace_back(2);
    vector2.emplace_back(2);
    test_vector_equality(vector1, vector2);

    vector1.emplace_back(3);
    vector2.emplace_back(3);
    test_vector_equality(vector1, vector2);

    vector1.emplace_back(4);
    vector2.emplace_back(4);
    test_vector_equality(vector1, vector2);

    vector1.pop_back();
    vector2.pop_back();
    test_vector_equality(vector1, vector2);

    vector1.emplace_back(4);
    vector2.emplace_back(4);
    test_vector_equality(vector1, vector2);

    auto it1 = vector1.emplace(vector1.begin(), 6);
    auto it2 = vector2.emplace(vector2.begin(), 6);
    test_vector_equality(vector1, vector2);
    CHECK_EQ(std::distance(it1, vector1.end()), std::distance(it2, vector2.end()));

    it1 = vector1.emplace(vector1.end(), 7);
    it2 = vector2.emplace(vector2.end(), 7);
    test_vector_equality(vector1, vector2);
    CHECK_EQ(std::distance(it1, vector1.end()), std::distance(it2, vector2.end()));

    it1 = vector1.emplace(std::next(vector1.begin()), 8);
    it2 = vector2.emplace(std::next(vector2.begin()), 8);
    test_vector_equality(vector1, vector2);
    CHECK_EQ(std::distance(it1, vector1.end()), std::distance(it2, vector2.end()));

    course_l01::vector<int> vector3 = { 1, 2, 3, 4, 5 };
    std::vector<int> vector4 = { 1, 2, 3, 4, 5 };

    vector1.swap(vector3);
    vector2.swap(vector4);

    test_vector_equality(vector1, vector2);
    test_vector_equality(vector3, vector4);
}

TEST_SUITE_END();
