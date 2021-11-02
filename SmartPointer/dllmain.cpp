// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include <iostream>
#include <string>
#include <Windows.h>
#include "Array.h"
#include "HeapArray.h"
#include "WeakPtr.h"
#include "framework.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}




using namespace std;

class B;	//声明
class A
{
public:
	WeakPtr<B> pb_;
	A() {
		printf("A:%p\n", this);
	}
	~A()
	{
		cout << "A delete\n";
	}
};

class B
{
public:
	SharePtr<A> pa_;
	B() {
		printf("B:%p\n", this);
	}
	~B()
	{
		cout << "B delete\n";
	}
};



void SmartPointerTest()
{
	SharePtr<A> pa(new A());
	SharePtr<B> pb(new B());
	cout << pb.use_count() << endl;	//1
	cout << pa.use_count() << endl;	//1
	pb->pa_ = pa;
	pa->pb_ = pb;
	cout << pa->pb_.use_count() << endl;
	SharePtr<B> p = pa->pb_.lock();
	cout << pa->pb_.use_count() << endl;
	cout << pb.use_count() << endl;	//2
	cout << pa.use_count() << endl;	//2
}

void ArrayTest() {
	Array<std::string, 10>arr;
	arr.set(0, "hello");
	arr.set(1, "hhhhhh");
	for (int i = 0; i < 10; i++) {
		std::cout << "arr[" << i << "]=" << arr[i] << std::endl;
	}
	SharePtr<HeapArray<int>> heap = HeapArray<int>::NewInstance(10);

	for (int i = 0; i < 10; i++) {
		heap->set(i, i);
		std::cout << "heap[" << i << "]=" << (*heap)[i] << std::endl;
	}
}

extern "C" _declspec(dllexport)  int SmartPointer()
{
	std::cout << "************SmartPointerTest enter************"<< std::endl;
	SmartPointerTest();
	std::cout << "************SmartPointerTest leave************" << std::endl;
	std::cout << "************ArrayTest enter************" << std::endl;
	ArrayTest();
	std::cout << "************ArrayTest leave************" << std::endl;
	return 0;
}