#include <List/DynamicList.h>
#include <Windows.h>
#include <iostream>
#include <Array/DynamicArray.h>
#include <List/LinkList.h>
#include <Stack/LinkStack.h>
#include <String/String.h>
using namespace std;
using namespace FinlayLib;
typedef struct Goods
{
	int weight;
	int value;
	bool operator == (const Goods& s)const
	{
		if (this->weight == s.weight && this->value == s.value)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}Goods;

void Print(Stack<Goods>& stack,int maxValue)
{
	LinkStack<Goods> tmp;

	while (stack.size())
	{
		Goods e = stack.top();

		tmp.push(e);

		stack.pop();
	}

	while (tmp.size())
	{
		Goods e = tmp.top();

		cout <<" [" << e.weight << "," << e.value<< "] ";

		stack.push(e);

		tmp.pop();
	}

	cout <<" maxValue = "<< maxValue << endl;
}

void Print(Stack<String>& stack)
{
	LinkStack<String> tmp;

	while (stack.size())
	{
		String e = stack.top();

		tmp.push(e);

		stack.pop();
	}

	cout << "[ ";

	while (tmp.size())
	{
		String e = tmp.top();

		cout << e.str() << ".";

		stack.push(e);

		tmp.pop();
	}

	cout << "]"  << endl;
}

void taskcpy(Stack<Goods>& stack, Stack<Goods>& retstack) {
	retstack.clear();
	LinkStack<Goods> tmp;
	while (stack.size())
	{
		Goods e = stack.top();
		tmp.push(e);
		stack.pop();
	}
	while (tmp.size())
	{
		Goods e = tmp.top();
		retstack.push(e);
		stack.push(e);
		tmp.pop();
	}
}

void knapsack_problem(int totalweight, Goods* list,int begin,int end,int& maxValue,int& indexValue, Stack<Goods>& stack, Stack<Goods>& retstack)
{
	int i = begin;
	int weight=0;
	if (begin > end && indexValue > maxValue)
	{
		maxValue = indexValue;
		taskcpy(stack, retstack);
	}
	while(i <= end)
	{
		if (totalweight >= list[i].weight)
		{
			stack.push(list[i]);
			indexValue += list[i].value;
			knapsack_problem(totalweight - list[i].weight, list,i+1,end,maxValue,indexValue,stack,retstack);
			indexValue -= list[i].value;
			stack.pop();
		}
		else if(indexValue>maxValue)
		{
			maxValue = indexValue;
			taskcpy(stack, retstack);
		}
		i++;
	}
	return;
}
void knapsack_problem(int totalweight, Goods* list, int len)
{
	LinkStack<Goods> stack;
	LinkStack<Goods> retstack;
	//Goods list[] = { {7,5},{2,4},{3,3},{4,2},{5,1} };
	int maxValue = 0;
	int indexValue = 0;
	knapsack_problem(totalweight, list, 0, len-1, maxValue, indexValue, stack, retstack);
	Print(retstack,maxValue);
}

bool IsValid(String tmp) {
	if (tmp[0] != '0' && atoi(tmp.str()) <= 255)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void MakeIp(FinlayLib::String str,int i,List<String>& seg, List<String>& retsult)
{
	if (i==str.length() && seg.length() == 4)
	{
		String ip;
		for (int i=0;i<seg.length();i++)
		{
			String str;
			seg.get(i, str);
			ip += str + ".";
		}
		ip.remove(ip.length() - 1, 1);
		retsult.insert(ip);
		return;
	}
	else if (i < str.length())
	{
		int index = seg.length();
		String current="";
		String tmp = "";
		seg.get(index - 1, current);
		tmp = current + str[i];
		if (index > 0&& IsValid(tmp))
		{
				seg.set(index-1, tmp);
				MakeIp(str, i + 1, seg, retsult);
				seg.set(index - 1, current);
		}
		if (index<4)
		{
			seg.insert(str[i]);
			MakeIp(str, i + 1, seg, retsult);
			seg.remove(index);
		}
	}
}

typedef struct Coordinate
{
	int x;
	int y;
	bool operator == (const Coordinate& s)const
	{
		if (this->x == s.x && this->y == s.y)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}Coordinate;

#define NUM 10
void Print(Stack<Coordinate>& stack)
{
	LinkStack<Coordinate> tmp;

	while (stack.size())
	{
		Coordinate e = stack.top();

		tmp.push(e);

		stack.pop();
	}

	cout << "[ ";

	while (tmp.size())
	{
		Coordinate e = tmp.top();

		cout << " (" << e.y <<"," << e.x << ") ";

		stack.push(e);

		tmp.pop();
	}

	cout << "]" << endl;
}
void maze(int arr[NUM][NUM],int x,int y, Array<bool>& visited, LinkStack<Coordinate>& stack)
{
	visited[y * NUM + x] = true;
	if (x == NUM - 1 && y == NUM - 1)
	{
		Print(stack);
	}
	if (arr[y][x] == 0)
	{
		
		Coordinate coor = {x,y};
		stack.push(coor);
		if (x+1<NUM && !visited[y*NUM+x+1] &&arr[y][x + 1] == 0)
		{
			maze(arr, x + 1, y, visited, stack);
		}
		if (y + 1 < NUM && !visited[(y+1) * NUM + x] && arr[y + 1][x] == 0)
		{
			maze(arr, x, y+1, visited, stack);
		}
		if (x - 1 < NUM && x-1>=0 &&!visited[y * NUM + x-1] && arr[y][x - 1] == 0)
		{
			maze(arr, x-1, y, visited, stack);
		}
		if(y-1 < NUM && y-1>=0 && !visited[(y-1) * NUM + x] && arr[y - 1][x] == 0)
		{
			maze(arr, x, y-1, visited, stack);
		}
		stack.pop();
	}
	visited[y * NUM + x] = false;
	return;
}

void test()
{
	
	//LinkStack<int> stack;
	Goods list[] = { {1,5},{2,4},{3,3},{4,2},{5,1} };
	knapsack_problem(10, list, 5);
	
	LinkList<String> seg;
	LinkList<String> retsult;
	FinlayLib::String str = "10203040";
	MakeIp(str,0,seg,retsult);
	for (int i = 0; i < retsult.length(); i++)
	{
		String ip = retsult.get(i);
		std::cout <<ip.str() << endl;
	}
	/*
	int arr[NUM][NUM] = {
		0,0,0,1,1,1,1,1,1,1,
		1,0,0,1,1,1,1,1,1,1,
		1,0,0,0,0,1,1,1,1,1,
		1,0,1,1,0,1,1,1,1,1,
		1,0,1,1,0,0,1,1,1,1,
		1,0,1,1,1,0,0,1,1,1,
		1,0,1,1,1,1,0,0,1,1,
		1,0,0,0,0,0,0,0,1,1,
		1,1,1,1,1,1,1,0,1,1,
		1,1,1,1,1,1,1,0,0,0,
	};
	LinkStack<Coordinate> stack;
	DynamicArray<bool> visited(NUM*NUM);
	for (int i = 0; i < NUM * NUM; i++)
	{
		visited[i] = false;
	}
	maze(arr, 0, 0, visited, stack);
	*/
}