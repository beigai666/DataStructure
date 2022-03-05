// Finaly.cpp : 定义静态库的函数。
//
#include <Windows.h>
#include <iostream>
#include <Array/RangeArray.h>
#include <Queue/DualEndQueue.h>
#include <Tree/BTreeArray.h>
#include <Graph/ListGraph.h>
#include <Graph/MatrixGraph.h>
#include <Heap/DynamicHeap.h>
#include <Sort/Sort.h>
#include <List/DynamicList.h>
#include <String/String.h>
// TODO: 这是一个库函数示例
using namespace FinlayLib;
using namespace std;
void BigprtiteGraph();
void MatrixMinDistance();
bool IsContained(int a[], int n, int x);
bool IsOrdered(int a[], int n, bool min2max = true);
int MaxInArray(int a[], int n);
void subset(String str, DynamicList<FinlayLib::String>& ret);
void deduplication(List<int>& ret, List<int>& str, int n);
void fnFinaly()
{
	int a[10] = { 1,20,3,4,5,6,7,8,9,10 };
	cout<< IsContained(a,10,10)<<endl;

	cout << IsOrdered(a, 10)<<endl;

	cout << MaxInArray(a, 10) << endl;
/*
	String str = "abc";
	DynamicList<FinlayLib::String> list(8);
	subset(str, list);
	for (int i = 0; i < list.length(); i++)
	{
		cout << list[i].str() << endl;
	}
	*/
	LinkList<int> str;
	str.insert(1);
	str.insert(3);
	str.insert(1);
	str.insert(5);
	str.insert(3);
	str.insert(5);
	str.insert(7);
	LinkList<int> temp;
	deduplication(str, temp, 7);
	for (int i = 0; i < str.length(); i++)
	{	
		cout << str.get(i) << endl;
	}
}

