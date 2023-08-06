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

#ifndef CUSTOM_QUEUE_H
#define CUSTOM_QUEUE_H

#include "custom_list.h"

namespace course_l01
{

template<typename T, class Container = list<T>>
class queue
{
public:
    using value_type = T;
    using container_type = Container;
    using reference = typename container_type::reference;
    using const_reference = typename container_type::const_reference;
    using size_type = typename container_type::size_type;

    queue() = default;
    queue( container_type&& cont ) : m_container(std::move(cont)) { }

    bool empty() const { return m_container.empty(); }
    size_type size() const { return m_container.size(); }

    reference front() { return m_container.front(); }
    const_reference front() const { return m_container.front(); }

    reference back() { return m_container.back(); }
    const_reference back() const { return m_container.back(); }

    void push( const value_type& value ) { m_container.push_back(value); }
    void push( value_type&& value ) { m_container.push_back(std::move(value)); }

    template<typename... Args>
    void emplace( Args&&... args ) { m_container.emplace_back(std::forward<Args>(args)...); }

    void pop() { m_container.pop_front(); }

    void swap( queue& other ) { m_container.swap(other.m_container); }

private:
    container_type m_container;
};

}   // namespace course_l01

#endif // CUSTOM_QUEUE_H
