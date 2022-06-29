#ifndef BTREE_H
#define BTREE_H

#include <memory>
#include <iostream>

template<class T, class Compare = std::less<T>>
class Btree {
public:
    typedef T       value_type;
    typedef T*      pointer;
    
    struct Node
    {
        Node()
        : parent(nullptr)
        , left(nullptr)
        , right(nullptr)
        , balance_factor(0)
        , value()
        {
        }
        
        Node(const value_type& val)
        : parent(nullptr)
        , left(nullptr)
        , right(nullptr)
        , balance_factor(0)
        , value(val)
        {
        }
        
        ~Node()
        {
        }
        
        struct Node *parent;
        struct Node *left;
        struct Node *right;
        int balance_factor;
        value_type value;
    };
    
    Btree()
        : root_(nullptr)
    {

    }

    std::pair<Node*, bool> insert(const value_type& value)
    {
        return insert(root_, value, nullptr);
    }
    
    Node* insert(Node* node, const value_type& value) {
        return insert(node, value, nullptr).first;
    }
    
    Node* find(const value_type& value) {
        return find(root_, value);
    }
    
    void prefix()
    {
        prefix(root_);
    }    

private:
    
    Node* create_node(const value_type& value) {
        Node* node = alloc_.allocate(1);
        alloc_.construct(node, value);
        
        return node;
    }

    std::pair<Node*, bool> insert(Node* root, const value_type& value, int**)
    {
        if (root_ == nullptr) {
            root_ = create_node(value);
            return {root_, true};
        }
        else {
            if (comp_(root->value, value)) { // left less
                if (root->right != nullptr) {
                    return insert(root->right, value, nullptr);
                    
                }
                root->right = create_node(value);
                root->right->parent = root;
                return {root->right, true};
            }
            else if (comp_(value, root->value)) {
                if (root->left != nullptr) {
                    return insert(root->left, value, nullptr);
                }
                root->left = create_node(value);
                root->left->parent = root;
                return {root->left, true};
            }
        }
        return {root, false};
    }
    
    Node* find(Node* root, const value_type& value) {
        if (root == nullptr) {
            return nullptr;
        }
        else {
            if (comp_(root->value, value)) { // left less
                return find(root->right, value);
            }
            else if (comp_(value, root->value)) {
                return find(root->left, value);
            }
            else {
                return root;
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
