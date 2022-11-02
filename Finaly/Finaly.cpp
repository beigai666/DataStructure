// Finaly.cpp : 定义静态库的函数。
//
#include <Windows.h>
#include <iostream>

#include <Tree/AVLTree.h>
#include <Tree/RBTree.h>
// TODO: 这是一个库函数示例
using namespace FinlayLib;
using namespace std;
void print(RBTree<int>& bst)
{
	SharedPointer< Array<int> > arr1 = bst.traversal(PreOrder);
	for (int i = 0; i < arr1->length(); i++)
	{
		cout << (*arr1)[i] << " ";
	}
	cout << endl;
	SharedPointer< Array<int> > arr2 = bst.traversal(InOrder);
	for (int i = 0; i < arr2->length(); i++)
	{
		cout << (*arr2)[i] << " ";
	}
	cout << endl;
	SharedPointer< Array<int> > arr3 = bst.traversal(PostOrder);
	for (int i = 0; i < arr3->length(); i++)
	{
		cout << (*arr3)[i] << " ";
	}
	cout << endl;
}
int start();
void fnFinaly()
{
	start();
}

