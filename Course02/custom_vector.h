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

#ifndef CUSTOM_VECTOR_H
#define CUSTOM_VECTOR_H

#include <memory>
#include <stdexcept>
#include <iterator>
#include <algorithm>

namespace course_l01
{

template<typename T>
class vector
{
public:
    // Type declarations
    using value_type = T;
    using allocator_type = std::allocator<T>;
    using size_type = typename allocator_type::size_type;
    using difference_type = typename allocator_type::difference_type;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = typename std::allocator_traits<allocator_type>::pointer;
    using const_pointer = typename std::allocator_traits<allocator_type>::const_pointer;
    using iterator = pointer;
    using const_iterator = const_pointer;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    vector() = default;
    explicit vector( size_type count ) { resize(count); }
    template< class InputIt >
    vector( InputIt first, InputIt last ) { insert(end(), first, last); }
    vector( const vector& other ) { insert(end(), other.begin(), other.end()); }
    vector( vector&& other ) { swap(other); }
    vector( std::initializer_list<T> init ) { insert(end(), init.begin(), init.end()); }
    ~vector();

    // Assignment operator
    vector& operator=( const vector& other );
    vector& operator=( vector&& other );

    // Assign methods
    void assign( size_type count, const T& value );
    template< class InputIt, std::enable_if_t<std::is_same_v<T, typename std::iterator_traits<InputIt>::value_type>, int> = 0 >
    void assign( InputIt first, InputIt last );
    void assign( std::initializer_list<T> ilist );

    // Element access
    reference at( size_type pos );
    const_reference at( size_type pos ) const;

    reference operator[]( size_type pos );
    const_reference operator[]( size_type pos ) const;

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

    iterator end() noexcept { return m_data + m_size; }
    const_iterator end() const noexcept { return m_data + m_size; }
    const_iterator cend() const noexcept { return m_data + m_size; }

    reverse_iterator rbegin() noexcept { return std::make_reverse_iterator(end()); }
    const_reverse_iterator rbegin() const noexcept { return std::make_reverse_iterator(end()); }
    const_reverse_iterator crbegin() const noexcept { return std::make_reverse_iterator(cend()); }

    reverse_iterator rend() noexcept { return std::make_reverse_iterator(begin()); }
    const_reverse_iterator rend() const noexcept { return std::make_reverse_iterator(begin()); }
    const_reverse_iterator crend() const noexcept { return std::make_reverse_iterator(cbegin()); }

    // Capacity methods
    bool empty() const noexcept { return m_size == 0; }
    size_type size() const noexcept { return m_size; }
    size_type max_size() const noexcept { return std::allocator_traits<allocator_type>::max_size(m_allocator); }
    void reserve( size_type new_capacity ) { grow(new_capacity); }
    size_type capacity() const noexcept { return m_capacity; }
    void shrink_to_fit() { shrink(); }
    void resize( size_type count );
    void resize( size_type count, const value_type& value );

    // Modifiers
    void clear();
    void push_back( const T& item );
    void push_back( T&& item );
    void swap( vector& other );
    void pop_back();

    // Insert
    iterator insert( const_iterator pos, const T& value );
    iterator insert( const_iterator pos, T&& value );
    iterator insert( const_iterator pos, size_type count, const T& value );
    template<class InputIt, std::enable_if_t<std::is_same_v<T, typename std::iterator_traits<InputIt>::value_type>, int> = 0>
    iterator insert( const_iterator pos, InputIt first, InputIt last );
    iterator insert( const_iterator pos, std::initializer_list<T> ilist );

    // Erase
    iterator erase( iterator pos ) { return erase_impl(pos, 1); }
    iterator erase( const_iterator pos ) { return erase_impl(pos, 1); }
    iterator erase( iterator first, iterator last ) { return erase_impl(first, std::distance(first, last)); }
    iterator erase( const_iterator first, const_iterator last ) { return erase_impl(first, std::distance(first, last)); }

    // Emplace
    template<typename... Args>
    reference emplace_back( Args&&... args );
    template< class... Args >
    iterator emplace( const_iterator pos, Args&&... args );

    allocator_type get_allocator() const { return m_allocator; }

private:
    iterator erase_impl( const_iterator pos, size_type count );
    void grow(std::size_t newSize);
    void shrink();

    allocator_type m_allocator;
    T* m_data = nullptr;
    size_type m_size = 0;
    size_type m_capacity = 0;
};

template<typename T>
inline typename vector<T>::reference vector<T>::at( size_type pos )
{
    if (!(pos < size()))
        throw std::out_of_range("vector<T>::at - index is out of range.");

    return m_data[pos];
}

template<typename T>
vector<T>::~vector()
{
    clear();
    shrink();
}

template<typename T>
vector<T>& vector<T>::operator=( const vector& other )
{
    clear();
    shrink();

    insert(end(), other.begin(), other.end());
    return *this;
}

template<typename T>
inline typename vector<T>::const_reference vector<T>::at( size_type pos ) const
{
    if (!(pos < size()))
        throw std::out_of_range("vector<T>::at - index is out of range.");

    return m_data[pos];
}

template<typename T>
inline typename vector<T>::reference vector<T>::operator[]( size_type pos )
{
    return m_data[pos];
}

template<typename T>
void vector<T>::resize( size_type count )
{
    resize(count, value_type());
}

template<typename T>
void vector<T>::resize( size_type count, const value_type& value )
{
    // Nothing to do?
    if (count == size())
        return;

    if (count < size())
    {
        erase(std::prev(end(), size() - count), end());
    }
    else
    {
        insert(end(), count - size(), value);
    }
}

template<typename T>
inline void vector<T>::clear()
{
    // Just erase all elements, do not shrink the vector,
    // so the behaviour is the same as for std::vector.
    erase(begin(), end());
}

template<typename T>
inline void vector<T>::push_back( const T& item )
{
    // Ensure the array is large enough. After
    // the call, capacity() >= size() + 1. If
    // there is not enough memory, exception
    // is thrown.
    grow(size() + 1);

    // Construct item at given position, use copy constructor
    std::allocator_traits<allocator_type>::construct(m_allocator, data() + size(), item);

    // Increment size of the vector
    ++m_size;
}

template<typename T>
inline void vector<T>::push_back( T&& item )
{
    // Ensure the array is large enough. After
    // the call, capacity() >= size() + 1. If
    // there is not enough memory, exception
    // is thrown.
    grow(size() + 1);

    // Construct item at given position, use move constructor
    std::allocator_traits<allocator_type>::construct(m_allocator, data() + size(), std::move(item));

    // Increment size of the vector
    ++m_size;
}

template<typename T>
inline void vector<T>::swap( vector& other )
{
    std::swap(m_data, other.m_data);
    std::swap(m_capacity, other.m_capacity);
    std::swap(m_size, other.m_size);

    if constexpr (std::allocator_traits<allocator_type>::propagate_on_container_swap::value)
    {
        std::swap(m_allocator, other.m_allocator);
    }
}

template<typename T>
vector<T>& vector<T>::operator=(vector<T>&& other)
{
    swap(other);
    return *this;
}

template<typename T>
void vector<T>::pop_back()
{
    erase(std::prev(end()));
}

template<typename T>
typename vector<T>::iterator vector<T>::insert( const_iterator pos, const T& value )
{
    auto distance = std::distance(cbegin(), pos);
    push_back(value);
    return std::prev(std::rotate(begin() + distance, std::prev(end()), end()));
}

template<typename T>
typename vector<T>::iterator vector<T>::insert( const_iterator pos, T&& value )
{
    auto distance = std::distance(cbegin(), pos);
    push_back(std::move(value));
    return std::prev(std::rotate(begin() + distance, std::prev(end()), end()));
}

template<typename T>
typename vector<T>::iterator vector<T>::insert( const_iterator pos, size_type count, const T& value )
{
    // If we are not inserting anything, just return current iterator
    if (count == 0)
        return const_cast<iterator>(pos);

    auto distance = std::distance(cbegin(), pos);

    // Pre-allocate the memory, after we calculate
    // the distance. Keep in mind, that iterator pos
    // can be invalidated.
    grow(size() + count);

    for (size_type i = 0; i < count; ++i)
    {
        push_back(value);
    }

    std::rotate(begin() + distance, std::prev(end(), count), end());
    return std::next(begin(), distance);
}

template<typename T>
template<class InputIt, std::enable_if_t<std::is_same_v<T, typename std::iterator_traits<InputIt>::value_type>, int>>
typename vector<T>::iterator vector<T>::insert( const_iterator pos, InputIt first, InputIt last )
{
    // If we are not inserting anything, just return current iterator
    if (first == last)
        return const_cast<iterator>(pos);

    auto distance = std::distance(cbegin(), pos);
    auto count = std::distance(first, last);

    // Pre-allocate the memory, after we calculate
    // the distance. Keep in mind, that iterator pos
    // can be invalidated.
    grow(size() + count);

    for (auto it = first; it != last; ++it)
    {
        push_back(*it);
    }

    std::rotate(begin() + distance, std::prev(end(), count), end());
    return std::next(begin(), distance);
}

template<typename T>
typename vector<T>::iterator vector<T>::insert( const_iterator pos, std::initializer_list<T> ilist )
{
    return insert(pos, ilist.begin(), ilist.end());
}

template<typename T>
typename vector<T>::iterator vector<T>::erase_impl( const_iterator pos, size_type count )
{
    // Do we remove something?
    if (count == 0)
        return const_cast<iterator>(pos);

    // We rotate the erased items to the end
    auto itFirst = std::next(begin(), std::distance(cbegin(), pos));
    auto itLast = std::next(itFirst, count);
    auto it = std::rotate(itFirst, itLast, end());

    // Destroy allocated objects
    for (auto it2 = it; it2 != end(); ++it2)
        std::allocator_traits<allocator_type>::destroy(m_allocator, it2);

    // Set new size of the vector
    m_size -= count;

    return itFirst;
}

template<typename T>
void vector<T>::grow(size_t newSize)
{
    // If we have allocated enough space, do nothing
    if (newSize <= capacity())
        return;

    // If we want to allocate too much items, throw exception
    if (newSize > max_size())
        throw std::bad_alloc();

    size_type newCapacity = capacity();

    // Initialize capacity to one, if it is zero, we can
    // have zero capacity at start.
    if (newCapacity == 0)
        newCapacity = 1;

    while (newCapacity < newSize)
        newCapacity = 2 * newCapacity;

    // Now we will allocate a new array and move all elements
    // from the old array into it. We deallocate the old array.
    T* data = std::allocator_traits<allocator_type>::allocate(m_allocator, newCapacity);

    for (size_type i = 0; i < size(); ++i)
    {
        std::allocator_traits<allocator_type>::construct(m_allocator, data + i, std::move(m_data[i]));
        std::allocator_traits<allocator_type>::destroy(m_allocator, m_data + i);
    }

    std::allocator_traits<allocator_type>::deallocate(m_allocator, m_data, m_capacity);

    // Set new data. Size is not changed, only capacity.
    m_data = data;
    m_capacity = newCapacity;
}

template<typename T>
void vector<T>::shrink()
{
    size_type newCapacity = capacity();

    // Capacity and size is the same - we cannot shrink
    if (newCapacity == size())
        return;

    if (m_size == 0)
        newCapacity = 0;
    else
    {
       size_type currentCapacity = newCapacity;
       while (currentCapacity > size())
       {
           newCapacity = currentCapacity;
           currentCapacity /= 2;
       }
    }

    if (newCapacity == 0)
    {
        std::allocator_traits<allocator_type>::deallocate(m_allocator, m_data, m_capacity);
        m_data = nullptr;
        m_capacity = 0;
    }
    else
    {
        // Now we will allocate a new array and move all elements
        // from the old array into it. We deallocate the old array.
        T* data = std::allocator_traits<allocator_type>::allocate(m_allocator, newCapacity);

        for (size_type i = 0; i < size(); ++i)
        {
            std::allocator_traits<allocator_type>::construct(m_allocator, data + i, std::move(m_data[i]));
            std::allocator_traits<allocator_type>::destroy(m_allocator, m_data + i);
        }

        std::allocator_traits<allocator_type>::deallocate(m_allocator, m_data, m_capacity);

        // Set new data. Size is not changed, only capacity.
        m_data = data;
        m_capacity = newCapacity;
    }
}

template<typename T>
inline typename vector<T>::const_reference vector<T>::operator[]( size_type pos ) const
{
    return m_data[pos];
}

template<typename T>
template<typename... Args>
typename vector<T>::reference vector<T>::emplace_back( Args&&... args )
{
    // Ensure the array is large enough. After
    // the call, capacity() >= size() + 1. If
    // there is not enough memory, exception
    // is thrown.
    grow(size() + 1);

    // Construct item at given position
    std::allocator_traits<allocator_type>::construct(m_allocator, data() + size(), std::forward<Args>(args)...);

    // Increment size of the vector
    ++m_size;

    return back();
}

template<typename T>
template<typename... Args>
typename vector<T>::iterator vector<T>::emplace( const_iterator pos, Args&&... args )
{
    auto distance = std::distance(cbegin(), pos);
    emplace_back(std::forward<Args>(args)...);
    return std::prev(std::rotate(begin() + distance, std::prev(end()), end()));
}

template<typename T>
void vector<T>::assign(size_type count, const T& value)
{
    clear();
    insert(end(), count, value);
}

template<typename T>
void vector<T>::assign(std::initializer_list<T> ilist)
{
    clear();
    insert(end(), ilist.begin(), ilist.end());
}

template<typename T>
template<class InputIt, std::enable_if_t<std::is_same_v<T, typename std::iterator_traits<InputIt>::value_type>, int>>
void vector<T>::assign( InputIt first, InputIt last )
{
    clear();
    insert(end(), first, last);
}

}   // namespace course_l01

#endif // CUSTOM_ARRAY_H
