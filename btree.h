#ifndef BTREE_H
#define BTREE_H

#include <memory>
#include <iostream>

template<class T, class Compare = std::less<T>>
class Btree {
public:
    typedef T       value_type;
    typedef T*      pointer;

    Btree()
        : root_(nullptr)
    {

    }

    void insert(const value_type& value)
    {
        insert_recursive(&root_, value);
    }

    void prefix()
    {
        prefix(root_);
    }    

private:
    struct Node
    {
        Node()
            : left(nullptr), right(nullptr), value()
        {
        }

        Node(const value_type& val)
            : left(nullptr), right(nullptr), value(val)
        {
        }

        ~Node()
        {
        }

        struct Node *left;
        struct Node *right;
        value_type value;
    };

    void insert_recursive(Node** root, const value_type& value)
    {
        if (*root == nullptr) {
            *root = alloc_.allocate(1);
            alloc_.construct(*root, value);
        }
        else {
            if (comp_((*root)->value, value)) { // left less
                insert_recursive(&(*root)->right, value);
            }
            else {
                insert_recursive(&(*root)->left, value);
            }
        }
    }
    
    void prefix(Node* root)
    {
        if (root == nullptr) {
            return;
        }
        prefix(root->left);
        std::cout << root->value << "\n";
        prefix(root->right);
    }

    struct Node* root_;
    Compare comp_;
    std::allocator<Node> alloc_;
};

#endif