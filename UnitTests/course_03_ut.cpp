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

#include "bubble_sort.h"
#include "insert_sort.h"
#include "selection_sort.h"
#include "merge_sort.h"
#include "quick_sort.h"
#include "heap_sort.h"
#include "doctest.h"

#include <vector>
#include <random>
#include <numeric>
#include <algorithm>

TEST_SUITE_BEGIN("sorting");

static const int SORT_REPEATS = 10;

std::vector<std::vector<int>> getTestNumbers()
{
    std::vector<std::vector<int>> result;

    for (int count : { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 50, 100, 200, 500, 1000 })
    {
        for (int i = 0; i < SORT_REPEATS; ++i)
        {
            std::vector<int> myVector(count);
            std::iota(myVector.begin(), myVector.end(), 1);

            std::random_device rd;
            std::mt19937 g(rd());
            std::shuffle(myVector.begin(), myVector.end(), g);

            result.emplace_back(std::move(myVector));
        }
    }

    return result;
}

TEST_CASE("[sorting] bubble sort - empty / one element")
{
    std::vector<int> myVector;
    course03::bubble_sort(myVector.begin(), myVector.end());
    CHECK(myVector.empty());

    myVector.push_back(1);
    course03::bubble_sort(myVector.begin(), myVector.end());
    CHECK(true);
}

TEST_CASE("[sorting] bubble sort")
{
    std::vector<std::vector<int>> testNumberSequences = getTestNumbers();
    for (std::vector<int>& numberSequence : testNumberSequences)
    {
        course03::bubble_sort(numberSequence.begin(), numberSequence.end());
        CHECK(std::is_sorted(numberSequence.begin(), numberSequence.end()));
    }
}

TEST_CASE("[sorting] insert sort - empty / one element")
{
    std::vector<int> myVector;
    course03::insert_sort(myVector.begin(), myVector.end());
    CHECK(myVector.empty());

    myVector.push_back(1);
    course03::insert_sort(myVector.begin(), myVector.end());
    CHECK(true);
}

TEST_CASE("[sorting] insert sort")
{
    std::vector<std::vector<int>> testNumberSequences = getTestNumbers();
    for (std::vector<int>& numberSequence : testNumberSequences)
    {
        course03::insert_sort(numberSequence.begin(), numberSequence.end());
        CHECK(std::is_sorted(numberSequence.begin(), numberSequence.end()));
    }
}

TEST_CASE("[sorting] selection sort - empty / one element")
{
    std::vector<int> myVector;
    course03::selection_sort(myVector.begin(), myVector.end());
    CHECK(myVector.empty());

    myVector.push_back(1);
    course03::selection_sort(myVector.begin(), myVector.end());
    CHECK(true);
}

TEST_CASE("[sorting] selection sort")
{
    std::vector<std::vector<int>> testNumberSequences = getTestNumbers();
    for (std::vector<int>& numberSequence : testNumberSequences)
    {
        course03::selection_sort(numberSequence.begin(), numberSequence.end());
        CHECK(std::is_sorted(numberSequence.begin(), numberSequence.end()));
    }
}

TEST_CASE("[sorting] merge sort - empty / one element")
{
    std::vector<int> myVector;
    course03::merge_sort(myVector.begin(), myVector.end());
    CHECK(myVector.empty());

    myVector.push_back(1);
    course03::merge_sort(myVector.begin(), myVector.end());
    CHECK(true);
}

TEST_CASE("[sorting] merge sort")
{
    std::vector<std::vector<int>> testNumberSequences = getTestNumbers();
    for (std::vector<int>& numberSequence : testNumberSequences)
    {
        course03::merge_sort(numberSequence.begin(), numberSequence.end());
        CHECK(std::is_sorted(numberSequence.begin(), numberSequence.end()));
    }
}

TEST_CASE("[sorting] quick sort - empty / one element")
{
    std::vector<int> myVector;
    course03::quick_sort(myVector.begin(), myVector.end());
    CHECK(myVector.empty());

    myVector.push_back(1);
    course03::quick_sort(myVector.begin(), myVector.end());
    CHECK(true);
}

TEST_CASE("[sorting] quick sort")
{
    std::vector<std::vector<int>> testNumberSequences = getTestNumbers();
    for (std::vector<int>& numberSequence : testNumberSequences)
    {
        course03::quick_sort(numberSequence.begin(), numberSequence.end());
        CHECK(std::is_sorted(numberSequence.begin(), numberSequence.end()));
    }
}

TEST_CASE("[sorting] heap sort - empty / one element")
{
    std::vector<int> myVector;
    course03::heap_sort(myVector.begin(), myVector.end());
    CHECK(myVector.empty());

    myVector.push_back(1);
    course03::heap_sort(myVector.begin(), myVector.end());
    CHECK(true);
}

TEST_CASE("[sorting] heap sort")
{
    std::vector<std::vector<int>> testNumberSequences = getTestNumbers();
    for (std::vector<int>& numberSequence : testNumberSequences)
    {
        course03::heap_sort(numberSequence.begin(), numberSequence.end());
        CHECK(std::is_sorted(numberSequence.begin(), numberSequence.end()));
    }
}

TEST_SUITE_END();
