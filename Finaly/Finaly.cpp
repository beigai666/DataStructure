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
	AVLTree<int> avl;
	BSTree<int> bst;
	avl.insert(20, NULL);
	avl.insert(30, NULL);
	avl.insert(31, NULL);
	avl.insert(32, NULL);
	avl.insert(33, NULL);
	avl.insert(34, NULL);
	SharedPointer< Array<int> > arr = avl.traversal(PreOrder);
	for (int i = 0; i < arr->length(); i++)
	{
		cout << (*arr)[i] << " ";
	}
	cout << "##################" << endl;
	SharedPointer< Array<int> > arr1 = avl.traversal(InOrder);
	for (int i = 0; i < arr1->length(); i++)
	{
		cout << (*arr1)[i] << " ";
	}
	cout << endl;
	avl.insert(21, NULL);
	avl.insert(19, NULL);
	avl.insert(18, NULL);
	SharedPointer< Array<int> > arr2=avl.traversal(PreOrder);
	for (int i = 0; i < arr2->length(); i++)
	{
		cout << (*arr2)[i] <<" " ;
	}
	cout << "##################" << endl;
	SharedPointer< Array<int> > arr3 = avl.traversal(InOrder);
	for (int i = 0; i < arr3->length(); i++)
	{
		cout << (*arr3)[i] << " ";
	}
	cout << endl;
	avl.DeleteNode(20);
	SharedPointer< Array<int> > arr4 = avl.traversal(PreOrder);
	for (int i = 0; i < arr4->length(); i++)
	{
		cout << (*arr4)[i] << " ";
	}
	cout << "##################" << endl;
	SharedPointer< Array<int> > arr5 = avl.traversal(InOrder);
	for (int i = 0; i < arr5->length(); i++)
	{
		cout << (*arr5)[i] << " ";
	}
}

