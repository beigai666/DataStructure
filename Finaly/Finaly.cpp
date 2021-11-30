// Finaly.cpp : 定义静态库的函数。
//

#include "pch.h"
#include "framework.h"
#include <iostream>
#include <Array/DynamicArray.h>
//#include "pointer/SmartPointer.h"
#include "pointer/SharePointer.h"
using namespace FinlayLib;

class Test
{
public:
	Test();
	~Test();
	int value;
private:

};

Test::Test():value(0)
{
	cout << "Test::Test()" << endl;
}

Test::~Test()
{
	cout << "Test::~Test()" << endl;
}
// TODO: 这是一个库函数示例
void fnFinaly()
{
	SharePointer<Test> sp0 = new Test;
	SharePointer<Test> sp1= sp0;
	SharePointer<Test> sp2 = NULL;
	sp2 = sp1;
	sp2->value = 100;
	std::cout << sp0->value << std::endl;
	std::cout << sp1->value << std::endl;
	std::cout << sp2->value << std::endl;
	sp1.clear();
	std::cout << (sp0 == sp1)<< std::endl;
	std::cout << (sp0 != sp1) << std::endl;
	std::cout << "fnFinaly" << std::endl;
}
