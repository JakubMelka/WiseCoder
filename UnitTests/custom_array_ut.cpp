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

#include "custom_array.h"
#include "doctest.h"

#include <array>

template<typename T1, typename T2>
void test_iterator_equality(T1 it1, T1 it1End, T2 it2, T2 it2End)
{
    CHECK_EQ(std::distance(it1, it1End), std::distance(it2, it2End));

    for (; it1 != it1End && it2 != it2End; ++it1, ++it2)
    {
        CHECK_EQ(*it1, *it2);
    }
}

template<typename V1, typename V2>
void test_array_equality(const V1& v1, const V2& v2)
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

TEST_SUITE_BEGIN("array");

TEST_CASE("[array] default constructor")
{
    course_l01::array<int, 1> array1 { };
    std::array<int, 1> array2 { };

    test_array_equality(array1, array2);
}

TEST_CASE("[array] constructor with 5 elements")
{
    course_l01::array<int, 5> array1 { 1, 2, 3, 4, 5};
    std::array<int, 5> array2 { 1, 2, 3, 4, 5};

    test_array_equality(array1, array2);
}

TEST_CASE("[array] another constructor with 5 elements")
{
    std::array<int, 5> array2 = { 1, 2, 3, 4, 5 };
    course_l01::array<int, 5> array1 = { 1, 2, 3, 4, 5 };

    test_array_equality(array1, array2);
}

TEST_CASE("[array] copy constructor")
{
    std::array<int, 5> array2 = { 1, 2, 3, 4, 5 };
    course_l01::array<int, 5> array1 = { 1, 2, 3, 4, 5};
    course_l01::array<int, 5> array3(array1);

    test_array_equality(array3, array2);
}

TEST_CASE("[array] move constructor")
{
    std::array<int, 5> array2 = { 1, 2, 3, 4, 5 };
    course_l01::array<int, 5> array1 = { 1, 2, 3, 4, 5};
    course_l01::array<int, 5> array3(std::move(array1));

    test_array_equality(array3, array2);
}

TEST_CASE("[array] initializer list")
{
    course_l01::array<int, 5> array1({ 1, 2, 3, 4, 5});
    std::array<int, 5> array2({ 1, 2, 3, 4, 5 });

    test_array_equality(array1, array2);
}

TEST_CASE("[array] assignment copy operator")
{
    std::array<int, 5> array2 = { 1, 2, 3, 4, 5 };
    course_l01::array<int, 5> array1 = { 1, 2, 3, 4, 5 };
    course_l01::array<int, 5> array3;
    array3 = array1;

    test_array_equality(array3, array2);
}

TEST_CASE("[array] assignment move operator")
{
    std::array<int, 6> array2 = { 1, 2, 3, 4, 5 };
    course_l01::array<int, 6> array1 = { 1, 2, 3, 4, 5 };
    course_l01::array<int, 6> array3;
    array3 = std::move(array1);

    test_array_equality(array3, array2);
}

TEST_CASE("[array] operator[]")
{
    course_l01::array<int, 5> array1 = { 1, 2, 3, 4, 5 };
    std::array<int, 5> array2 = { 1, 2, 3, 4, 5 };

    test_array_equality(array1, array2);

    CHECK_EQ(array1.front(), array2.front());
    CHECK_EQ(array1.back(), array2.back());

    array1[0] = 10;
    array2[0] = 10;
    array1[4] = 20;
    array2[4] = 20;

    test_array_equality(array1, array2);

    CHECK_EQ(array1.front(), array2.front());
    CHECK_EQ(array1.back(), array2.back());

    array1.front() = 30;
    array2.front() = 30;
    array1.back() = 40;
    array2.back() = 40;

    test_array_equality(array1, array2);

    CHECK_EQ(array1.front(), array2.front());
    CHECK_EQ(array1.back(), array2.back());
}

TEST_CASE("[array] max_size")
{
    course_l01::array<int, 6> array1;

    CHECK_EQ(array1.max_size(), 6);
}

TEST_SUITE_END();
