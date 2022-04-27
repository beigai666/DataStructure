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
}

