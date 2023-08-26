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

#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include <iterator>
#include <algorithm>

namespace course03
{

template<typename Iterator, typename Comparator = std::less<typename std::iterator_traits<Iterator>::value_type>>
void merge_sort(Iterator begin, Iterator end, const Comparator& comparator = Comparator())
{
    // If the number of elements in the iterator range is zero or one,
    // no action is needed, as these items are implicitly sorted.
    const auto count = std::distance(begin, end);
    if (count < 2)
    {
        return;
    }

    // Split the range into two halves and recursively sort each half using merge sort.
    auto it_middle = std::next(begin, count / 2);
    merge_sort(begin, it_middle, comparator);
    merge_sort(it_middle, end, comparator);

    // Merge the two sorted halves in place.
    std::inplace_merge(begin, it_middle, end, comparator);
}

}

#endif // MERGE_SORT_H
