/**
 * @file queue.tcc
 * @author Chase Geigle
 * @date Summer 2014
 */

#include "queue.h"

namespace cs225
{

template <class T>
const T& queue<T>::front() const
{
    return arr_[0];
}

template <class T>
T& queue<T>::front()
{
    return arr_[0];
}

template <class T>
void queue<T>::push(const T& elem)
{
    return arr_.push_back(elem);
}

template <class T>
void queue<T>::push(T&& elem)
{
    arr_.push_back(std::move(elem));
}

template <class T>
void queue<T>::pop()
{
    arr_.pop_front();
}

template <class T>
uint64_t queue<T>::size() const
{
    return arr_.size();
}

template <class T>
bool queue<T>::empty() const
{
    return arr_.empty();
}
}
