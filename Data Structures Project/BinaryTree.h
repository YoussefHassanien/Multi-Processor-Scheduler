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
    // Destroy the whole tree
    void Destroy()
    {
        DestroyTree(Root);
    }
    // Delete a specific node and all its children
    void Delete(T value)
    {
        DeleteNode(Root, value);
    }
    //Prints the whole tree
    void Print()
    {
        PrintBT(Root);
    }
    ~BinaryTree()
    {
        Destroy();
    }
private:
    // The Private Insert Function
    void InsertBT(TreeNode<T>*& root, T value) 
    {
        if (!root)
        {
            root = new TreeNode<T>(value);
            return;
        }
        else if(!root->GetLeft())
        {
            InsertBT(root->GetLeft(), value);
        }
        else if (!root->GetRight())
        {
            InsertBT(root->GetRight(), value);
        }

    }

    // The Private Search Function
    bool SearchBT(TreeNode<T>* root, T value)
    {
        if (!root)  return false;
        else if (value == root->GetData()) return true;     
        SearchBT(root->GetLeft(), value);
        SearchBT(root->GetRight(), value);
    }
    // The Private Destroy Function
    void DestroyTree(TreeNode<T>*& root)
    {
        if (root)
        {
            DestroyTree(root->GetLeft());
            DestroyTree(root->GetRight());
            delete root;
            root = nullptr;
        }
    }
    // The Private Delete Function
    void DeleteNode(TreeNode<T>*& root,T value)
    {
        if (!root) return;
        if (SearchBT(root, value))
        {
            if (value == root->GetData())
                DestroyTree(root);
            
            else
            {
                DeleteNode(root->GetLeft(), value);
                DeleteNode(root->GetRight(), value);
            }
    
        }

    }
    void PrintBT(TreeNode<T>* root)
    {
        if (!root) return;
        PrintBT(root->GetLeft());
        PrintBT(root->GetRight());
        cout << *root->GetData() << endl;
    }
};
#endif
