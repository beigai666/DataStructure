// Finaly.cpp : 定义静态库的函数。
//

#include "pch.h"
#include "framework.h"
#include <iostream>
#include <List/StaticList.h>
#include <List/DynamicList.h>
#include <Array/DynamicArray.h>
using namespace FinlayLib;

// TODO: 这是一个库函数示例
void fnFinaly()
{
	DynamicaArray<int> arr(5);

	for (int i = 0; i < arr.length(); i++)
	{
		arr[i]=i*i;
	}
	int num = 0;
	for (int i = 0; i < arr.length(); i++)
	{
		num += arr[i];
		std::cout<< arr[i]<<std::endl;
		arr[i] = num;
	}

	for (int i = 0; i < arr.length(); i++)
	{
		std::cout << arr[i] << std::endl;
	}
	DynamicaArray<int> s2(10);
	s2 = arr;
	s2.resize(8);

	for (int i = 0; i < s2.length(); i++)
	{
		std::cout << s2[i] << std::endl;
	}
	std::cout << "fnFinaly" << std::endl;
}
