#include <List/DynamicList.h>
#include <Windows.h>
#include <iostream>
#include <Array/DynamicArray.h>
#include <Stack/LinkStack.h>
#include <String/String.h>
using namespace std;
using namespace FinlayLib;
typedef struct Goods
{
	int weight;
	int value;
	
}Goods;
template< typename T >
void Print(Stack<T>& stack,int weight)
{
	LinkStack<T> tmp;

	while (stack.size())
	{
		T e = stack.top();

		tmp.push(e);

		stack.pop();
	}

	cout << "[ ";

	while (tmp.size())
	{
		T e = tmp.top();

		cout << e << ", ";

		stack.push(e);

		tmp.pop();
	}

	cout << "] ="<< weight << endl;
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



int knapsack_problem(int weight_cout, Goods* list,int len, int b, Stack<int>& stack)
{
	int i = b;
	int g_value=0;
	int value = 0;
	int weight=0;
	if (i == len)
	{
		Print(stack, 10 - weight_cout);
	}
	while( i < len)
	{
		
		if (weight_cout >= list[i].weight)
		{
			stack.push(list[i].weight);
			std::cout << i<<"=>weight:" << list[i].weight << std::endl;
			value = knapsack_problem(weight_cout - list[i].weight, list, len,i+1,stack)+ list[i].value;
			if (value > g_value)
			{
				g_value = value;
				weight = list[i].weight;
			}
			stack.pop();
		}
		else
		{
			Print(stack,10- weight_cout);
		}
		
		i++;
	}
	return g_value;
}

void recovery_ip(FinlayLib::String str, Stack<String>& stack,int num)
{
	if (stack.size() >= 4)
	{
		return;
	}
	for (int i = 0; i < 3&&i<str.length(); i++)
	{
		String string = str.sub(0, i + 1);
		if (i > 0&&string[0]=='0')
		{
			continue;
		}
		const char* c_str = string.str();
		int num = atoi(c_str);
		if (num < 255)
		{
			stack.push(c_str);
			if (i + 1 < str.length())
			{
				recovery_ip(str.sub(i + 1), stack,num-1);
			}
			else if(stack.size()==4)
			{
				Print(stack);
			}
			stack.pop();
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
	/*
	LinkStack<int> stack;
	Goods list[] = { {7,5},{2,4},{3,3},{4,2},{5,1} };
	int value = knapsack_problem(10, list, 5, 0,stack);
	std::cout << value << endl;
	LinkStack<String> stack_string;
	FinlayLib::String str = "10203040";
	recovery_ip(str, stack_string,3);
	*/
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
}