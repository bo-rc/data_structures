/**
 * @file kdtree.tcc
 * Implementation of kd_tree class.
 */

#include "kdtree.h"
#include <cmath>
#include <algorithm>
#include <functional>

template <int Dim>
bool kd_tree<Dim>::smaller_in_dimension(const point<Dim>& first,
                                       const point<Dim>& second,
                                       int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if (first[curDim] == second[curDim])
        return first < second;
    else
        return first[curDim] < second[curDim];
}

template <int Dim>
bool kd_tree<Dim>::should_replace(const point<Dim>& target,
                                 const point<Dim>& current_best,
                                 const point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */

    if (distance(target, current_best) == distance(target, potential))
    {
        return potential < current_best;
    }
    else
    {
        return distance(target, potential) < distance(target, current_best);
    }

}

// helper for should_replace
template <int Dim>
size_t kd_tree<Dim>::distance(const point<Dim>& target, const point<Dim>& current) const
{
    size_t square_sum = 0;
    for (size_t dim = 0; dim < Dim; ++dim)
    {
        square_sum += std::pow(target[dim] - current[dim], 2);
    }

    return std::sqrt(square_sum);
}

template <int Dim>
kd_tree<Dim>::kd_tree(const std::vector<point<Dim>>& newpoints)
{
    /**
     * @todo Implement this function!
     */

    points.reserve(newpoints.size());
    for (size_t i = 0; i < newpoints.size(); ++i)
    {
        points.push_back(newpoints[i]);
    }

    if (points.size() != 0)
    {
        size_t sorting_dim = 0;

        build_tree(points.begin(), points.end(), sorting_dim);
    }
}

template <int Dim>
void kd_tree<Dim>::build_tree(typename std::vector<point<Dim>>::iterator it_points_begin,
                typename std::vector<point<Dim>>::iterator it_points_end,
                size_t sorting_dim)
{
    if (it_points_begin == it_points_end)
    {
        return;
    }

//    std::cout << "before sorting: ";
//    for (auto it = it_points_begin; it != it_points_end; ++it)
//        std::cout << *it << ", ";
//    std::cout << std::endl;

    auto mid = (std::distance(it_points_begin, it_points_end) - 1)/2; // check
    auto median = quick_select(it_points_begin, it_points_end, mid, sorting_dim);

//    std::cout << "after sorting: ";
//    for (auto it = it_points_begin; it != it_points_end; ++it)
//        std::cout << *it << ", ";
//    std::cout << std::endl;

//    std::cout << "median = " << mid << std::endl;
//    std::cout << "Placing median: " << *median << std::endl;

    sorting_dim = (++sorting_dim) % Dim;

    build_tree(it_points_begin, median, sorting_dim);

    build_tree(median + 1, it_points_end, sorting_dim);
}

template <int Dim>
point<Dim> kd_tree<Dim>::find_nearest_neighbor(const point<Dim>& query) const
{
    auto points_copy = points;
    auto it_begin = points_copy.begin();
    auto it_end = points_copy.end();
    point<Dim> best;

    size_t sorting_dim = 0;
    find_nearest_neighbor_kdtree(query, best, it_begin, it_end, sorting_dim);
//    std::cout << "nearest neighbor: " << best << std::endl;
    return best;
}

template <int Dim>
void kd_tree<Dim>::find_nearest_neighbor_kdtree(const point<Dim>& query, point<Dim>& best,
                                    typename std::vector<point<Dim>>::iterator& it_begin,
                                    typename std::vector<point<Dim>>::iterator& it_end, size_t sorting_dim) const
{
//    std::cout << std::endl;
//    std::cout << "Debug: subtree = ";
//    for (auto it = it_begin; it < it_end; ++it)
//    {
//        std::cout << *it << ", ";
//    }
//    std::cout << std::endl;



    auto it_median = it_begin + (std::distance(it_begin, it_end) - 1)/2;

    if (std::distance(it_begin, it_end) <= 1)
    {
        auto potential = *it_median;
        if (should_replace(query, best, potential))
            best = potential;

//        std::cout << "$ " << best << " $"<< std::endl;
        return;
    }

    if (query[sorting_dim] < (*it_median)[sorting_dim] ||
            (query[sorting_dim] == (*it_median)[sorting_dim] && query <= *it_median))
    {
        sorting_dim = (++sorting_dim) % Dim; // down a level
        find_nearest_neighbor_kdtree(query, best, it_begin, it_median, sorting_dim);

        sorting_dim = (--sorting_dim) % Dim; // up a level

        if (should_replace(query, best, *it_median))
            best = *it_median;

        if (distance(best, query) >= std::abs((*it_median)[sorting_dim] - query[sorting_dim]))
        {
            auto new_begin = it_median + 1;
            auto potential = best;
            sorting_dim = (++sorting_dim) % Dim; // down a level

//            std::cout << std::endl;
//            std::cout << "Debug: subtree = ";
//            for (auto it = new_begin; it < it_end; ++it)
//            {
//                std::cout << *it << ", ";
//            }
//            std::cout << std::endl;

            find_nearest_neighbor_kdtree(query, potential, new_begin, it_end, sorting_dim);
            if (should_replace(query, best, potential))
                best = potential;
        }

    }
    else if (query[sorting_dim] > (*it_median)[sorting_dim] ||
             (query[sorting_dim] == (*it_median)[sorting_dim] && query > *it_median))
    {
        auto new_begin = it_median + 1;
        sorting_dim = (++sorting_dim) % Dim; // down a level
        find_nearest_neighbor_kdtree(query, best, new_begin, it_end, sorting_dim);

        sorting_dim = (--sorting_dim) % Dim; // up a level

        if (should_replace(query, best, *it_median))
            best = *it_median;

        if (distance(best, query) >= std::abs((*it_median)[sorting_dim] - query[sorting_dim]))
        {
            sorting_dim = (++sorting_dim) % Dim; // down a level
            auto potential = best;

//            std::cout << std::endl;
//            std::cout << "Debug: subtree = ";
//            for (auto it = it_begin; it < it_median; ++it)
//            {
//                std::cout << *it << ", ";
//            }
//            std::cout << std::endl;

            find_nearest_neighbor_kdtree(query, potential, it_begin, it_median, sorting_dim);
            if (should_replace(query, best, potential))
                best = potential;
        }
    }
//    else // query overlaps with median
//        best = *it_median;
}

template <int Dim>
auto kd_tree<Dim>::quick_select(typename std::vector<point<Dim>>::iterator it_begin,
                    typename std::vector<point<Dim>>::iterator it_end,
                    typename  std::vector<point<Dim>>::iterator::difference_type kth,
                    size_t sorting_dim)
-> typename std::vector<point<Dim>>::iterator
{
    while(true)
    {
        auto it_pivot = it_begin + std::rand() % std::distance(it_begin, it_end);
        std::iter_swap(it_pivot, it_end-1); // move pivot value to end

        auto pivot = it_end - 1;
        it_pivot = partition(it_begin, it_end-1, pivot, sorting_dim);

        std::iter_swap(it_end-1, it_pivot); // move pivot value to its place
        if (kth == it_pivot - it_begin)
        {
          return it_pivot;
        }
        else if (kth < it_pivot - it_begin)
        {
          it_end = it_pivot;
        }
        else
        {
          kth -= it_pivot+1 - it_begin;
          it_begin = it_pivot + 1;
        }
    }
}

template <int Dim>
auto
kd_tree<Dim>::partition(typename std::vector<point<Dim>>::iterator it_begin,
               typename std::vector<point<Dim>>::iterator it_end,
               typename std::vector<point<Dim>>::iterator pivot,
               size_t sorting_dim)
-> typename std::vector<point<Dim>>::iterator
{
    while (1) {
        while ((it_begin != it_end) && smaller_in_dimension(*it_begin, *pivot, sorting_dim)) {
            ++it_begin;
        }
        if (it_begin == it_end--) break;

        while ((it_begin != it_end) && !smaller_in_dimension(*it_end, *pivot, sorting_dim)) {
            --it_end;
        }
        if (it_begin == it_end) break;
        std::iter_swap(it_begin++, it_end);
    }
    return it_begin;
}

