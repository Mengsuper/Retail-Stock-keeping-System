//
//  redblacktree.cpp
//  redblacktree
//
//  Created by LI MENG on 2016-06-09.
//  Copyright © 2016 LI MENG. All rights reserved.
//
#ifdef _RBTREE_H_

#include <iostream>
#include <cstdlib>
using namespace std;


// default constructor
template <typename T>
RBTree<T>::RBTree()
{
    //root = new Node<T>(item);
    root = NULL;
    size = 0;
}

// destructor
// Must deallocate memory associated with all nodes in tree
template <typename T>
RBTree<T>::~RBTree()
{
    //RemoveAll();
    delete root;
    size = 0;
}

template <typename T>
void RBTree<T>::RBRemoveFixUp(Node<T>* x, Node<T>* xparent, bool xisleftchild)
{      // xparent and xisleftchild are useless!!!
    while (x != NULL && x != root && x->is_black == true)
    {
        if (x == x->p->left)  // x is the left child
        {
            Node<T>* y = x->p->right;
            if (y->is_black == false)
            {
                y->is_black = true;
                x->p->is_black = false;
                RotateLeft(x->p);
                y = x->p->right;
            }
            if (y->left->is_black == true && y->right->is_black == true)
            {
                y->is_black = false;
                x = x->p;
            }
            else
                if (y->right->is_black == true)
                {
                    y->left->is_black = true;
                    y->is_black = false;
                    RotateRight(y);
                    y = x->p->right;
                }
            y->is_black = x->p->is_black;
            x->p->is_black = true;
            y->right->is_black = true;
            RotateLeft(x->p);
            x = root;
        }
        else  // symmetric   x is the right child
        {
            Node<T>* y = x->p->left;
            if (y->is_black == false)
            {
                y->is_black = true;
                x->p->is_black = false;
                RotateRight(x->p);
                y = x->p->left;
            }
            if (y->right->is_black == true && y->left->is_black == true)
            {
                y->is_black = false;
                x = x->p;
            }
            else
                if (y->left->is_black == true)
                {
                    y->right->is_black = true;
                    y->is_black = false;
                    RotateLeft(y);
                    y = x->p->left;
                }
            y->is_black = x->p->is_black;
            x->p->is_black = true;
            y->left->is_black = true;
            RotateRight(x->p); // RotateRight(x->p);
            x = root;
        }
        x->is_black = true;
    }
    
}


template <typename T>
bool RBTree<T>::Insert(T item)
{
    if (Contains(item))              //check whether it already contains item
        return false;
    else
    {
        Node<T>* x = BSTInsert(item);  //BST insert the item and return its node
        x->is_black = false;
        
        while (x != NULL && x != root && x->p->is_black == false)
        {
            if (x->p == x->p->p->left)
            {
                Node<T>* y = x->p->p->right;
                if (y != NULL && y->is_black == false)  // ADD ONE MORE CONDITION: y != NULL
                    
                {
                    x->p->is_black = true;
                    y->is_black = true;
                    x->p->p->is_black = false;
                    x = x->p->p;
                }
                else
                {
                    if (x == x->p->right)     //y->is_black == true;
                    {
                        x = x->p;
                        RotateLeft(x);
                    }
                    x->p->is_black = true;
                    x->p->p->is_black = false;
                    RotateRight(x->p->p);
                }
            }
            else //if (x->p == x->p->p->right)
            {
                Node<T>* y = x->p->p->left;
                if (y != NULL && y->is_black == false)    // ADD ONE MORE CONDITION: y != NULL
                {
                    x->p->is_black = true;
                    y->is_black = true;
                    x->p->p->is_black = false;
                    x = x->p->p;
                }
                else
                {
                    if (x == x->p->left)     //y->is_black == true;
                    {
                        x = x->p;
                        RotateRight(x);
                    }
                    x->p->is_black = true;
                    x->p->p->is_black = false;
                    RotateLeft(x->p->p);
                }
            }  // end of while loop;
        }
        root->is_black = true;
        size++;
        return true;
    }
    
}

template <typename T>
bool RBTree<T>::Remove(T item)
{
    if (Contains(item))        // check whether RBT contains the item to be deleted
    {
        Node<T>* z = Find(item);  // Find the item to be deleted and return its node pointer
        Node<T>* y = NULL;
        Node<T>* x = NULL;
        
        //y = (z->left == NULL || z->right == NULL) ? z : Predecessor(z);
        if (z->left == NULL || z->right == NULL)
            y = z;
        else
            y = Predecessor(z);
        
        //x = (y->left != NULL) ? y->left : y->right;
        if (y->left != NULL)
            x = y->left;
        else
            x = y->right;
        
        
        if (x != NULL)      //if x is not NULL;
            x->p = y->p;
        
        bool xisleftchild = true;
        
        if (y->p == NULL)
            root = x;
        else
            if (y == y->p->left)
                y->p->left = x;
            else
                y->p->right = x;
        if (y != z)
            z->data = y->data;
        
        if (y->is_black == true)
            RBRemoveFixUp(x, y, xisleftchild);  //FixUp;
        
        delete y;  // deallocated memory;
        size--;    // decrease size by 1;
        return true;
    }
    else
        return false;
}

template <typename T>
void RBTree<T>::RemoveAll(Node<T>* node)
{
    if(node != NULL)
    {
        Remove(node->data);  // get new RBtree??
        if (node->left != NULL && node->right != NULL)
        {
            RemoveAll(node->left);
            RemoveAll(node->right);
        }
        else
            if (node->left != NULL && node->right == NULL)
            {
                RemoveAll(node->left);
            }
            else
                if (node->left == NULL && node->right != NULL)
                {
                    RemoveAll(node->right);
                }
    }
    else return;
}

template <typename T>
void RBTree<T>::RemoveAll()
{
    if (root == NULL)
        return;
    else
        RemoveAll(root);
    root = NULL;
    size = 0;
}

//copy tree
template <typename T>
Node<T>* RBTree<T>::CopyTree(Node<T>* sourcenode, Node<T>* parentnode)
{
    if (sourcenode != NULL)
    {
        Node<T>* newNode = new Node<T>(sourcenode->data);
        newNode->p = sourcenode->p;
        newNode->is_black = sourcenode->is_black;
        newNode->left = CopyTree(sourcenode->left, newNode);
        newNode->right = CopyTree(sourcenode->right, newNode);
        return newNode;
    }
    return NULL;
    
}

//Deep copy (copy constructor)
template <typename T>
RBTree<T>::RBTree(const RBTree<T>& rbtree)
{
    size = rbtree.size;
    root = CopyTree(rbtree.root, NULL);  // why it can get the root directly by rbtree.root?
    
}


// Deep copy (overloaded operator)
template <typename T>
RBTree<T>&::RBTree<T>::operator=(const RBTree<T>& rbtree)
{
    if (this != &rbtree)
    {
        RemoveAll(root);
        size = rbtree.size;
        root = CopyTree(rbtree.root, NULL);
    }
    return *this;
}


/*
template <typename T>
void RBTree<T>::printTree()
{
    printTree(root);
}
 */


// private function: compute tree height
template <typename T>
int RBTree<T>::ComputeHeight(Node<T>* node) const
{
    if (node == NULL)
        return 0;
    else
    {
        int leftheight = ComputeHeight(node->left);
        int rightheight = ComputeHeight(node->right);
        return (leftheight >= rightheight) ? (leftheight+1) : (rightheight+1);
    }
}

template <typename T>
int RBTree<T>::Height() const
{
    return ComputeHeight(root);
}


template <typename T>
int RBTree<T>::Size() const
{
    return size;
}

#endif