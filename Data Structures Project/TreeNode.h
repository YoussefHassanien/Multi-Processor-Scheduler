#pragma once
#ifndef _TreeNode
#define _TreeNode
template<class T>
class TreeNode
{
private:
	T Data;
	TreeNode<T>* Left;
	TreeNode<T>* Right;
public:
	//Default Constructor
	TreeNode()
	{
		Left = nullptr;
		Right = nullptr;
	}
	//Constructor that takes 1 parameter (the data value)
	TreeNode(const T& value)
	{
		Data = value;
		Left = nullptr;
		Right = nullptr;
	}
	//Constructor that takes 3 parameters( the data value and 2 pointers for the left and rights TreeNodes)
	TreeNode(const T& value, TreeNode<T>* leftptr, TreeNode<T>* rightptr)
	{
		Data = value;
		Left = leftptr;
		Right = rightptr;
	}
	// Setter for Data
	void SetData(const T& value)
	{
		Data = value;
	}
	// Setter for Left
	void SetLeft(TreeNode<T>* leftptr)
	{
		Left = leftptr;
	}
	// Setter for Right
	void SetRight(TreeNode<T>* right) {
		Right = right;
	}
	// Getter for Data
	T GetData() const
	{
		return Data;
	}
	// Getter for Left
	TreeNode<T>*& GetLeft() 
	{
		return Left;
	}
	// Getter for Right
	TreeNode<T>*& GetRight() 
	{
		return Right;
	}
};
#endif