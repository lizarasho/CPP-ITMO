#ifndef RANDOMIZED_QUEUE_HPP
#define RANDOMIZED_QUEUE_HPP

#include <vector>
#include <random>

template<typename T>
struct queue_iterator;

template<typename T>
struct randomized_queue
{
public:
    typedef queue_iterator<T> iterator;

    bool empty() const;

    size_t size() const;

    const T& sample() const;

    T& sample();

    void enqueue(T const &x);

    T& dequeue();

    iterator begin();

    iterator end();

private:
    std::vector<T> base_;
    friend struct queue_iterator<T>;
};

template<typename T>
bool randomized_queue<T>::empty() const
{
    return size() == 0;
}

template<typename T>
const T& randomized_queue<T>::sample() const
{
    std::random_device rd;
    std::mt19937 g(rd());
    return base_[g() % size()];
}

template<typename T>
size_t randomized_queue<T>::size() const
{
    return base_.size();
}

template<typename T>
void randomized_queue<T>::enqueue(const T &x)
{
    base_.push_back(x);
}

template<typename T>
T& randomized_queue<T>::sample()
{
    std::random_device rd;
    std::mt19937 g(rd());
    return base_[g() % size()];
}

template<typename T>
T& randomized_queue<T>::dequeue()
{
    std::random_device rd;
    std::mt19937 g(rd());
    size_t ind = g() % size();
    std::swap(base_[ind], base_.back());
    T result = base_.back();
    base_.pop_back();
    return result;
}

template<typename T>
typename randomized_queue<T>::iterator randomized_queue<T>::begin()
{
    return iterator(this, 0);
}

template<typename T>
typename randomized_queue<T>::iterator randomized_queue<T>::end()
{
    return iterator(this, size());
}


template<typename T>
struct queue_iterator
{
public:
    queue_iterator(randomized_queue<T> *, size_t);

    T &operator*();

    queue_iterator<T> &operator++();

    queue_iterator<T> &operator--();

    queue_iterator<T> operator++(int);

    queue_iterator<T> operator--(int);

    bool operator==(queue_iterator<T> const &);

    bool operator!=(queue_iterator<T> const &);

private:
    size_t pos_;
    std::vector<size_t> permutation_;
    randomized_queue<T> *queue_;
};

template<typename T>
queue_iterator<T>::queue_iterator(randomized_queue<T> *queue,
        size_t const pos) : queue_(queue), pos_(pos)
{
    permutation_.resize(queue->size());
    for (size_t i = 0; i < queue->size(); i++)
        permutation_[i] = i;
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(permutation_.begin(), permutation_.end(), g);
    permutation_.push_back(queue->size());
}

template<typename T>
T &queue_iterator<T>::operator*()
{
    return queue_->base_[permutation_[pos_]];
}

template<typename T>
queue_iterator<T> &queue_iterator<T>::operator++()
{
    pos_++;
    return *this;
}

template<typename T>
queue_iterator<T> &queue_iterator<T>::operator--()
{
    pos_--;
    return *this;
}

template<typename T>
queue_iterator<T> queue_iterator<T>::operator++(int)
{
    queue_iterator<T> it = *this;
    ++*this;
    return it;
}

template<typename T>
queue_iterator<T> queue_iterator<T>::operator--(int)
{
    queue_iterator<T> it = *this;
    --*this;
    return it;
}

template<typename T>
bool queue_iterator<T>::operator==(queue_iterator<T> const &it)
{
    if (pos_ == queue_->size())
        return pos_ == it.pos_ && queue_ == it.queue_;
    return pos_ == it.pos_ && queue_ == it.queue_ && permutation_ == it.permutation_;
}

template<typename T>
bool queue_iterator<T>::operator!=(queue_iterator<T> const &it)
{
    return !(*this == it);
}

#endif