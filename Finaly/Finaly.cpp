// Finaly.cpp : 定义静态库的函数。
//

#include "pch.h"
#include "framework.h"
#include <iostream>
#include <String/String.h>
using namespace std;
using namespace FinlayLib;

void test_1() {
	cout << "test_1()begin ..." << endl;
	String s;
	s = 'D';
	cout << s.str() << endl;
	cout << s.length() << endl;
	cout << (s == "D") << endl;
	cout << (s > "CCC") << endl;

	s += " Finlay zhu neng feng";
	cout << s.str() << endl;
	cout << s.length() << endl;
	cout << (s == "D Finlay zhu neng feng") << endl;
	cout << (s > "CCC") << endl;
	cout << "test_1() end ..." << endl;
}

void test_2() {
	cout << "test_2()begin ..." << endl;
	String a[] = { "E","D","C","B","A" };
	String min = a[0];
	for (int i = 0; i < 5; i++)
	{
		if (min > a[i]) {
			min = a[i];
		}
	}
	cout << "min=" << min.str() << endl;
	cout << "test_2() end ..." << endl;
}

// TODO: 这是一个库函数示例
void fnFinaly()
{
	String s = "   abc   ";
	if (s.trim().insert(0, "D.T.").endOf("abc") && s.startWith("D.T."))
	{
		cout <<"["<< s.str()<<"]" << endl;
	}
	cout << s.str() << endl;
}
