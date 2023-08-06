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

#ifndef CUSTOM_ARRAY_H
#define CUSTOM_ARRAY_H

#include <stdexcept>
#include <iterator>

namespace course_l01
{

template<typename T, size_t N>
class array
{
public:
    // Type declarations
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using iterator = pointer;
    using const_iterator = const_pointer;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    // Capacity methods
    constexpr bool empty() const noexcept { return N == 0; }
    constexpr size_type size() const noexcept { return N; }
    constexpr size_type max_size() const noexcept { return N; }

    // Element access
    reference at( size_type pos );
    const_reference at( size_type pos ) const;

    reference operator[]( size_type pos ) { return m_data[pos]; }
    const_reference operator[]( size_type pos ) const { return m_data[pos]; }

    reference front() noexcept { return m_data[0]; }
    const_reference front() const noexcept { return m_data[0]; }

    reference back() noexcept { return m_data[size() - 1]; }
    const_reference back() const noexcept { return m_data[size() - 1]; }

    pointer data() noexcept { return m_data; }
    const_pointer data() const noexcept { return m_data; }

    // Iterators

    iterator begin() noexcept { return m_data; }
    const_iterator begin() const noexcept { return m_data; }
    const_iterator cbegin() const noexcept { return m_data; }

    iterator end() noexcept { return m_data + N; }
    const_iterator end() const noexcept { return m_data + N; }
    const_iterator cend() const noexcept { return m_data + N; }

    reverse_iterator rbegin() noexcept { return std::make_reverse_iterator(end()); }
    const_reverse_iterator rbegin() const noexcept { return std::make_reverse_iterator(end()); }
    const_reverse_iterator crbegin() const noexcept { return std::make_reverse_iterator(cend()); }

    reverse_iterator rend() noexcept { return std::make_reverse_iterator(begin()); }
    const_reverse_iterator rend() const noexcept { return std::make_reverse_iterator(begin()); }
    const_reverse_iterator crend() const noexcept { return std::make_reverse_iterator(cbegin()); }

    void fill(const value_type& val) { std::fill(begin(), end(), val); }
    void swap(const array<T, N>& other) { std::swap(*this, other); }

    T m_data[N];
};

template<typename T, size_t N>
typename array<T, N>::reference array<T, N>::at(size_type pos)
{
    if (!(pos < size()))
        throw std::out_of_range("array<T>::at - index is out of range.");

    return m_data[pos];
}

template<typename T, size_t N>
typename array<T, N>::const_reference array<T, N>::at(size_type pos) const
{
    if (!(pos < size()))
        throw std::out_of_range("array<T>::at - index is out of range.");

    return m_data[pos];
}

} // namespace course_l01

#endif // CUSTOM_ARRAY_H
