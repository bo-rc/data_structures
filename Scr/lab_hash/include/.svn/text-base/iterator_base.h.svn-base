#ifndef ITERATOR_BASE_
#define ITERATOR_BASE_

#include <iterator>
#include <type_traits>

namespace cs225
{
/// \cond STAFF

/**
 * A CRTP base class for more easily creating iterators.
 */
template <class Category, class Value, class Iterator>
class iterator_base : public std::iterator<Category, Value>
{
  public:
    template <class Cat = Category>
    typename std::enable_if<
        std::is_base_of<std::input_iterator_tag, Cat>::value, Iterator&>::type
        operator++()
    {
        static_assert(std::is_same<Cat, Category>::value,
                      "no explicit specialization");
        self()->increment();
        return *self();
    }

    template <class Cat = Category>
    typename std::enable_if<
        std::is_base_of<std::input_iterator_tag, Cat>::value, Iterator>::type
        operator++(int)
    {
        static_assert(std::is_same<Cat, Category>::value,
                      "no explicit specialization");
        auto temp = *self();
        self()->increment();
        return temp;
    }

    template <class Cat = Category>
    typename std::enable_if<
        std::is_base_of<std::bidirectional_iterator_tag, Cat>::value,
        Iterator&>::type
        operator--()
    {
        static_assert(std::is_same<Cat, Category>::value,
                      "no explicit specialization");
        self()->decrement();
        return *self();
    }

    template <class Cat = Category>
    typename std::enable_if<
        std::is_base_of<std::bidirectional_iterator_tag, Cat>::value,
        Iterator&>::type
        operator--(int)
    {
        static_assert(std::is_same<Cat, Category>::value,
                      "no explicit specialization");
        auto temp = *self();
        self()->decrement();
        return temp;
    }

    template <class Cat = Category>
    typename std::enable_if<
        std::is_base_of<std::random_access_iterator_tag, Cat>::value,
        Iterator&>::type
        operator+=(typename std::iterator<Cat, Value>::difference_type diff)
    {
        static_assert(std::is_same<Cat, Category>::value,
                      "no explicit specialization");
        self()->advance(diff);
        return *self();
    }

    template <class Cat = Category>
    typename std::enable_if<
        std::is_base_of<std::random_access_iterator_tag, Cat>::value,
        Iterator>::type
        operator+(typename std::iterator<Cat, Value>::difference_type diff)
    {
        static_assert(std::is_same<Cat, Category>::value,
                      "no explicit specialization");
        auto temp = *self();
        return temp += diff;
    }

    template <class Cat = Category>
    typename std::enable_if<
        std::is_base_of<std::random_access_iterator_tag, Cat>::value,
        Iterator&>::type
        operator-=(typename std::iterator<Cat, Value>::difference_type diff)
    {
        static_assert(std::is_same<Cat, Category>::value,
                      "no explicit specialization");
        self()->advance(-diff);
        return *self();
    }

    template <class Cat = Category>
    typename std::enable_if<
        std::is_base_of<std::random_access_iterator_tag, Cat>::value,
        Iterator>::type
        operator-(typename std::iterator<Cat, Value>::difference_type diff)
    {
        auto temp = *self();
        return temp -= diff;
    }

    template <class Cat = Category>
    typename std::enable_if<
        std::is_base_of<std::random_access_iterator_tag, Cat>::value,
        typename std::iterator<Cat, Value>::difference_type>::type
        operator-(const Iterator& other)
    {
        return self()->distance(other);
    }

    template <class Cat = Category>
    typename std::enable_if<
        std::is_base_of<std::random_access_iterator_tag, Cat>::value,
        const Value&>::type
        operator[](typename std::iterator<Cat, Value>::difference_type diff)
        const
    {
        return *(*self() + diff);
    }

    template <class Cat = Category>
    typename std::enable_if<
        std::is_base_of<std::random_access_iterator_tag, Cat>::value,
        Value&>::type
        operator[](typename std::iterator<Cat, Value>::difference_type diff)
    {
        return *(*self() + diff);
    }

    const Value* operator->() const
    {
        return &self()->dereference();
    }

    const Value& operator*() const
    {
        return self()->dereference();
    }

    Value* operator->()
    {
        return &self()->dereference();
    }

    Value& operator*()
    {
        return self()->dereference();
    }

    friend inline bool operator==(const iterator_base& lhs,
                                  const iterator_base& rhs)
    {
        return lhs.self()->equal(*rhs.self());
    }

    friend inline bool operator!=(const iterator_base& lhs,
                                  const iterator_base& rhs)
    {
        return !(lhs == rhs);
    }

  private:
    inline Iterator* self()
    {
        return static_cast<Iterator*>(this);
    }

    inline const Iterator* self() const
    {
        return static_cast<const Iterator*>(this);
    }
};
/// \endcond
}
#endif
