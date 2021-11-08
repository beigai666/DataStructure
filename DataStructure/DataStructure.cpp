// DataStructure.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <typeinfo>
#include <iostream>
#include <Windows.h>
typedef int (*SmartPointer)();

typedef void (*ExceptionTest)();

int main()
{
    HINSTANCE hDll;//DLL 句柄
    ExceptionTest smartPointer;//函数指针
    
    hDll = LoadLibrary(L"Exception.dll");//动态获取dll文件的路径
    if (hDll != NULL)
    {
        printf("hDll=%p\n", hDll);
        smartPointer = (ExceptionTest)GetProcAddress(hDll, "exceptionTest");//根据函数名在dll文件中获取该函数的地址    
        if (smartPointer != NULL)
        {
            smartPointer();
            //printf("result=%d\n", result);
        }
        FreeLibrary(hDll);
    }
    
    int i = 0;
    const type_info& tiv = typeid(i);
    std::cout << tiv.name() << std::endl;
    std::cout << "Hello World!\n";
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
