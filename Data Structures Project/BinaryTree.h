#pragma once
#ifndef _BinaryTree
#define _BinaryTree
#include"TreeNode.h"
template<class T>
class BinaryTree
{
private:
	TreeNode<T>* Root; // pointer to the root of the tree
public:
    // Constructor
    BinaryTree() 
    {
        Root = nullptr;
    }
    // Insert a node with the given value
    void Insert(T value) 
    {
         InsertBT(Root, value);
    }

    // Search for a value in the tree
    bool Search(T value) 
    {
        return SearchBT(Root, value);
    }
private:
    // Helper function to insert a node with the given value
    void InsertBT(TreeNode<T>*& node, T value) 
    {
        if (Root == nullptr)
            Root = new TreeNode<T>(value);

        else if (value < node->GetData()) 
        {
            InsertBT(node->GetLeft(), value);
        }
        else 
        {
            InsertBT(node->GetRight(), value);   
        }
    }

    // Helper function to search for a value in the tree
    bool SearchBT(TreeNode<T>* node, T value)
    {
        if (node == nullptr) 
        {
            return false;
        }
        else if (value == node->GetData()) 
        {
            return true;
        }
        else if (value < node->GetData()) 
        {
            return SearchBT(node->GetLeft(), value);
        }
        else 
        {
            return SearchBT(node->GetRight(), value);
        }
    }
};
#endif
