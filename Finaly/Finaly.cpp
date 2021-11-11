// Finaly.cpp : 定义静态库的函数。
//

#include "pch.h"
#include "framework.h"
#include <iostream>
#include <List/StaticList.h>

using namespace FinlayLib;

// TODO: 这是一个库函数示例
void fnFinaly()
{
	StaticList<int, 5> l;
	for (int i = 0; i < l.capaity(); i++)
	{
		l.insert(0, i);
	}

	for (int i = 0; i < l.capaity(); i++)
	{
		std::cout<<l[i]<<std::endl;
	}
	l[0] *= l[0];
	for (int i = 0; i < l.capaity(); i++)
	{
		std::cout << l[i] << std::endl;
	}
	try
	{
		l[5] = 10;
	}
	catch (Exception & e)
	{
		std::cout << e.location() << std::endl;
		std::cout << e.message() << std::endl;
	}
	std::cout << "fnFinaly" << std::endl;
}
