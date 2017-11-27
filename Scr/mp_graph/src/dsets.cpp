#include "dsets.h"

namespace cs225 {

void dsets::add_elements (uint64_t num)
{
    arr_.reserve(num);
    for (size_t i = 0; i < num; ++i)
    {
        arr_.emplace_back(-1);
    }
}

uint64_t dsets::find(uint64_t elem)
{
    if(arr_[elem] < 0)
        return elem;
    return find(arr_[elem]);
}

void dsets::merge (uint64_t a, uint64_t b)
{
    auto root1 = find(a);
    auto root2 = find(b);

    if (root1 == root2)
        return;

    if(arr_[root1] <= arr_[root2])
    {
        arr_[root1] += arr_[root2];
        arr_[root2] = root1;
    }
    else
    {
        arr_[root2] += arr_[root1];
        arr_[root1] = root2;
    }

}

}
