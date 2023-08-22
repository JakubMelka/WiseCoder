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

#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H

#include <iterator>

namespace course03
{

template<typename Iterator, typename Comparator = std::less<typename std::iterator_traits<Iterator>::value_type>>
void bubble_sort(Iterator begin, Iterator end, Comparator comparator = Comparator())
{
    // If the number of elements in the iterator range is zero or one,
    // no action is needed, as these items are implicitly sorted.
    if (std::distance(begin, end) < 2)
    {
        return;
    }

    bool changed = true;

    while (changed)
    {
        changed = false;

        for (auto it = std::next(begin); it != end; ++it)
        {
            if (comparator(*it, *std::prev(it)))
            {
                // The current value is less than the previous one. We must
                // swap the elements and mark that a change has occurred.
                std::swap(*it, *std::prev(it));
                changed = true;
            }
        }

        // The end iterator can be decremented, since the largest element
        // within the current iterator range has been moved to the end.
        --end;
    }
}

}

#endif // BUBBLE_SORT_H
