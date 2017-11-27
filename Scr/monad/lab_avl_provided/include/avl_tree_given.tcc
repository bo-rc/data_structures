/**
 * @file avl_tree_given.tcc
 * Definitions of some standard binary tree functions.
 *
 * YOU WON'T NEED TO MODIFY THIS FILE.
 *
 * In fact, you shouldn't have to read below this line. To see what the given
 * functions do, read the header file.
 */

#include "avl_tree.h"
#include "printtree.h"

template <class K, class V>
avl_tree<K, V>::avl_tree()
    : _out{&std::cout}
{
    // nothing
}

template <class K, class V>
avl_tree<K, V>::avl_tree(const avl_tree& other)
    : root_{copy(other.root_.get())}, _out{&std::cout}
{
    // nothing
}

template <class K, class V>
avl_tree<K, V>& avl_tree<K, V>::operator=(avl_tree rhs)
{
    swap(rhs);
    return *this;
}

template <class K, class V>
void avl_tree<K, V>::swap(avl_tree& other)
{
    std::swap(root_, other.root_);
    std::swap(_out, other._out);
}

template <class K, class V>
auto avl_tree<K, V>::copy(const node* subRoot) -> std::unique_ptr<node>
{
    if (!subRoot)
        return nullptr;

    // Copy this node and its children
    auto n = std::make_unique(subRoot->key, subRoot->value);
    n->left = copy(subRoot->left);
    n->right = copy(subRoot->right);
    return n;
}

// class for generic printing

template <typename Node>
class avl_treeNodeDescriptor
    : public GenericNodeDescriptor<avl_treeNodeDescriptor<Node>>
{
  public:
    avl_treeNodeDescriptor(const Node* root) : subRoot(root)
    {
        // nothing
    }
    bool isNull() const
    {
        return !subRoot;
    }

    string key() const
    {
        std::stringstream ss;
        ss << subRoot->key;
        return ss.str();
    }

    avl_treeNodeDescriptor left() const
    {
        return avl_treeNodeDescriptor(subRoot->left.get());
    }
    avl_treeNodeDescriptor right() const
    {
        return avl_treeNodeDescriptor(subRoot->right.get());
    }

  private:
    const Node* subRoot;
};

template <class K, class V>
void avl_tree<K, V>::print(ostream& out) const
{
    printTree(avl_treeNodeDescriptor<node>(root_.get()), out);
}

template <class K, class V>
int64_t avl_tree<K, V>::heightOrNeg1(const node* node) const
{
    if (node == NULL)
        return -1;
    else
        return node->height;
}

template <class K, class V>
void avl_tree<K, V>::setOutput(ostream& newOut)
{
    _out = &newOut;
}
