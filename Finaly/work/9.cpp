#include <Array/StaticArray.h>
#include <Sort/Sort.h>
#include <Stack/LinkStack.h>
#include <String/String.h>
#include <iostream>
using namespace FinlayLib;
using namespace std;

template<typename T>
void copy_stack(LinkStack<T>& source, LinkStack<T>& des)
{
	LinkStack<T> temp;
	while (source.size()>0)
	{
		T var = source.top();
		temp.push(var);
		source.pop();
	}
	while (temp.size()>0)
	{
		T var = temp.top();
		source.push(var);
		des.push(var);
		temp.pop();
	}
}

void Round_up(Array<int> &c,int k, LinkStack<int>& temp, LinkStack<int>& ret)
{
	if (ret.size() > 0 && ret.size() < temp.size())
	{
		return;
	}
	for (int i = 0; i < c.length(); i++)
	{
		if (k < c[i])
		{
			continue;
		}
		temp.push(c[i]);
		if (k == c[i])
		{
			if (temp.size() < ret.size()||ret.size()==0)
			{
				copy_stack(temp,ret);
			}
		}
		else
		{
			Round_up(c, k-c[i], temp, ret);
		}
		temp.pop();
		
	}
}
/*
零钱凑整问题
*/
void Round_up()
{
	StaticArray<int, 4> c;
	c[0] = 1;
	c[1] = 2;
	c[2] = 5;
	c[3] = 10;
	Sort::Quick(c, false);
	LinkStack<int> temp;
	LinkStack<int> ret;
	Round_up(c, 28,temp, ret);
	while (ret.size()>0)
	{
		cout << ret.top() << " ";
		ret.pop();
	}
	cout << endl;
}
bool Compute(int n1, int n2, char sign, int& result)
{
	bool ret = true;
	switch (sign)
	{
	case '+':
		result = n1 + n2;
		break;
	case '-':
		ret = (n1 >= n2) ? (result = n1 - n2, true) : false;
		break;

	case '*':
		result = n1 * n2;
		break;

	case '/':
		if (n2)
			ret = !(n1 % n2) ? (result = n1 / n2, true) : false;
		else
		{
			ret = false;
		}
		break;

	default:
		ret = false;
		break;
	}
	return ret;
}

void print(LinkStack<String>& ret)
{
	LinkStack<String> temp;
	copy_stack(ret, temp);
	String str3 = temp.top();
	temp.pop();
	String str2 = temp.top();
	temp.pop();
	String str1 = temp.top();
	temp.pop();
	cout << str1.str() << "   " << str2.str() << "   " << str3.str() << endl;
}

void totalEvaluation(int result1, int result2,int k, LinkStack<String>& ret)
{
	if (result1 == 24 && result2 == 1)
	{
		cout << "24,1" << endl;
	}
	int resul = 0;
	if (Compute(result1, result2, '+', resul)&&resul==k)
	{
		char buff[100] = { 0 };
		snprintf(buff, 100, "%d + %d", result1, result2);
		String str = buff;
		ret.push(buff);
		print(ret);
		ret.pop();
	}
	if (Compute(result1, result2, '-', resul) && resul == k)
	{
		char buff[100] = { 0 };
		snprintf(buff, 100, "%d - %d", result1, result2);
		String str = buff;
		ret.push(buff);
		print(ret);
		ret.pop();
	}
	if (Compute(result2, result1, '-', resul) && resul == k)
	{
		char buff[100] = { 0 };
		snprintf(buff, 100, "%d - %d", result2, result1);
		String str = buff;
		ret.push(buff);
		print(ret);
		ret.pop();
	}
	if (Compute(result1, result2, '*', resul) && resul == k)
	{
		char buff[100] = { 0 };
		snprintf(buff, 100, "%d * %d", result1, result2);
		String str = buff;
		ret.push(buff);
		print(ret);
		ret.pop();
	}
	if (Compute(result1, result2, '/', resul) && resul == k)
	{
		char buff[100] = { 0 };
		snprintf(buff, 100, "%d / %d", result1, result2);
		String str = buff;
		ret.push(buff);
		print(ret);
		ret.pop();
	}
	if (Compute(result2, result1, '/', resul) && resul == k)
	{
		char buff[100] = { 0 };
		snprintf(buff, 100, "%d / %d", result2, result1);
		String str = buff;
		ret.push(buff);
		print(ret);
		ret.pop();
	}
}

void evaluation2(int n1, int n2, int k, LinkStack<String>& ret, int result1)
{
	int result2 = 0;
	if (Compute(n1, n2, '+', result2))
	{
		char buff[100] = { 0 };
		snprintf(buff, 100, "%d + %d", n1, n2);
		String str = buff;
		ret.push(buff);
		totalEvaluation(result1, result2,k, ret);
		ret.pop();
	}
	if (Compute(n1, n2, '-', result2))
	{
		char buff[100] = { 0 };
		snprintf(buff, 100, "%d - %d", n1, n2);
		String str = buff;
		ret.push(buff);
		totalEvaluation(result1, result2, k, ret);
	}
	if (Compute(n2, n1, '-', result2))
	{
		char buff[100] = { 0 };
		snprintf(buff, 100, "%d - %d", n2, n1);
		String str = buff;
		ret.push(buff);
		totalEvaluation(result1, result2, k, ret);
		ret.pop();
	}
	if (Compute(n1, n2, '*', result2))
	{
		char buff[100] = { 0 };
		snprintf(buff, 100, "%d * %d", n1, n2);
		String str = buff;
		ret.push(buff);
		totalEvaluation(result1, result2, k, ret);
		ret.pop();
	}
	if (Compute(n1, n2, '/', result2))
	{
		char buff[100] = { 0 };
		snprintf(buff, 100, "%d / %d", n1, n2);
		String str = buff;
		ret.push(buff);
		totalEvaluation(result1, result2, k, ret);
		ret.pop();
	}
	if (Compute(n2, n1, '/', result2))
	{
		char buff[100] = { 0 };
		snprintf(buff, 100, "%d / %d", n2, n1);
		String str = buff;
		ret.push(buff);
		totalEvaluation(result1, result2, k, ret);
		ret.pop();
	}
}

void fun2(Array<int>& pk, int k, LinkStack<String>& ret,int result)
{
	for (int i = 0; i < pk.length(); i++)
	{
		if (pk[i] != 0) {
			int n1 = pk[i];
			pk[i] = 0;
			for (int j = i; j < pk.length(); j++)
			{
				if (pk[j] != 0)
				{
					int n2 = pk[j];
					pk[j] = 0;

					evaluation2(n1, n2, k, ret, result);

					pk[j] = n2;
				}

			}
			pk[i] = n1;
		}
		
	}
}
void evaluation1(int n1,int n2,Array<int>& pk, int k, LinkStack<String>& ret)
{
	int result=0;
	if (Compute(n1, n2, '+', result))
	{
		char buff[100] = { 0 };
		snprintf(buff, 100, "%d + %d", n1, n2);
		String str = buff;
		ret.push(buff);
		fun2(pk, k, ret, result);
		ret.pop();
	}
	if (Compute(n1, n2, '-', result))
	{
		char buff[100] = { 0 };
		snprintf(buff, 100, "%d - %d", n1, n2);
		String str = buff;
		ret.push(buff);
		fun2(pk, k, ret, result);
		ret.pop();
	}
	if (Compute(n2, n1, '-', result))
	{
		char buff[100] = { 0 };
		snprintf(buff, 100, "%d - %d", n2, n1);
		String str = buff;
		ret.push(buff);
		fun2(pk, k, ret, result);
		ret.pop();
	}
	if (Compute(n1, n2, '*', result))
	{
		char buff[100] = { 0 };
		snprintf(buff, 100, "%d * %d", n1, n2);
		String str = buff;
		ret.push(buff);
		fun2(pk, k, ret, result);
		ret.pop();
	}
	if (Compute(n1, n2, '/', result))
	{
		char buff[100] = { 0 };
		snprintf(buff, 100, "%d / %d", n1, n2);
		String str = buff;
		ret.push(buff);
		fun2(pk, k, ret, result);
		ret.pop();
	}
	if (Compute(n2, n1, '/', result))
	{
		char buff[100] = { 0 };
		snprintf(buff, 100, "%d / %d", n2, n1);
		String str = buff;
		ret.push(buff);
		fun2(pk, k, ret, result);
		ret.pop();
	}
}

void fun1(Array<int>& pk, int k,LinkStack<String>& ret)
{
	for (int i = 0; i < pk.length()&&pk[i]!=0; i++)
	{
		int n1 = pk[i];
		pk[i] = 0;
		for (int j = i; j < pk.length(); j++)
		{
			if (pk[j] != 0)
			{
				int n2 = pk[j];
				pk[j] = 0;

				evaluation1(n1, n2, pk, k, ret);

				pk[j] = n2;
			}
			
		}
		pk[i] = n1;
	}
}

//24点问题
void fun8_2() {
	StaticArray<int,4> pk;
	pk[0] = 2;
	pk[1] = 3;
	pk[2] = 4;
	pk[3] = 6;
	LinkStack<String> ret;
	fun1(pk, 24, ret);
}