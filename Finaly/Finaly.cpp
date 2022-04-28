// Finaly.cpp : 定义静态库的函数。
//
#include <Windows.h>
#include <iostream>

#include <Tree/AVLTree.h>
#include <Tree/BSTree.h>
// TODO: 这是一个库函数示例
using namespace FinlayLib;
using namespace std;

void fnFinaly()
{
//	AVLTree<int> avl;
	BSTree<int> bst;
	bst.insert(20);
	bst.insert(30);
	bst.insert(31);
	bst.insert(32);
	bst.insert(33);
	bst.insert(34);
	SharedPointer< Array<int> > arr = bst.traversal(PreOrder);
	for (int i = 0; i < arr->length(); i++)
	{
		cout << (*arr)[i] << " ";
	}
	cout << "##################" << endl;
	SharedPointer< Array<int> > arr1 = bst.traversal(InOrder);
	for (int i = 0; i < arr1->length(); i++)
	{
		cout << (*arr1)[i] << " ";
	}
	cout << endl;
	bst.insert(21);
	bst.insert(19);
	bst.insert(18);
	SharedPointer< Array<int> > arr2= bst.traversal(PreOrder);
	for (int i = 0; i < arr2->length(); i++)
	{
		cout << (*arr2)[i] <<" " ;
	}
	cout << "##################" << endl;
	SharedPointer< Array<int> > arr3 = bst.traversal(InOrder);
	for (int i = 0; i < arr3->length(); i++)
	{
		cout << (*arr3)[i] << " ";
	}
	cout << endl;
	bst.remove(32);
	SharedPointer< Array<int> > arr4 = bst.traversal(PreOrder);
	for (int i = 0; i < arr4->length(); i++)
	{
		cout << (*arr4)[i] << " ";
	}
	cout << "##################" << endl;
	SharedPointer< Array<int> > arr5 = bst.traversal(InOrder);
	for (int i = 0; i < arr5->length(); i++)
	{
		cout << (*arr5)[i] << " ";
	}
	//cout << bst.count() << endl;
}

