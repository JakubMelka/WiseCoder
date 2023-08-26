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

#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include <iterator>
#include <algorithm>
#include <random>

namespace course03
{

template<typename Iterator, typename Comparator = std::less<typename std::iterator_traits<Iterator>::value_type>>
void quick_sort(Iterator begin, Iterator end, const Comparator& comparator = Comparator())
{
    // First, shuffle the elements to ensure randomness, mitigating worst-case scenarios for QuickSort.
    // Then, perform the QuickSort algorithm using the provided comparator.
    std::random_device randomDevice;
    std::mt19937 randomGenerator(randomDevice());
    std::shuffle(begin, end, randomGenerator);
    quick_sort_impl(begin, end, comparator);
}

template<typename Iterator, typename Comparator = std::less<typename std::iterator_traits<Iterator>::value_type>>
void quick_sort_impl(Iterator begin, Iterator end, const Comparator& comparator = Comparator())
{
    // If the number of elements in the iterator range is zero or one,
    // no action is needed, as these items are implicitly sorted.
    const auto count = std::distance(begin, end);
    if (count < 2)
    {
        return;
    }

    auto pivot = *std::next(begin, count / 2);

    // Using std::partition to segregate the elements into three distinct partitions:
    // 1. Elements that are considered "less than" the pivot, which span from 'begin' to 'middle1'.
    // 2. Elements that are considered "equal to" the pivot, which span from 'middle1' to 'middle2'.
    // 3. Elements that are considered "greater than" the pivot, which span from 'middle2' to 'end'.
    auto middle1 = std::partition(begin, end, [&](const auto& element) { return comparator(element, pivot); });
    auto middle2 = std::partition(middle1, end, [&](const auto& element) { return !comparator(pivot, element); });

    // Recursively sort the two partitions
    quick_sort_impl(begin, middle1, comparator);
    quick_sort_impl(middle2, end, comparator);
}

}

#endif // QUICK_SORT_H
