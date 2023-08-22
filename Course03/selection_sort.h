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

#ifndef SELECTION_SORT_H
#define SELECTION_SORT_H

#include <iterator>

namespace course03
{

template<typename Iterator, typename Comparator = std::less<typename std::iterator_traits<Iterator>::value_type>>
void selection_sort(Iterator begin, Iterator end, Comparator comparator = Comparator())
{
    while (begin != end)
    {
        // Obtain an iterator to the minimum element within the specified range
        // [begin, end) using the provided comparator function.
        Iterator it = std::min_element(begin, end, comparator);

        // Move the minimum element to the start of the unsorted range by swapping it
        // with the element at the start, but only if it's not already at the start.
        if (it != begin)
        {
            std::swap(*it, *begin);
        }

        // Increment the begin iterator, as the sorted range has expanded
        // by one element, moving the boundary of the unsorted range.
        ++begin;
    }
}

}

#endif // SELECTION_SORT_H
