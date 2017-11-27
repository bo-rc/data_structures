/**
 * @file quadtree.cpp
 * quadtree class implementation.
 * @date Spring 2008
 * @date Modified Summer 2014
 */

#include "quadtree.h"
#include <stdexcept>
#include <cmath>

namespace cs225
{

quadtree::quadtree() : root_{nullptr}
{
    // nothing to do
}

quadtree::quadtree(const epng::png &source, uint64_t resolution)
{
    if(resolution%2 != 0)
        throw std::runtime_error("resolution must be a power of 2.");
    build_tree(source, resolution);
}

quadtree::quadtree(const quadtree &other)
{
    copy_quadtree(root_, other.root_);
}

// private helper for cctor
void quadtree::copy_quadtree(std::unique_ptr<node> &this_subroot, const std::unique_ptr<node> &other_subroot)
{

    if(other_subroot == nullptr)
    {
        this_subroot = nullptr;
        return;
    }

    this_subroot = std::make_unique<node>(other_subroot->up_left_x,
                                          other_subroot->up_left_y,
                                          other_subroot->width,
                                          other_subroot->element);

    copy_quadtree(this_subroot->northwest, other_subroot->northwest);
    copy_quadtree(this_subroot->northeast, other_subroot->northeast);
    copy_quadtree(this_subroot->southwest, other_subroot->southwest);
    copy_quadtree(this_subroot->southeast, other_subroot->southeast);
}

quadtree::quadtree(quadtree &&other)
{
    root_ = std::move(other.root_);
}

quadtree& quadtree::operator=(quadtree other)
{
    this->swap(other);
    return *this;
}

void quadtree::swap(quadtree &other)
{
    std::swap(this->root_, other.root_);
}

void quadtree::build_tree(const epng::png &source, uint64_t resolution)
{
    root_ = std::make_unique<node>(0, 0, resolution);
    build_tree(0, 0, resolution, source, root_); // building the quadtree, only leaves have element info.
    init(root_); // initialize node elements from the pixels
}

// private helper for build_tree
void quadtree::build_tree(uint64_t x, uint64_t y, uint64_t width, const epng::png& img, std::unique_ptr<node>& subroot)
{
    if(width == 2) // base case
    {
        subroot->northwest = std::make_unique<node>(x, y, width/2, img);
        subroot->northeast = std::make_unique<node>(x+width/2, y, width/2, img);
        subroot->southwest = std::make_unique<node>(x, y+width/2, width/2, img);
        subroot->southeast = std::make_unique<node>(x+width/2, y+width/2, width/2, img);
        return;
    }
    else
    {
        subroot->northwest = std::make_unique<node>(x, y, width/2);
        build_tree(x, y, width/2, img, subroot->northwest);
        subroot->northeast = std::make_unique<node>(x+width/2, y, width/2);
        build_tree(x+width/2, y, width/2, img, subroot->northeast);
        subroot->southwest = std::make_unique<node>(x, y+width/2, width/2);
        build_tree(x, y+width/2, width/2, img, subroot->southwest);
        subroot->southeast = std::make_unique<node>(x+width/2, y+width/2, width/2);
        build_tree(x+width/2, y+width/2, width/2, img, subroot->southeast);
        return;
    }
}

// private helper for build_tree
void quadtree::init(std::unique_ptr<node>& subroot)
{
    if(!subroot->northwest->northwest) // Base case. perfect quadtree does not test other leaves
    {
        get_avg(subroot->element, subroot);
        return;
    }
    else
    {
        init(subroot->northwest);
        init(subroot->northeast);
        init(subroot->southwest);
        init(subroot->southeast);

        get_avg(subroot->element, subroot);
        return;
    }
}

void quadtree::rotate_clockwise()
{
    rotate_clockwise(root_);
}

void quadtree::rotate_clockwise(std::unique_ptr<node>& subroot)
{
    if (subroot->northwest == nullptr)
    {
        return;
    }

//    uint64_t x_nw = subroot->northwest->up_left_x;
//    uint64_t y_nw = subroot->northwest->up_left_y;

//    uint64_t x_ne = subroot->northeast->up_left_x;
//    uint64_t y_ne = subroot->northeast->up_left_y;

//    uint64_t x_se = subroot->southeast->up_left_x;
//    uint64_t y_se = subroot->southeast->up_left_y;

//    uint64_t x_sw = subroot->southwest->up_left_x;
//    uint64_t y_sw = subroot->southwest->up_left_y;


    // auto nw_tmp = std::make_unique<node>();
    // copy_quadtree(nw_tmp, subroot->northwest);


    subroot->northeast.swap(subroot->southeast);
//    subroot->northeast->up_left_x = x_ne;
//    subroot->northeast->up_left_y = y_ne;
//    subroot->southeast->up_left_x = x_se;
//    subroot->southeast->up_left_y = y_se;

    subroot->northeast.swap(subroot->southwest);
//    subroot->northeast->up_left_x = x_ne;
//    subroot->northeast->up_left_y = y_ne;
//    subroot->southwest->up_left_x = x_sw;
//    subroot->southwest->up_left_y = y_sw;

    subroot->northeast.swap(subroot->northwest);
//    subroot->northeast->up_left_x = x_ne;
//    subroot->northeast->up_left_y = y_ne;
//    subroot->northwest->up_left_x = x_nw;
//    subroot->northwest->up_left_y = y_nw;

    rotate_clockwise(subroot->northwest);
    rotate_clockwise(subroot->southwest);
    rotate_clockwise(subroot->southeast);
    rotate_clockwise(subroot->northeast);
}

void quadtree::prune(uint32_t tolerance)
{
    prune(tolerance, root_);
}

void quadtree::prune(uint32_t t, std::unique_ptr<node>& subroot)
{
    if (subroot->northwest == nullptr)
        return;

    if (prunable(t, subroot))
    {
        subroot->element = get_region_color(subroot);
        subroot->northwest = nullptr;
        subroot->northeast = nullptr;
        subroot->southwest = nullptr;
        subroot->southeast = nullptr;
        return;
    }

    prune(t, subroot->northwest);
    prune(t, subroot->northeast);
    prune(t, subroot->southeast);
    prune(t, subroot->southwest);
}

epng::rgba_pixel quadtree::get_region_color(std::unique_ptr<node>& subroot)
{
    epng::rgba_pixel pxl;
    uint64_t x = subroot->up_left_x;
    uint64_t y = subroot->up_left_y;

    pxl.red = get(x, y, subroot).red;
    pxl.green = get(x, y, subroot).green;
    pxl.blue = get(x, y, subroot).blue;
    pxl.alpha = get(x, y, subroot).alpha;

    for (uint64_t w = x; w != (x + subroot->width); ++w)
    {
        for (uint64_t h = y; h != (y + subroot->width); ++h)
        {
            pxl.red = (pxl.red + get(w, h, subroot).red) / 2;
            pxl.green = (pxl.green + get(w, h, subroot).green) / 2;
            pxl.blue = (pxl.blue + get(w, h, subroot).blue) / 2;
            pxl.alpha = (pxl.alpha + get(w, h, subroot).alpha) / 2;
        }
    }

    return pxl;
}


bool quadtree::prunable(uint32_t t, const std::unique_ptr<node>& subroot) const
{
    auto region_avg = subroot->element;
    for (uint64_t x = subroot->up_left_x; x != (subroot->up_left_x + subroot->width); ++x)
    {
        for (uint64_t y = subroot->up_left_y; y != (subroot->up_left_y + subroot->width); ++y)
        {
            if (pxl_diff(region_avg, get(x, y, subroot)) > t)
                return false;
        }
    }

    return true;
}

uint32_t quadtree::pxl_diff(const epng::rgba_pixel avg, epng::rgba_pixel pxl) const
{
    return std::pow(double(avg.red) - double(pxl.red), 2) +
           std::pow(double(avg.green) - double(pxl.green), 2) +
           std::pow(double(avg.blue) - double(pxl.blue), 2);
}


uint64_t quadtree::pruned_size(uint32_t tolerance) const
{
    uint64_t num_pxl = 0;
    count_pxl(root_, num_pxl);

    pruned_size(root_, tolerance, num_pxl);

    return num_pxl;
}

void quadtree::pruned_size(const std::unique_ptr<node>& subroot, uint32_t tol, uint64_t& num) const
{
    if (subroot->northwest == nullptr)
        return;

    if (prunable(tol, subroot))
    {
        num = num - subroot->width * subroot->width + 1;
        return;
    }

    pruned_size(subroot->northwest, tol, num);
    pruned_size(subroot->northeast, tol, num);
    pruned_size(subroot->southwest, tol, num);
    pruned_size(subroot->southeast, tol, num);
}

void quadtree::count_pxl(const std::unique_ptr<node> &subroot, uint64_t& num) const
{
    if (subroot->northwest == nullptr)
    {
        ++num;
        return;
    }

    count_pxl(subroot->northwest, num);
    count_pxl(subroot->northeast, num);
    count_pxl(subroot->southeast, num);
    count_pxl(subroot->southwest, num);
}


uint32_t quadtree::ideal_prune(uint64_t num_leaves) const
{
    uint64_t RANGE_BEGIN = 0;
    uint64_t RANGE_END = 100000;

    uint64_t tol_begin = RANGE_BEGIN;
    uint64_t tol_end = RANGE_END;
    uint64_t tol_mid = (tol_begin + tol_end)/2;

    uint64_t current_size = 0;

    while (tol_mid > tol_begin)
    {
        if (current_size > num_leaves)
        {
            tol_begin = tol_mid;
            tol_mid = (tol_begin + tol_end)/2;
            //std::cout << tol_mid << std::flush;
        }
        else if (current_size <= num_leaves)
        {
            tol_end = tol_mid;
            tol_mid = (tol_begin + tol_end)/2;
            //std::cout << tol_mid << std::flush;
        }
        current_size = pruned_size(tol_mid);
    }

    return tol_mid + 1;
}

// private helper
void quadtree::get_avg(epng::rgba_pixel& pxl, std::unique_ptr<node>& subroot)
{
    pxl.red = ( subroot->northwest->element.red
                + subroot->northeast->element.red
                + subroot->southwest->element.red
                + subroot->southeast->element.red) / 4;
    pxl.green = ( subroot->northwest->element.green
                + subroot->northeast->element.green
                + subroot->southwest->element.green
                + subroot->southeast->element.green) / 4;
    pxl.blue = ( subroot->northwest->element.blue
                + subroot->northeast->element.blue
                + subroot->southwest->element.blue
                + subroot->southeast->element.blue) / 4;
    pxl.alpha = ( subroot->northwest->element.alpha
                + subroot->northeast->element.alpha
                + subroot->southwest->element.alpha
                + subroot->southeast->element.alpha) / 4;
}


const epng::rgba_pixel& quadtree::operator ()(uint64_t x, uint64_t y) const
{
    if(root_ == nullptr)
        throw std::out_of_range("this is an empty image");
    else
    {
        return determine(x, y, root_);
    }
}

const epng::rgba_pixel& quadtree::determine(uint64_t x, uint64_t y, const std::unique_ptr<node>& subroot) const
{
    if(subroot == nullptr)
        throw std::out_of_range("empty quadtree");

    if ((x >= subroot->up_left_x + subroot->width) || (y >= subroot->up_left_y + subroot->width))
        throw std::out_of_range("pixel location out of quadtree boundary");

    return get(x, y, subroot);
}


const epng::rgba_pixel& quadtree::get(uint64_t x, uint64_t y, const std::unique_ptr<node>& subroot) const
{
    if(subroot->northwest == nullptr)
    {
        return subroot->element;
    }
    else
    {
        if(x >= subroot->up_left_x + subroot->width/2)
        {
            if(y >= subroot->up_left_y + subroot->width/2)
            {
                return get(x, y, subroot->southeast);
            }
            else
            {
                return get(x, y, subroot->northeast);
            }
        }
        else
        {
            if(y >= subroot->up_left_y + subroot->width/2)
            {
                return get(x, y, subroot->southwest);
            }
            else
            {
                return get(x, y, subroot->northwest);
            }
        }
    }
}


epng::png quadtree::decompress() const
{
    if(root_ == nullptr)
        throw std::runtime_error("This quadtree is empty");

    epng::png image(root_->width, root_->width);

    traverse_and_recover(root_, image);

    return image;

}

void quadtree::traverse_and_recover(const std::unique_ptr<node>& subroot, epng::png& img) const
{
    if(subroot->northwest == nullptr) // Base case. perfect quadtree does not test other leaves
    {
        img(subroot->up_left_x, subroot->up_left_y)->red = subroot->element.red;
        img(subroot->up_left_x, subroot->up_left_y)->green = subroot->element.green;
        img(subroot->up_left_x, subroot->up_left_y)->blue = subroot->element.blue;
        img(subroot->up_left_x, subroot->up_left_y)->alpha = subroot->element.alpha;
        return;
    }

    traverse_and_recover(subroot->northwest, img);
    traverse_and_recover(subroot->northeast, img);
    traverse_and_recover(subroot->southwest, img);
    traverse_and_recover(subroot->southeast, img);
}



/* nested node class begins */
quadtree::node::node(uint64_t x, uint64_t y, uint64_t w)
    : up_left_x{x}, up_left_y{y}, width{w},
      northwest{nullptr}, northeast{nullptr},
      southwest{nullptr}, southeast{nullptr}
{
    // nothing to do
    element.red = 0;
    element.green = 0;
    element.blue = 0;
    element.alpha = 0;
}

quadtree::node::node(uint64_t x, uint64_t y, uint64_t w, const epng::png& img)
    : up_left_x{x}, up_left_y{y}, width{w},
      northwest{nullptr}, northeast{nullptr},
      southwest{nullptr}, southeast{nullptr}
{
    element.red = img(x,y)->red;
    element.green = img(x,y)->green;
    element.blue = img(x,y)->blue;
    element.alpha = img(x,y)->alpha;
}

quadtree::node::node(uint64_t x, uint64_t y, uint64_t w, const epng::rgba_pixel &pxl)
    : up_left_x{x}, up_left_y{y}, width{w},
      northwest{nullptr}, northeast{nullptr},
      southwest{nullptr}, southeast{nullptr}
{
    element.red = pxl.red;
    element.green = pxl.green;
    element.blue = pxl.blue;
    element.alpha = pxl.alpha;
}

/* nested node class ends */



} // namespace cs225
