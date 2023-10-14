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

#ifndef HEAP_SORT_H
#define HEAP_SORT_H

#include <iterator>
#include <algorithm>

namespace course03
{

template<typename Iterator, typename Comparator = std::less<typename std::iterator_traits<Iterator>::value_type>>
void heap_sort(Iterator begin, Iterator end, Comparator comparator = Comparator())
{
    std::make_heap(begin, end, comparator);
    std::sort_heap(begin, end, comparator);
}

template<typename Iterator, typename Comparator = std::less<typename std::iterator_traits<Iterator>::value_type>>
void heap_sort_v2(Iterator begin, Iterator end, Comparator comparator = Comparator())
{
    auto parentIndex = [](std::ptrdiff_t i) { return (i - 1) / 2; };
    auto childLeftIndex = [](std::ptrdiff_t i) { return 2 * i + 1; };
    auto childRightIndex = [](std::ptrdiff_t i) { return 2 * i + 2; };

    const std::ptrdiff_t count = std::distance(begin, end);

    // Nothing to be sorted
    if (count <= 1)
    {
        return;
    }

    std::ptrdiff_t lastHeapIndex = count - 1;

    auto bubbleDown = [&](std::ptrdiff_t index)
    {
        while (index <= lastHeapIndex)
        {
            const std::ptrdiff_t child1 = childLeftIndex(index);
            const std::ptrdiff_t child2 = childRightIndex(index);

            const bool hasChild1 = child1 <= lastHeapIndex;
            const bool hasChild2 = child2 <= lastHeapIndex;

            if (hasChild1 && hasChild2)
            {
                // We have both children in the heap. We must
                // test them both, we will move current value
                // to the lower nodes in the heap.
                auto& value = *std::next(begin, index);
                auto& valueLeftChild = *std::next(begin, child1);
                auto& valueRightChild = *std::next(begin, child2);

                if (comparator(value, valueLeftChild) || comparator(value, valueRightChild))
                {
                    if (comparator(valueLeftChild, valueRightChild))
                    {
                        std::swap(value, valueRightChild);
                        index = child2;
                    }
                    else
                    {
                        std::swap(value, valueLeftChild);
                        index = child1;
                    }
                }
                else
                {
                    return; // We are finished
                }
            }
            else if (hasChild1)
            {
                auto& value = *std::next(begin, index);
                auto& valueLeftChild = *std::next(begin, child1);

                if (comparator(value, valueLeftChild))
                {
                    std::swap(value, valueLeftChild);
                    index = child1;
                }
                else
                {
                    return; // We are finished
                }
            }
            else
            {
                return;
            }
        }
    };

    // Make heap
    for (std::ptrdiff_t i = parentIndex(lastHeapIndex); i >= 0; --i)
    {
        bubbleDown(i);
    }

    // Perform sort
    while (lastHeapIndex > 0)
    {
        std::swap(*begin, *std::next(begin, lastHeapIndex));
        --lastHeapIndex;
        bubbleDown(0);
    }
}

}

#endif // HEAP_SORT_H
