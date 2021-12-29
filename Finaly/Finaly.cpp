// Finaly.cpp : 定义静态库的函数。
//

#include "pch.h"
#include "framework.h"
#include <iostream>
#include <String/String.h>
using namespace std;
using namespace FinlayLib;
int* make_pmt(const char* p) {
	int len = strlen(p);
	int* ret = static_cast<int*>(malloc(sizeof(int) * len));
	if (ret != NULL)
	{
		int ll = 0;
		ret[0] = 0;
		for (int i = 1; i < len; i++)
		{
			while ((ll>0)&&(p[ll]!=p[i]))
			{
				ll = ret[ll - 1];
			}
			if (p[ll] == p[i]) {
				ll++;
			}
			ret[i] = ll;
		}
	}
	return ret;
}

int kmp(const char* s, const char* p)
{
	int ret = -1;
	int sl = strlen(s);
	int pl = strlen(p);
	int* pmt = make_pmt(p);
	if ((pmt != NULL) && (0 < pl) && (pl <= sl)) {
		for (int i = 0,j=0; i < sl; i++)
		{
			while ((j>0)&&(s[i]!=p[j]))
			{
				j = pmt[j - 1];
			}
			if (s[i] == p[j]) {
				j++;
			}
			if (j == pl)
			{
				ret = i + 1 - pl;
			}
		}
	}
	free(pmt);
	return ret;
}

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
	String s = "ababax";
	String s1 = s.sub(3, 10);
	cout << s.str() << endl;
	cout << s1.str() << endl;
}
