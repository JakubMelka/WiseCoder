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

#include "custom_search.h"
#include "doctest.h"

#include <array>
#include <algorithm>

TEST_CASE("[search] linear search")
{
    static constexpr std::array<int, 6> array { 10, 20, 30, 40, 50, 60 };

    for (int value : array)
    {
        auto it = course_l01::linear_search(array.begin(), array.end(), value);
        CHECK_NE(it, array.end());
        CHECK_EQ(*it, value);
    }

    auto it = course_l01::linear_search(array.begin(), array.end(), 5);
    CHECK_EQ(it, array.end());
}

TEST_CASE("[search] binary search")
{
    static constexpr std::array<int, 6> array { 10, 20, 30, 40, 50, 60 };

    for (int value : array)
    {
        auto it = course_l01::binary_search(array.begin(), array.end(), value);
        CHECK_NE(it, array.end());
        CHECK_EQ(*it, value);
    }

    for (int i = 0; i < 70; ++i)
    {
        auto it = course_l01::binary_search(array.begin(), array.end(), i);
        if (std::binary_search(array.begin(), array.end(), i))
        {
            CHECK_NE(it, array.end());
            CHECK_EQ(*it, i);
        }
        else
        {
            CHECK_EQ(it, array.end());
        }
    }
}
