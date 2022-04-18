#include <Stack/LinkStack.h>
#include <iostream>
using namespace std;
using namespace FinlayLib;


struct Node : public Object
{
	int value;
	Node* next;
	Node* prev;

	Node(int v = 0)
	{
		value = v;
		next = NULL;
		prev = NULL;
	}
};

int getBottom(LinkStack<int>& stack)
{
	int ret = 0;
	if (stack.size())
	{
		if (stack.size() > 1)
		{
			int tmp = stack.top();
			stack.pop();
			ret = getBottom(stack);
			stack.push(tmp);
		}
		else
		{
			ret = stack.top();
			stack.pop();
		}
	}
	else
	{
		THROW_EXCEPTION(InvalidOperationException, "No element in current stack...");
	}
	return ret;
}

Node* LastToHead(Node* last)
{
	Node* head = NULL;
	if (last && last->prev)
	{
		head = LastToHead(last->prev);
	}
	else if(last->prev==NULL)
	{
		head = last;
	}
	return head;
}

void ListToStack(Node* list, Stack<int>& stack)
{
	if (list)
	{
		stack.push(list->value);
		ListToStack(list->next, stack);
	}
	return;
}

void StackReverse2(LinkStack<int>& stack,Node * prev)
{
	if (stack.size())
	{
		Node node(stack.top());
		node.prev = prev;
		if(prev) prev->next = &node;
		stack.pop();
		StackReverse2(stack, &node);
	}
	else
	{
		ListToStack(LastToHead(prev), stack);
	}
	return;
}

void StackReverse1(LinkStack<int> &stack)
{
	if (stack.size())
	{
		int bottom = getBottom(stack);
		StackReverse1(stack);
		stack.push(bottom);
	}
	return;
}

void StackReverse()
{
	int a[] = { 8, 3, 2, 1, 5, 6, 7, 0, 4, 9 };
	int len = sizeof(a) / sizeof(*a);
	LinkStack<int> stack;

	for (int i = 0; i < len; i++)
	{
		stack.push(a[i]);
	}
	StackReverse1(stack);
	StackReverse2(stack,NULL);

	while (stack.size())
	{
		cout << stack.top() << " ";
		stack.pop();
	}

	cout << endl;
}

void Collide(int planet[], int n, Stack<int>& result)
{
	for (int i = 0; i < n; i++)
	{
		while (result.size() > 0 && result.top() > 0 && planet[i] < 0 && i < n)
		{
			int wt = abs(result.top());
			int wp = abs(planet[i]);
			if (wt > wp)
			{
				i++;
			}
			else if(wt==wp)
			{
				result.pop();
				i++;
			}
			else
			{
				result.pop();
			}
		}
		if(i<n)
		{
			result.push(planet[i]);
		}
		
	}
}

void PlanetCollision()
{
	int a[] = { 4, 5, -6, 4, 8, -5 };
	int len = sizeof(a) / sizeof(*a);
	LinkStack<int> stack;

	Collide(a, len, stack);
	StackReverse2(stack,NULL);

	while (stack.size())
	{
		cout << stack.top() << " ";
		stack.pop();
	}

	cout << endl;
}