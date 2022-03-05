#include <iostream>

#include <List/DynamicList.h>
#include <String/String.h>
using namespace FinlayLib;
bool IsContained(int a[], int n, int x)
{
	if (n > 0)
	{
		if (a[--n] == x)
		{
			return true;
		}
		return IsContained(a, n, x);
	}
	return false;
}

bool IsOrdered(int a[], int n, bool min2max = true)
{
	bool ret = true;
	if (--n > 0) {
		ret = min2max ? a[n] > a[n - 1] : a[n] < a[n - 1];
		return ret && IsOrdered(a, n, min2max);
	}
	return ret;
}

int MaxInArray(int a[], int n)
{
	int ret = 0;
	if (n--) {
		ret = MaxInArray(a, n);
	}
	return ret > a[n] ? ret : a[n];

}

void subset(String str,DynamicList<FinlayLib::String> &ret)
{
	if (str.length() >= 0)
	{
		if (ret.find(str) == -1) {
			ret.insert(str);
		}
		
	}
	for (int i = 0; i < str.length(); i++)
	{
			String temp = str;
			temp.remove(i,1);
			subset(temp, ret);
	}
}


void deduplication(List<int> &ret, List<int> &str,int n)
{
	int temp = 0;
	if (--n >= 0)
	{
		ret.get(n, temp);
		if (str.find(temp)!=-1) {
			ret.remove(n);
		}
		else
		{
			str.insert(temp);
		}
		deduplication(ret, str, n);
	}
}