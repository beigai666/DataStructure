// Finaly.cpp : 定义静态库的函数。
//
#include <Windows.h>
#include <iostream>
#include <Array/RangeArray.h>
// TODO: 这是一个库函数示例
using namespace FinlayLib;
using namespace std;
void fnFinaly()
{
	RangeArray<double> a(-3,5);
	for (int i = a.lower(); i < a.upper(); i++)
	{
		a[i] = i / 10.0;
	}
	for (int i = a.lower(); i < a.upper(); i++)
	{
		cout << "a["<< i << "]" <<a[i]<< endl;
	}
}