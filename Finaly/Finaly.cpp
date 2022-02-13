// Finaly.cpp : 定义静态库的函数。
//
#include <Windows.h>
#include <iostream>
#include <Array/RangeArray.h>
#include <Queue/DualEndQueue.h>
// TODO: 这是一个库函数示例
using namespace FinlayLib;
using namespace std;
bool IsSym(int n)
{
	DualEndQueue<int> q;
	if (n < 0) n = -n;
	while (n)
	{
		q.add(n % 10);
		n /= 10;
	}
	while ((q.length() > 1) && (q.front() == q.back()))
	{
		q.remove();
		q.dismiss();
	}
	return (q.length() <= 1);
}
void fnFinaly()
{
	cout << IsSym(121) << endl;
	cout << IsSym(2332) << endl;
	cout << IsSym(112211) << endl;
	cout << IsSym(123456) << endl;
	cout << IsSym(321654) << endl;
}