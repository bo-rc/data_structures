/**
* @file dynamic_array.tcc
* @author Bo Liu (boliu1)
* @date Summer 2015
* cs225 mp1
*/
#include "dynamic_array.h"
#include <algorithm>
#include <stdexcept>
#include <iostream>

namespace cs225
{

template <typename T>
dynamic_array<T>::dynamic_array() : arr_{nullptr}, size_{0} 
{
	/* empty */
}

template <typename T>
dynamic_array<T>::dynamic_array(uint64_t sze) : size_(sze)
{
	arr_ = new T[sze];
}

template <typename T>
dynamic_array<T>::dynamic_array(const dynamic_array &other) : size_{other.size_}
{
	arr_ = new T[size_];
	std::copy(other.arr_, other.arr_ + other.size_, arr_);
	/* for (uint64_t i = 0; i < size_; ++i)
	{
	    arr_[i] = other[i];
	}
	*/
}

template <typename T>
dynamic_array<T>::dynamic_array(dynamic_array &&other) : arr_{other.arr_}, size_{ other.size_ }
{
	other.arr_ = nullptr;
	other.size_ = 0;
}

template <typename T>
dynamic_array<T>& dynamic_array<T>::operator=(dynamic_array<T> rhs)
{
	swap(rhs);
	return *this;
}

template <typename T>
dynamic_array<T>::~dynamic_array()
{
	clear();
}

template <typename T>
void dynamic_array<T>::clear()
{
	delete[] arr_;
	arr_ = nullptr;
	size_ = 0;
}

template <typename T>
void dynamic_array<T>::swap(dynamic_array &other)
{
	using std::swap;
	swap(this->arr_, other.arr_);
	swap(this->size_, other.size_);
}

template <typename T>
void dynamic_array<T>::resize(uint64_t size)
{
    if(size == 0)
	clear();
    else
    {
    	T* tmp = new T[size];

	std::move(arr_, arr_ + (size_ > size ? size : size_), tmp);
	/* for (uint64_t i = 0; i < (size_ > size ? size : size_); ++i )
	{
	    tmp[i] = std::move(arr_[i]);
	}
	*/

	clear();
	arr_ = tmp;
	size_ = size;
	tmp = nullptr;
    }
}

template <typename T>
const T& dynamic_array<T>::operator[] (uint64_t idx) const
{
	return *(arr_ + idx);
}

template <typename T>
T& dynamic_array<T>::operator[] (uint64_t idx)
{
	return *(arr_ + idx);
}

template <typename T>
const T& dynamic_array<T>::at(uint64_t idx) const
{
	if (idx > size_)
		throw std::out_of_range("index out of bounds");
	else
		return this->operator[](idx);
}

template <typename T>
T& dynamic_array<T>::at(uint64_t idx)
{
	if (idx >= size_)
	{
	    throw std::out_of_range("index out of bounds");
	} else {
            return this->operator[](idx);
	}
}

template <typename T>
uint64_t dynamic_array<T>::size() const
{
	return size_;
}

template <typename T>
bool dynamic_array<T>::empty() const
{
	return !arr_;
}


} // namespace cs225

