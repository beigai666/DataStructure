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
bool IsIntStr(const char* s, int& n);
int FindMid(int a[], int n);
void test();
void StackSort();
void StackReverse();
void PlanetCollision();
void fnFinaly()
{
	//StackReverse();
	PlanetCollision();
	//StackSort();
	//test();
	/*
	const char* s = "123456";
	int n = 0;
	std::cout <<IsIntStr(s,n)<<" num=" << n << endl;
	int arr[] = { 5,2,3,4,1,6,7,8,9 };
	std::cout << FindMid(arr, 9) << std::endl;
	*/
}

