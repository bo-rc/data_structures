/**
 * @file binary_tree.tcc
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

#include <algorithm>

template <class T>
int binary_tree<T>::height() const
{
    // Call recursive helper function on root
    return height(root_.get());
}

template <class T>
int binary_tree<T>::height(const node* subRoot) const
{
    // Base case
    if (!subRoot)
        return -1;

    // Recursive definition
    auto left = height(subRoot->left.get());
    auto right = height(subRoot->right.get());
    return std::max(left, right) + 1;
}

template <class T>
void binary_tree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root_.get());

    // Finish the line
    std::cout << std::endl;
}

template <class T>
void binary_tree<T>::printLeftToRight(const node* subRoot) const
{
    // Base case - null node
    if (!subRoot)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left.get());

    // Print this node
    std::cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right.get());
}

template <class T>
void binary_tree<T>::mirror()
{
    mirror(root_.get());
}

template <class T>
bool binary_tree<T>::isOrdered() const
{
    return isOrdered(root_.get());
}

template <class T>
void binary_tree<T>::printPaths() const
{
    /// @todo your code here
    std::vector<T> vec{};
    printPaths(root_.get(), vec);
}

template <class T>
void binary_tree<T>::printPaths(node* subRoot, std::vector<T>& vec) const
{

    vec.push_back(subRoot->elem);
    //std::cout << subRoot->elem << " ";

    if (subRoot->left.get())
    {
        printPaths(subRoot->left.get(), vec);
        vec.pop_back();
        if (subRoot->right.get())
        {
            printPaths(subRoot->right.get(), vec);
            vec.pop_back();
        }
    } else if (subRoot->right.get())
    {
        printPaths(subRoot->right.get(), vec);
        vec.pop_back();
        if (subRoot->left.get())
        {
            printPaths(subRoot->left.get(), vec);
            vec.pop_back();
        }
    }
    else
    {
        std::cout << "Path: ";
        for (auto& x : vec)
            std::cout << x << " ";

        std::cout << std::endl;
        return;
    }
}

template <class T>
uint64_t binary_tree<T>::sumDistances() const
{
    /// @todo your code here
    int counter = 0;
    sumDistUtil(root_.get(), counter);
    return counter;
}

template <class T>
void binary_tree<T>::mirror(node* subRoot)
{
    // Base case - null node
    if (!subRoot)
        return;
    mirror(subRoot->left.get());
    mirror(subRoot->right.get());
    subRoot->left.swap(subRoot->right);
}

template <class T>
bool binary_tree<T>::isOrderedUtil(node* subRoot, T min, T max) const
{
    if(!subRoot)
       return true;

    if((subRoot->elem > min)
    && (subRoot->elem < max)
    && (isOrderedUtil(subRoot->left.get(), min, subRoot->elem))
    && (isOrderedUtil(subRoot->right.get(), subRoot->elem, max)))
        return true;
    else
        return false;
}

template <class T>
bool binary_tree<T>::isOrdered(node* subRoot) const
{
    return isOrderedUtil(subRoot, INT_MIN, INT_MAX);
}

template <class T>
void binary_tree<T>::sumDistUtil(node* subRoot, int& counter) const
{
    if (!subRoot)
        return;
    counter += get_depth(root_.get(), subRoot->elem, 0);
    sumDistUtil(subRoot->left.get(), counter);
    sumDistUtil(subRoot->right.get(), counter);
}

template <class T>
int binary_tree<T>::get_depth(node* subRoot, T data, int depth) const
{
    if (!subRoot)
        return 0;

    if (subRoot->elem == data)
        return depth;

    int downlevel = get_depth(subRoot->left.get(), data, depth+1);
    if (downlevel != 0)
        return downlevel;

    downlevel = get_depth(subRoot->right.get(), data, depth+1);
    return downlevel;
}

//template <class T>
//std::pair<T, T> binary_tree<T>::tree_limits(node* subRoot) const
//{
//    std::vector<T> cont {};
//    traverse_and_save(subRoot, cont);

//    std::sort (cont.begin(), cont.end());
//    return std::pair<T, T> {cont[0], cont[cont.size() - 1]};
//}

//template <class T>
//void binary_tree<T>::traverse_and_save(node* subRoot, std::vector<T>& cont) const
//{
//    if (subRoot)
//    {
//        traverse_and_save(subRoot->left.get(), cont);
//        cont.push_back(subRoot->elem);
//        traverse_and_save(subRoot->right.get(), cont);
//    } else {
//        return;
//    }
//}



