/**
 * @file circ_array.h
 * @author Chase Geigle
 * @date Summer 2014
 */

#include <stdexcept>
#include "circ_array.h"
#include <algorithm>

namespace cs225
{

template <class T>
circ_array<T>::circ_array()
    : arr_{nullptr}, capacity_{0}, idx0_{0}, size_{0}
{
    /* empty */
}

template <class T>
circ_array<T>::circ_array(uint64_t capacity)
    : arr_{new T[capacity]},
      capacity_{capacity}, idx0_{0}, size_{capacity}
{
    for (uint64_t i = 0; i < size_; ++i)
    {
        arr_[i] = T{};
    }
}

template <class T>
circ_array<T>::circ_array(const circ_array& other)
    : arr_{new T[other.capacity_]},
      capacity_{other.capacity_},
      idx0_{0}, size_{other.size_}
{
    for (decltype(circ_array::capacity_) i = 0; i < capacity_; i++ )
    {
        arr_[i] = other[i];
    }
}

template <class T>
circ_array<T>::circ_array(circ_array&& other)
    : arr_{other.arr_.release()},
      capacity_{other.capacity_},
      idx0_{other.idx0_}, size_{other.size_}
{
    /* empty */
}

template <class T>
circ_array<T>& circ_array<T>::operator=(circ_array rhs)
{
    this->swap(rhs);
    return *this;
}

template <class T>
circ_array<T>& circ_array<T>::operator=(circ_array&& rhs)
{
    arr_ = std::move(rhs.arr_);
    capacity_ = std::move(rhs.capacity_);
    idx0_ = std::move(rhs.idx0_);
    size_ = std::move(rhs.size_);
    return *this;
}

template <class T>
circ_array<T>::~circ_array() = default;

template <class T>
void circ_array<T>::swap(circ_array& other)
{
    arr_.swap(other.arr_);
    std::swap(idx0_, other.idx0_);
    std::swap(size_, other.size_);
}

template <class T>
const T& circ_array<T>::operator[](uint64_t idx) const
{
    return arr_[pos(idx)];
}

template <class T>
T& circ_array<T>::operator[](uint64_t idx)
{
    return arr_[pos(idx)];
}

template <class T>
const T& circ_array<T>::at(uint64_t idx) const
{
    if(!(idx < size_))
        throw std::out_of_range("index out of boundary");
    return this->operator[](idx);
}

template <class T>
T& circ_array<T>::at(uint64_t idx)
{
    if(!(idx < size_))
        throw std::out_of_range("index out of boundary");
    return this->operator[](idx);
}

template <class T>
void circ_array<T>::push_front(T elem)
{
    add(0, std::move(elem));
}

template <class T>
void circ_array<T>::push_back(T elem)
{
    add(size_, std::move(elem));
}

template <class T>
void circ_array<T>::pop_front()
{
    remove(0);
}

template <class T>
void circ_array<T>::pop_back()
{
    remove(size_ - 1);
}

template <class T>
void circ_array<T>::erase(uint64_t idx)
{
    remove(idx);
}

template <class T>
uint64_t circ_array<T>::size() const
{
    return size_;
}

template <class T>
bool circ_array<T>::empty() const
{
    return !size_;
}

template <class T>
void circ_array<T>::resize()
{
    auto circ_array_copy(*this);
    auto new_capacity = std::max(uint64_t(1), (2*size_));

    arr_.reset(new T[new_capacity]);
    for (uint64_t i = 0; i < size_; ++i)
    {
        arr_[i] = std::move(circ_array_copy.operator[](i)); // new idx0_ = 0
    }

    capacity_ = new_capacity;
    idx0_ = 0;
    // size_ not changed in resize();

}

template <class T>
void circ_array<T>::add(int idx, T elem)
{
    if (size_ + 1 > capacity_)
        resize();
    if (uint64_t(idx) < size_/2)
    {
        idx0_ = (idx0_ == 0) ? capacity_ - 1 : (idx0_ - 1);
        ++size_;
        for (int i = 0; i < int(idx); ++i)
        {
            arr_[pos(i)] = std::move(arr_[pos(i+1)]);
        }
    }
    else
    {
        ++size_;
        for (int i = size_ - 1; i > int(idx); --i)
        {
            arr_[pos(i)] = std::move(arr_[pos(i-1)]);
        }
    }
    arr_[pos(idx)] = std::move(elem);
}

template <class T>
T circ_array<T>::remove(int idx)
{
    T x = arr_[pos(idx)];
    if (uint64_t(idx) < size_/2)
    {
        for (int i = idx; i > 0; --i)
        {
            arr_[pos(i)] = arr_[pos(i - 1)];
        }
        idx0_ = pos(1);
    }
    else
    {
        for (int i = idx; i < int(size_ - 1); ++i)
        {
            arr_[pos(i)] = arr_[pos(i + 1)];
        }
    }
    --size_;
    if (3*size_ < capacity_)
        resize();
    return x;
}

template <class T>
int circ_array<T>::pos(int idx) const
{
    if (capacity_ == 0)
        throw std::runtime_error("capacity is zero");
    return (idx0_ + idx)%capacity_;
}

} // end namespace

