#include "dsets.h"


dsets::dsets(dsets::nElements num)
{
    arr_.reserve(num);
    for (size_t i = 0; i != num; ++i)
    {
        arr_.emplace_back(-1);
    }
}

dsets::root dsets::find(dsets::element a)
{
    if (arr_[a] < 0)
        return a;

    // path compression
    return arr_[a] = find(arr_[a]);
}

void dsets::unify(dsets::element a, dsets::element b)
{
    auto root_a = find(a);
    auto root_b = find(b);

    if (root_a == root_b)
        return;

    if (arr_[root_a] < arr_[root_b])
    {
        // root_a leads more elements
        arr_[root_a] += arr_[root_b];
        arr_[root_b] = root_a;
    }
    else
    {
        arr_[root_b] += arr_[root_a];
        arr_[root_a] = root_b;
    }
}
