// Finaly.cpp : 定义静态库的函数。
//
#include <iostream>
#include "pch.h"
#include "Array/StaticArray.h"
#include "Sort/Sort.h"
#include <Tree/Tree.h>
using namespace std;
using namespace FinlayLib;

struct Test : public Object
{
	int id;
	int data1[1000];
	double data2[500];
	bool operator <(const Test& obj)const
	{
		return id < obj.id;
	}
	bool operator <=(const Test& obj)const
	{
		return id <= obj.id;
	}
	bool operator >(const Test& obj)const
	{
		return id > obj.id;
	}
	bool operator >=(const Test& obj)const
	{
		return id >= obj.id;
	}
};

class TestProxy : public Object
{
protected:
	Test* m_pTest;

public:


	Test& operator = (Test& test)
	{
		m_pTest = &test;
		return test;
	}

	int id()
	{
		return m_pTest->id;
	}

	int* data1()
	{
		return m_pTest->data1;
	}

	double* data2()
	{
		return m_pTest->data2;
	}

	Test& test()const
	{
		return *m_pTest;
	}

	bool operator <(const TestProxy& obj)
	{
		return test() < obj.test();
	}
	bool operator <=(const TestProxy& obj)
	{
		return test() <= obj.test();
	}
	bool operator >(const TestProxy& obj)
	{
		return test() > obj.test();
	}
	bool operator >=(const TestProxy& obj)
	{
		return test() >= obj.test();
	}
private:

};


Test t[1000];
TestProxy pt[1000];

// TODO: 这是一个库函数示例
void fnFinaly()
{
	Tree<int> *tree;
	clock_t begin = 0;
	clock_t end = 0;
	for (int i = 0; i < 1000; i++)
	{
		t[i].id = i;
		pt[i] = t[i];
	}
	begin = clock();
	Sort::Quick(pt,1000, false);
	
	for (int i = 0; i < 1000; i++)
	{
		cout << t[i].id <<" " << pt[i].id() << endl;
	}
	
	end = clock();
	cout << "Time: "<<end-begin << endl;
	return;
}