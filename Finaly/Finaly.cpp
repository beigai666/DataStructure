// Finaly.cpp : 定义静态库的函数。
//

#include "pch.h"
#include "framework.h"
#include <iostream>
#include <Array/DynamicArray.h>
#include "List/DualLinkList.h"
#include "List/CircleList.h"
#include "List/LinuxList.h"
using namespace FinlayLib;
void josephus(int n, int s, int m) {
	CircleList<int> cl;
	for (int i = 1; i <= n; i++)
	{
		cl.insert(i);
	}
	cl.move(s - 1, m - 1);

	while (cl.length()>0)
	{
		cl.next();
		cout << cl.current() << endl;
		cl.remove(cl.find(cl.current()));
	}
}
// TODO: 这是一个库函数示例
void fnFinaly()
{
	DualLinkList<int> dl;

	for (int i = 0; i < 5; i++)
	{
		dl.insert(0, i);
		dl.insert(0, 5);

	}
	for (dl.move(0); !dl.end(); dl.next())
	{
		cout << dl.current() << endl;
	}
	//josephus(41, 1, 3);
	cout << "begin" << endl;
	for (dl.move(dl.length()-1); !dl.end(); dl.pre())
	{
		cout<< dl.current() <<endl;
	}

}
