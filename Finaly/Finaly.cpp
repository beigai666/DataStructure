// Finaly.cpp : 定义静态库的函数。
//

#include "pch.h"
#include "framework.h"
#include <iostream>
//#include "Stack/Stacktest.h"
#include "Queue/LinkQueue.h"
using namespace std;
using namespace FinlayLib;

// TODO: 这是一个库函数示例
void fnFinaly()
{
	//cout << scan("<a{b(\'l)c}d>") << endl;
	LinkQueue<int> queue;
	for (int i = 0; i < 10; i++)
	{
		queue.add(i);
	}

	while (queue.length()>0)
	{
		cout << queue.front() << endl;
		queue.remove();
	}
}
