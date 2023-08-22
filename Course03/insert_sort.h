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

#ifndef INSERT_SORT_H
#define INSERT_SORT_H

#include <iterator>

namespace course03
{

template<typename Iterator, typename Comparator = std::less<typename std::iterator_traits<Iterator>::value_type>>
void insert_sort(Iterator begin, Iterator end, Comparator comparator = Comparator())
{
    // If the number of elements in the iterator range is zero or one,
    // no action is needed, as these items are implicitly sorted.
    if (std::distance(begin, end) < 2)
    {
        return;
    }

    Iterator it = std::next(begin);

    while (it != end)
    {
        // Find the position where the current element (*it) should be inserted
        // to maintain the sorted order, using the given comparator.
        Iterator insert_it = std::upper_bound(begin, it, *it, comparator);

        // Move the current element out of the way, storing its value temporarily.
        auto value = std::move(*it);

        // Shift all elements that are greater than the current element one position to the right.
        // This creates space to insert the current element in the sorted order.
        std::move_backward(insert_it, it, std::next(it));

        // Insert the current element into the correct position to maintain sorted order.
        *insert_it = std::move(value);

        // Move the iterator to the next element to be sorted.
        ++it;
    }
}

}

#endif // INSERT_SORT_H
