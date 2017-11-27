/**
 * @file avl_tree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

#include "avl_tree.h"
#include <cmath>

template <class K, class V>
const V& avl_tree<K, V>::find(const K& key) const
{
    return find(root_.get(), key);
}

template <class K, class V>
const V& avl_tree<K, V>::find(const node* subtree, const K& key) const
{
    if (!subtree)
    {
        throw std::out_of_range{"invalid key"};
    }
    else if (key == subtree->key)
    {
        return subtree->value;
    }
    else if (key < subtree->key)
    {
        return find(subtree->left.get(), key);
    }
    else
    {
        return find(subtree->right.get(), key);
    }
}

//template <class K, class V>
//void avl_tree<K, V>::rotate_left(std::unique_ptr<node>& t)
//{
//    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
//    /// @ Your code here
//    std::unique_ptr<node> right = std::move(t->right);

//    if (right)
//        t->right = std::move(right->left);

//    right->left = std::move(t);

//    t = std::move(right);

//    t->height = std::max(heightOrNeg1(t->left.get()), heightOrNeg1(t->right.get())) + 1;
//    t->left->height = std::max(heightOrNeg1(t->left->left.get()), heightOrNeg1(t->left->right.get())) + 1;
//}

template <class K, class V>
void avl_tree<K, V>::rotate_left(std::unique_ptr<node>& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)

    std::unique_ptr<node> right = std::move(t->right);
    std::unique_ptr<node> right_left = std::move(right->left);

    t->right = std::move(right_left);
    right->left = std::move(t);
    t = std::move(right);

    t->left->height = std::max(heightOrNeg1(t->left->left.get()), heightOrNeg1(t->left->right.get())) + 1;
    t->height = std::max(heightOrNeg1(t->left.get()), heightOrNeg1(t->right.get())) + 1;
}

template <class K, class V>
void avl_tree<K, V>::rotate_left_right(std::unique_ptr<node>& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // Implemented for you:
    rotate_left(t->left);
    rotate_right(t);
}

//template <class K, class V>
//void avl_tree<K, V>::rotate_right(std::unique_ptr<node>& t)
//{
//    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
//    /// @ Your code here
//    std::unique_ptr<node> left = std::move(t->left);

//    if (left != nullptr)
//    {
//        t->left = std::move(left->right);
//        left->right = std::move(t);
//        t = std::move(left);
//    }

//    t->height = std::max(heightOrNeg1(t->left.get()), heightOrNeg1(t->right.get())) + 1;
//    t->right->height = std::max(heightOrNeg1(t->right->left.get()), heightOrNeg1(t->right->right.get())) + 1;
//}


template <class K, class V>
void avl_tree<K, V>::rotate_right(std::unique_ptr<node>& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)

    std::unique_ptr<node> left = std::move(t->left);
    std::unique_ptr<node> left_right = std::move(left->right);

    t->left = std::move(left_right);
    left->right = std::move(t);
    t = std::move(left);

    t->right->height = std::max(heightOrNeg1(t->right->left.get()), heightOrNeg1(t->right->right.get())) + 1;
    t->height = std::max(heightOrNeg1(t->left.get()), heightOrNeg1(t->right.get())) + 1;
}

template <class K, class V>
void avl_tree<K, V>::rotate_right_left(std::unique_ptr<node>& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    /// @ Your code here
    rotate_right(t->right);
    rotate_left(t);
}

template <class K, class V>
void avl_tree<K, V>::insert(K key, V value)
{
    insert(root_, std::move(key), std::move(value));
}

template <class K, class V>
void avl_tree<K, V>::insert(std::unique_ptr<node>& subtree, K key, V value)
{
    /// @ Your code here
    if (!subtree)
        subtree = std::make_unique<node>(std::move(key), std::move(value));

    else if (key < subtree->key)
        insert(subtree->left, key, value);
    else if (key > subtree->key)
        insert(subtree->right, key, value);

    rebalance(subtree);
}

template <class K, class V>
void avl_tree<K, V>::rebalance(std::unique_ptr<node>& subroot)
{
    /// @ Your code here
    auto balance = heightOrNeg1(subroot->left.get()) - heightOrNeg1(subroot->right.get());

    if (balance == 2) // case 1: left - left
    {
        rebalance_left(subroot);
    }
    else if (balance == -2) // case 2: left - right: double-rotation
    {
        rebalance_right(subroot);
    }

    subroot->height = std::max(heightOrNeg1(subroot->left.get()),
                               heightOrNeg1(subroot->right.get())) + 1;
}

template <class K, class V>
void avl_tree<K, V>::rebalance_left(std::unique_ptr<node>& subroot)
{
    /// @ Your code here
    auto balance = heightOrNeg1(subroot->left->left.get()) - heightOrNeg1(subroot->left->right.get());

    if (balance >= 0)
    {
        rotate_right(subroot);
    }
    else
    {
        rotate_left_right(subroot);
    }
}

template <class K, class V>
void avl_tree<K, V>::rebalance_right(std::unique_ptr<node>& subroot)
{
    /// @todo Your code here
    auto balance = heightOrNeg1(subroot->right->left.get()) - heightOrNeg1(subroot->right->right.get());

    if (balance <= 0)
    {
        rotate_left(subroot);
    }
    else
    {
        rotate_right_left(subroot);
    }
}
