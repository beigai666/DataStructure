// Finaly.cpp : 定义静态库的函数。
//
#include <Windows.h>
#include <iostream>
#include "pch.h"
#include "Array/StaticArray.h"
#include "Sort/Sort.h"
#include <Tree/GTree.h>
#include <Tree/BTree.h>
using namespace std;
using namespace FinlayLib;


// TODO: 这是一个库函数示例
void fnFinaly()
{

	BTree<int> bt;
	BTreeNode<int>* n=NULL;
	bt.insert(1,NULL);
	n = bt.find(1);
	bt.insert(2, n);
	bt.insert(3, n);

	n = bt.find(2);
	bt.insert(4, n);
	bt.insert(5, n);

	n = bt.find(4);
	bt.insert(8, n);
	bt.insert(9, n);
	n = bt.find(5);
	bt.insert(10, n);

	n = bt.find(3);
	bt.insert(6, n);
	bt.insert(7, n);

	n = bt.find(6);
	bt.insert(11, n, LEFT);

	int a[] = { 8,9,10,11,7 };
	for (int i = 0; i < 5; i++)
	{
		BTreeNode<int>* node = bt.find(a[i]);
		while (node)
		{
			cout << node->value << " ";
			node = dynamic_cast<BTreeNode<int>*>( node->parent);
		}
		cout << endl;
	}
	return;
}