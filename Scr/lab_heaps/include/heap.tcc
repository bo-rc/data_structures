/**
 * @file heap.cpp
 * Implementation of a heap class.
 */
#include <cmath>
#include <stdexcept>
#include "heap.h"

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    // Update to return the index you are choosing to be your root.
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::left_child(size_t idx) const
{
    // Update to return the index of the left child.
    return 2*idx;
}

template <class T, class Compare>
size_t heap<T, Compare>::right_child(size_t idx) const
{
    // Update to return the index of the left child.
    return 2*idx + 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t idx) const
{
    // Update to return the parent index.
    return std::floor(idx/2);
}

template <class T, class Compare>
bool heap<T, Compare>::has_child(size_t idx) const
{
    // Update to return whether the node at index has a child.
    return (2*idx <= current_size_);
}

template <class T, class Compare>
size_t heap<T, Compare>::max_priority_child(size_t idx) const
{
    // Update to return the index of the child with highest priority
    // as defined by higherPriority()
    if (!has_child(idx))
        throw std::runtime_error("this node has no children");

    // left = left_child(idx);
    // right = right_child(idx);
    size_t left = 2*idx;
    size_t right = 2*idx + 1;

    return higher_priority_(elems_[left], elems_[right])? left : right;
}

template <class T, class Compare>
void heap<T, Compare>::heapify_down(size_t idx)
{
    // Implement the heapifyDown algorithm.
    size_t child;
    T tmp = std::move(elems_[idx]);

    for(; (idx * 2) <= current_size_; idx = child)
    {
        child = idx * 2;
        if(child != current_size_ && higher_priority_(elems_[child + 1], elems_[child]))
            ++child;
        if(higher_priority_(elems_[child], tmp))
            elems_[idx] = std::move(elems_[child]);
        else
            break;
    }
    elems_[idx] = std::move(tmp);

}

template <class T, class Compare>
void heap<T, Compare>::heapify_up(size_t idx)
{
    if (idx == root())
        return;
    size_t parentIdx = parent(idx);
    if (higher_priority_(elems_[idx], elems_[parentIdx]))
    {
        std::swap(elems_[idx], elems_[parentIdx]);
        heapify_up(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap(size_t capacity)
    : elems_(capacity + 1), current_size_{0}
{
    // nothing to do
    //std::cout << "size of elems_ = " << elems_.size() << std::endl;
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems)
    : elems_(elems.size() + 1), current_size_{elems.size()}
{
    // Construct a heap using the buildHeap algorithm
    for(size_t i = 0; i < current_size_; ++i)
    {
        elems_[i + 1] = elems[i];
    }
    buildHeap();
}

template <class T, class Compare>
void heap<T, Compare>::pop()
{
    // Remove the element with the highest priority.
    if (empty())
        throw std::underflow_error("pop() called but the heap is empty");

    elems_[1] = std::move(elems_[current_size_--]);
    elems_.pop_back();
    heapify_down(1);
}

template <class T, class Compare>
const T& heap<T, Compare>::peek() const
{
    // Return the element with the highest priority (do *not* remove!)
    return elems_[1];
}

template <class T, class Compare>
void heap<T, Compare>::push(T elem)
{
    // Add an element to the heap
    elems_.emplace_back(elem);
    size_t hole = ++current_size_;

    for(; hole > 1 && higher_priority_(elem, elems_[hole/2]); hole /= 2)
        elems_[hole] = std::move(elems_[hole/2]);
    elems_[hole] = std::move(elem);
}

template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    // Determine if the heap is empty
    return (current_size_ == 0);
}

template <class T, class Compare>
void heap<T, Compare>::buildHeap()
{
    for (int i = current_size_ / 2; i > 0; --i)
        heapify_down(i);
}

//template <class Type, class Comp>
//std::ostream& operator<<(std::ostream& out,
//                         const heap<Type, Comp>& toPrint)
//{
//    out << "[";
//    for(size_t i = 1; i < toPrint.current_size_; ++i)
//        out << " " << (toPrint.elems_)[i];

//    out << " ]" << std::endl << std::endl;
//    return out;
//}
