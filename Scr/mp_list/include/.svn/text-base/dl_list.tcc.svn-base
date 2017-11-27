/**
 * @file dl_list.tcc
 * @author Chase Geigle
 * @date Summer 2014
 */

#include <cassert>
#include <utility>
#include "dl_list.h"

namespace cs225
{

template <class T>
dl_list<T>::dl_list()
{
    /// @todo mp_list.1
}

template <class T>
dl_list<T>::dl_list(const dl_list& other)
{
    /// @todo mp_list.1
    /// hint: re-use your push_X function(s)!
}

template <class T>
dl_list<T>::dl_list(dl_list&& other)
{
    /// @todo mp_list.1
}

template <class T>
dl_list<T>& dl_list<T>::operator=(dl_list rhs)
{
    /// @todo mp_list.1
}

template <class T>
void dl_list<T>::swap(dl_list& other)
{
    /// @todo mp_list.1
}

template <class T>
void dl_list<T>::push_back(T data)
{
    /// @todo mp_list.1
}

template <class T>
void dl_list<T>::push_front(T data)
{
    /// @todo mp_list.1
}

template <class T>
void dl_list<T>::reverse()
{
    reverse(head_, tail_);
}

template <class T>
void dl_list<T>::reverse(std::unique_ptr<node>& first, node*& last)
{
    /// @todo mp_list.1
}

template <class T>
void dl_list<T>::reverse_nth(unsigned n)
{
    /// @todo mp_list.1
}

template <class T>
void dl_list<T>::waterfall()
{
    /// @todo mp_list.1
}

template <class T>
auto dl_list<T>::split(unsigned split_point) -> dl_list
{
    if (split_point >= size_)
        return {};

    if (split_point == 0)
    {
        dl_list lst;
        swap(*this);
        return lst;
    }

    auto old_size = size_;
    auto new_head = split(head_.get(), split_point);

    // set up current list
    size_ = split_point;
    for (tail_ = head_.get(); tail_->next; tail_ = tail_->next.get())
        ;

    // set up returned list
    dl_list ret;
    ret.head_ = std::move(new_head);
    for (ret.tail_ = ret.head_.get(); ret.tail_->next;
         ret.tail_ = ret.tail_->next.get())
        ;
    ret.size_ = old_size - split_point;
    return ret;
}

template <class T>
auto dl_list<T>::split(node* start, unsigned split_point)
    -> std::unique_ptr<node>
{
    assert(split_point > 0);
    /// @todo mp_list.2
}

template <class T>
void dl_list<T>::merge(dl_list& to_merge)
{
    head_ = merge(std::move(head_), std::move(to_merge.head_));

    for (tail_ = head_.get(); tail_->next; tail_ = tail_->next.get())
        ;
    size_ += to_merge.size_;

    to_merge.tail_ = nullptr;
    to_merge.size_ = 0;
}

template <class T>
auto dl_list<T>::merge(std::unique_ptr<node> first,
                       std::unique_ptr<node> second) -> std::unique_ptr<node>
{
    /// @todo mp_list.2
}

template <class T>
void dl_list<T>::sort()
{
    if (!head_)
        return;

    head_ = mergesort(std::move(head_), size_);
    for (tail_ = head_.get(); tail_->next; tail_ = tail_->next.get())
        ;
}

template <class T>
auto dl_list<T>::mergesort(std::unique_ptr<node> start, uint64_t length)
    -> std::unique_ptr<node>
{
    /// @todo mp_list.2
}
}
