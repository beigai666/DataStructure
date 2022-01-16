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
	BTreeNode<int> btn;
	GTree<char> t;
	GTreeNode<char>* node = NULL ;
	t.insert('A', NULL);
	node = t.find('A');
	t.insert('B', node);
	t.insert('C', node);
	t.insert('D', node);

	node = t.find('B');
	t.insert('E', node);
	t.insert('F', node);

	node = t.find('E');
	t.insert('K', node);
	t.insert('L', node);

	node = t.find('C');
	t.insert('G', node);

	node = t.find('D');
	t.insert('H', node);
	t.insert('I', node);
	t.insert('J', node);

	node = t.find('H');
	t.insert('M', node);
	cout << "count=" << t.count() << endl;
	cout << "height=" << t.height() << endl;
	cout << "degree=" << t.degree() << endl;
	for (t.begin(); ! t.end(); t.next())
	{
		cout<<t.current()<<endl;
	}
	return;
}