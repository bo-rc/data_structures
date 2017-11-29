#ifndef DSETS_H
#define DSETS_H

#include <cstdint>
#include <vector>

/**
 * @brief The dsets class: implement union-find with union by size and path compression
 * m union + find takes O(mlog*(n)) time.
 * @author Bo Liu
 */
class dsets
{
public:
    using nElements = uintmax_t;
    using element = uintmax_t;

    /*
     * negative leader means this leader is a root,
     * the magnitude means nElements this root leads
     */
    using leader = intmax_t;
    using root = element;

    dsets() = delete;
    dsets(nElements num);
    root find(element a);
    void unify(element a, element b);
private:
    std::vector<leader> arr_;
};

#endif // DSETS_H
