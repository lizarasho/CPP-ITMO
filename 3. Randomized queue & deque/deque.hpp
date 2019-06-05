#ifndef DEQUE_HPP
#define DEQUE_HPP

#include <list>

template<typename T>
struct deque
{
public:
    typedef typename std::list<T>::iterator iterator;

    bool empty() const;

    size_t size() const;

    void push_front(T const &x);

    void push_back(T const &x);

    const T& front() const;

    T& front();

    const T& back() const;

    T& back();

    void pop_front();

    void pop_back();

    iterator begin();

    iterator end();

private:
    std::list<T> list_;
};


template<typename T>
bool deque<T>::empty() const
{
    return list_.empty();
}

template<typename T>
size_t deque<T>::size() const
{
    return list_.size();
}

template<typename T>
void deque<T>::push_front(const T &x)
{
    list_.push_front(x);
}

template<typename T>
void deque<T>::push_back(const T &x)
{
    list_.push_back(x);
}

template<typename T>
const T& deque<T>::front() const
{
    return list_.front();
}

template<typename T>
T& deque<T>::front()
{
    return list_.front();
}

template<typename T>
const T& deque<T>::back() const
{
    return list_.back();
}

template<typename T>
T& deque<T>::back()
{
    return list_.back();
}

template<typename T>
void deque<T>::pop_front()
{
    list_.pop_front();
}

template<typename T>
void deque<T>::pop_back()
{
    list_.push_back();
}

template<typename T>
typename deque<T>::iterator deque<T>::begin()
{
    return list_.begin();
}

template<typename T>
typename deque<T>::iterator deque<T>::end()
{
    return list_.end();
}

#endif

