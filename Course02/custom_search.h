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

#ifndef CUSTOM_SEARCH_H
#define CUSTOM_SEARCH_H

#include <functional>

namespace course_l01
{

template<typename Iterator, typename Value>
Iterator linear_search(Iterator it1, Iterator it2, const Value& value)
{
    for (; it1 != it2; ++it1)
    {
        if (*it1 == value)
            return it1;
    }

    return it2;
}

template<typename Iterator, typename Value, typename Comparator = std::less<Value>>
Iterator binary_search(Iterator it1, Iterator it2, const Value& value, const Comparator& comparator = Comparator())
{
    auto itEnd = it2;

    while (it1 != it2)
    {
        const auto mid = std::distance(it1, it2) / 2;
        auto itMid = std::next(it1, mid);

        if (comparator(*itMid, value))
            it1 = std::next(itMid); // middle value is lesser - use interval [itMid + 1, it2)
        else if (comparator(value, *itMid))
            it2 = itMid; // middle value is greater - use interval [it1, itMid)
        else
            return itMid; // value was found!
    }

    return itEnd;
}

}   // namespace course_l01

#endif // CUSTOM_SEARCH_H
