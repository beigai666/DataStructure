// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include "Exception.h"
#include "framework.h"
#include <iostream>
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
extern "C" _declspec(dllexport)  void exceptionTest() {
    try
    {
        TGEOW_EXCEPTION(FinlayLib::Exception,"test");
        //throw FinlayLib::Exception("test",__FILE__,__LINE__);
    }
    catch (const FinlayLib::Exception& e)
    {

        cout << e.location() << endl;
    }
}
