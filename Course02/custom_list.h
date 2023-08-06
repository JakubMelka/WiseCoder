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

#ifndef CUSTOM_LIST_H
#define CUSTOM_LIST_H

#include <iterator>

namespace course_l01
{

template<typename T>
class list
{
private:
    struct _node;

public:
    // Type declarations
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;

    list() = default;
    explicit list( size_type count ) { resize(count); }
    template< class InputIt >
    list( InputIt first, InputIt last ) { insert(end(), first, last); }
    list( const list& other ) { insert(end(), other.begin(), other.end()); }
    list( list&& other ) { swap(other); }
    list( std::initializer_list<T> init ) { insert(end(), init.begin(), init.end()); }
    ~list() { clear(); }

    // Assignment operator
    list& operator=( const list& other ) { clear(); insert(end(), other.begin(), other.end()); return *this; }
    list& operator=( list&& other ) { swap(other); return *this; }

    // Assign methods
    void assign( size_type count, const T& value ) { clear(); insert(end(), count, value); }
    template< class InputIt, std::enable_if_t<std::is_same_v<T, typename std::iterator_traits<InputIt>::value_type>, int> = 0 >
    void assign( InputIt first, InputIt last ) { clear(); insert(end(), first, last); }
    void assign( std::initializer_list<T> ilist ) { assign(ilist.begin(), ilist.end()); }

    template<typename Value>
    class _iterator
    {
    public:
        using value_type = Value;
        using reference = Value&;
        using pointer = Value*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::bidirectional_iterator_tag;

        _iterator(const list* myList, _node* node) : m_list(myList), m_node(node) {}

        reference operator*() const { return m_node->value; }
        pointer operator->() const { return &m_node->value; }
        _iterator& operator++() { m_node = m_node->next; return *this; }
        _iterator operator++(int) { _iterator temp = *this; ++(*this); return temp; }
        _iterator& operator--() { m_node = m_node ? m_node->prev : m_list->m_tail; return *this; }
        _iterator operator--(int) { _iterator temp = *this; --(*this); return temp; }

        bool operator==(const _iterator& other) const { return m_node == other.m_node; }
        bool operator!=(const _iterator& other) const { return !(*this == other); }

        operator _iterator<const T>() const { return _iterator<const T>(m_list, m_node); }

    private:
        friend class list;

        const list* m_list = nullptr;
        _node* m_node = nullptr;
    };

    using iterator = _iterator<value_type>;
    using const_iterator = _iterator<const value_type>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    // Element access

    reference front() noexcept { return m_head->value; }
    const_reference front() const noexcept { return m_head->value; }

    reference back() noexcept { return m_tail->value; }
    const_reference back() const noexcept { return m_tail->value; }

    // Iterators

    iterator begin() noexcept { return iterator(this, m_head); }
    const_iterator begin() const noexcept { return const_iterator(this, m_head); }
    const_iterator cbegin() const noexcept { return const_iterator(this, m_head); }

    iterator end() noexcept { return iterator(this, nullptr); }
    const_iterator end() const noexcept { return const_iterator(this, nullptr); }
    const_iterator cend() const noexcept { return const_iterator(this, nullptr); }

    reverse_iterator rbegin() noexcept { return std::make_reverse_iterator(end()); }
    const_reverse_iterator rbegin() const noexcept { return std::make_reverse_iterator(end()); }
    const_reverse_iterator crbegin() const noexcept { return std::make_reverse_iterator(cend()); }

    reverse_iterator rend() noexcept { return std::make_reverse_iterator(begin()); }
    const_reverse_iterator rend() const noexcept { return std::make_reverse_iterator(begin()); }
    const_reverse_iterator crend() const noexcept { return std::make_reverse_iterator(cbegin()); }

    // Capacity methods
    constexpr bool empty() const noexcept { return m_head == nullptr; }
    constexpr size_type size() const noexcept { return m_size; }
    constexpr size_type max_size() const noexcept { return static_cast<size_type>(-1) / sizeof(_node); }

    // Modifiers
    void clear() { erase(begin(), end()); }
    void swap( list& other );

    void push_back( const value_type& item ) { insert_impl(end(), construct(item)); }
    void push_back( value_type&& item ) { insert_impl(end(), construct(std::move(item))); }
    void push_front( const value_type& item ) { insert_impl(begin(), construct(item)); }
    void push_front( value_type&& item ) { insert_impl(begin(), construct(std::move(item))); }

    void pop_front() { erase(begin()); }
    void pop_back() { erase(std::prev(end())); }

    void resize( size_type count ) { resize(count, value_type()); }
    void resize( size_type count, const value_type& value );

    // Insert
    iterator insert( const_iterator pos, const T& value ) { return insert_impl(pos, construct(value)); }
    iterator insert( const_iterator pos, T&& value ) { return insert_impl(pos, construct(std::move(value))); }
    iterator insert( const_iterator pos, size_type count, const T& value );
    template<class InputIt, std::enable_if_t<std::is_same_v<T, typename std::remove_const<typename std::iterator_traits<InputIt>::value_type>::type>, int> = 0>
    iterator insert( const_iterator pos, InputIt first, InputIt last );
    iterator insert( const_iterator pos, std::initializer_list<T> ilist ) { return insert(pos, ilist.begin(), ilist.end()); }

    // Erase
    iterator erase( iterator pos ) { return erase_impl(pos, 1); }
    iterator erase( const_iterator pos ) { return erase_impl(pos, 1); }
    iterator erase( iterator first, iterator last ) { return erase_impl(first, std::distance(first, last)); }
    iterator erase( const_iterator first, const_iterator last ) { return erase_impl(first, std::distance(first, last)); }

    // Emplace
    template<typename... Args>
    reference emplace_back( Args&&... args ) { return *emplace(end(), std::forward<Args...>(args...)); }
    template<typename... Args>
    reference emplace_front( Args&&... args ) { return *emplace(begin(), std::forward<Args...>(args...)); }
    template< class... Args >
    iterator emplace( const_iterator pos, Args&&... args ) { return insert_impl(pos, new _node(std::forward<Args...>(args...))); }

    // Splice
    void splice( const_iterator pos, list& other) { splice_impl(pos, other); }
    void splice( const_iterator pos, list&& other) { splice_impl(pos, other); }
    void splice( const_iterator pos, list& other, const_iterator it ) { splice_impl(pos, other, it); }
    void splice( const_iterator pos, list&& other, const_iterator it ) { splice_impl(pos, other, it); }
    void splice( const_iterator pos, list& other, const_iterator it1, const_iterator it2 ) { splice_impl(pos, other, it1, it2); }
    void splice( const_iterator pos, list&& other, const_iterator it1, const_iterator it2 ) { splice_impl(pos, other, it1, it2); }

    // Merge
    void merge( list& other ) { merge(other, std::less<T>()); }
    void merge( list&& other ) { merge(other, std::less<T>()); }
    template<typename Comparator>
    void merge( list& other, Comparator comp ) { merge_impl(other, comp); }
    template<typename Comparator>
    void merge( list&& other, Comparator comp ) { merge_impl(other, comp); }

    // Sort
    void sort() { sort(std::less<T>()); }
    template<typename Comparator>
    void sort( Comparator comp );

    // Remove
    size_type remove( const T& value ) { return remove_impl([&value](const T& v) { return v == value; }); }
    template<typename UnaryPredicate>
    size_type remove( UnaryPredicate comp ) { return remove_impl(comp); }

    // Reverse
    void reverse();

    // Unique
    size_type unique() { return unique([](const auto& l, const auto& r) { return l == r; }); }
    template< class BinaryPredicate >
    size_type unique( BinaryPredicate p );

private:

    struct _node
    {
        _node() = default;
        template<typename... Args>
        _node( Args&&... args ) : value(std::forward<Args...>(args)...), prev(nullptr), next(nullptr) { }

        T value;
        _node* prev = nullptr;
        _node* next = nullptr;
    };

    template<typename Value>
    _node* construct(Value&& value) { return new _node(std::forward<Value>(value)); }

    iterator insert_impl(const_iterator pos, _node* newItem);
    iterator erase_impl( const_iterator pos, size_type count );
    void splice_impl( const_iterator pos, list& other);
    void splice_impl(const_iterator pos, list& other, const_iterator it );
    void splice_impl(const_iterator pos, list& other, const_iterator it1, const_iterator it2 );
    _node* extract_node( const_iterator pos );
    iterator unconst_iterator( const_iterator it ) { return iterator(this, it.m_node); }

    template<typename Comparator>
    void merge_impl( list& other, Comparator comp );

    template<typename UnaryPredicate>
    size_type remove_impl( UnaryPredicate comp );

    _node* m_head = nullptr;
    _node* m_tail = nullptr;
    size_t m_size = 0;
};

template<typename T>
void list<T>::swap( list<T>& other )
{
    std::swap(m_head, other.m_head);
    std::swap(m_tail, other.m_tail);
    std::swap(m_size, other.m_size);
}

template<typename T>
void list<T>::resize( size_type count, const value_type& value )
{
    if (count < size())
    {
        erase(std::prev(end(), size() - count), end());
    }
    else if (count > size())
    {
        insert(end(), count - size(), value);
    }
}

template<typename T>
typename list<T>::iterator list<T>::insert( const_iterator pos, size_type count, const T& value )
{
    for (size_type i = 0; i < count; ++i)
    {
        pos = insert(pos, value);
    }

    return unconst_iterator(pos);
}

template<typename T>
template<class InputIt, std::enable_if_t<std::is_same_v<T, typename std::remove_const<typename std::iterator_traits<InputIt>::value_type>::type>, int>>
typename list<T>::iterator list<T>::insert( const_iterator pos, InputIt first, InputIt last )
{
    auto it = std::make_reverse_iterator(last);
    auto itEnd = std::make_reverse_iterator(first);

    while (it != itEnd)
    {
        pos = insert(pos, *it++);
    }

    return unconst_iterator(pos);
}

template<typename T>
void list<T>::reverse()
{
    _node* node = m_head;
    while (node)
    {
        std::swap(node->prev, node->next);
        node = node->prev;
    }

    std::swap(m_head, m_tail);
}

template<typename T>
typename list<T>::iterator list<T>::insert_impl(const_iterator pos, _node* newItem)
{
    _node* prev = (pos == end()) ? m_tail : pos.m_node->prev;
    _node* next = (pos == end()) ? nullptr : pos.m_node;

    // Adjust the pointer to the previous item
    newItem->prev = prev;
    if (prev)
    {
        prev->next = newItem;
    }

    // Adjust the pointer to the next item
    newItem->next = next;
    if (next)
    {
        next->prev = newItem;
    }

    // Update the tail pointer
    if (prev == m_tail)
    {
        m_tail = newItem;
    }

    // Update the head pointer
    if (next == m_head)
    {
        m_head = newItem;
    }

    ++m_size;
    return iterator(this, newItem);
}

template<typename T>
typename list<T>::iterator list<T>::erase_impl(const_iterator pos, size_type count)
{
    for (size_t i = 0; i < count ; ++i)
    {
        const_iterator it = pos++;
        _node* node = extract_node(it);
        delete node;
    }

    return unconst_iterator(pos);
}

template<typename T>
void list<T>::splice_impl( const_iterator pos, list& other )
{
    while (!other.empty())
    {
        _node* node = other.extract_node(other.begin());
        insert_impl(pos, node);
    }
}

template<typename T>
void list<T>::splice_impl(const_iterator pos, list& other, const_iterator it)
{
    if (it == other.end())
        return;

    _node* node = other.extract_node(it);
    insert_impl(pos, node);
}

template<typename T>
void list<T>::splice_impl(const_iterator pos, list& other, const_iterator it1, const_iterator it2)
{
    while (it1 != it2)
    {
        const_iterator it = it1++;
        _node* node = other.extract_node(it);
        insert_impl(pos, node);
    }
}

template<typename T>
typename list<T>::_node* list<T>::extract_node( const_iterator pos )
{
    _node* node = pos.m_node;

    // Adjust the next node's pointer to the previous node
    if (node->prev)
    {
        node->prev->next = node->next;
    }

    // Adjust the previous node's pointer to the next node
    if (node->next)
    {
        node->next->prev = node->prev;
    }

    // If the node is the head, then set the head pointer
    // to the next node (we are deleting from the start)
    if (m_head == node)
    {
        m_head = node->next;
    }

    // If the node is the tail, then set the tail pointer
    // to the previous node (we are deleting from the end)
    if (m_tail == node)
    {
        m_tail = node->prev;
    }

    --m_size;

    return node;
}

template<typename T>
template<typename Comparator>
void list<T>::sort( Comparator comp )
{
    if (empty() || size() < 2)
        return;

    list<T> l1;
    list<T> l2;

    bool swap = false;
    while (!empty())
    {
        if (swap)
        {
            l2.splice(l2.end(), *this, begin());
        }
        else
        {
            l1.splice(l2.end(), *this, begin());
        }

        swap = !swap;
    }

    l1.sort(comp);
    l2.sort(comp);

    *this = std::move(l1);
    merge(l2);
}

template<typename T>
template<typename Comparator>
void list<T>::merge_impl( list& other, Comparator comp )
{
    list result;

    while (!empty() && !other.empty())
    {
        if (comp(front(), other.front()))
        {
            result.splice(result.end(), *this, begin());
        }
        else
        {
            result.splice(result.end(), other, other.begin());
        }
    }

    result.splice(result.end(), *this);
    result.splice(result.end(), other);

    splice(end(), result);
}

template<typename T>
template<typename UnaryPredicate>
typename list<T>::size_type list<T>::remove_impl( UnaryPredicate comp )
{
    size_type removedItems = 0;

    for (auto it = begin(); it != end();)
    {
        if (comp(*it))
        {
            it = erase(it);
            ++removedItems;
        }
        else
        {
            ++it;
        }
    }

    return removedItems;
}

template<typename T>
template<class BinaryPredicate>
typename list<T>::size_type list<T>::unique( BinaryPredicate p )
{
    if (empty())
        return 0;

    size_type removedItems = 0;

    for (auto it = std::next(begin()); it != end();)
    {
        if (p(*std::prev(it), *it))
        {
            it = erase(it);
            ++removedItems;
        }
        else
        {
            ++it;
        }
    }

    return removedItems;
}

} // namespace course_l01

#endif // CUSTOM_LIST_H
