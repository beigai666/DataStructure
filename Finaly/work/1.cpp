#include <iostream>
#include "pch.h"
#include <String/String.h>
#include "Graph/MatrixGraph.h"
#include "Graph/ListGraph.h"
#include <pointer/SmartPointer.h>
#include <Array/StaticArray.h>
#include <Array/DynamicArray.h>
#include <List/StaticList.h>
#include <List/DynamicList.h>
#include <List/LinkList.h>
#include <List/StaticLinkList.h>
#include <List/CircleList.h>
#include <List/DualLinkList.h>
#include <List/DualCircleList.h>
#include <List/LinuxList.h>
#include <Stack/LinkStack.h>
#include <Stack/StaticStack.h>
#include <Queue/StaticQueue.h>
#include <Queue/LinkQueue.h>
#include <Tree/BTree.h>
#include <Graph/ListGraph.h>
#include <Graph/MatrixGraph.h>
using namespace std;
using namespace FinlayLib;

void teststring() {
	const char* s = "DTLib";
	String hello = "Hello: ";
	String str;
	str.insert(hello);
	str += s;
	cout << str.str() << endl;
	int index = str.indexOf(s);
	cout << "sub string index: " << index << endl;
	cout << "sub string: " << str.sub(index).str() << endl;
	str.replace(s, "Delphi Tang");
	cout << str.str() << endl;
}

void testPointer()
{
	SmartPointer<int> p1 = new int(1);
	SmartPointer<int> p2 = p1;
	cout << "p1: " << (!p1.isNull() ? *p1 : -1) << endl;
	cout << "p2: " << (!p2.isNull() ? *p2 : -1) << endl;
	SharedPointer<int> pp1;
	SharedPointer<int> pp2;
	pp1 = new int(2);
	pp2 = pp1;
	cout << "pp1: " << (!pp1.isNull() ? *pp1 : -1) << endl;
	cout << "pp2: " << (!pp2.isNull() ? *pp2 : -1) << endl;
}

void testsort() {
	int arr[] = { 3,1,2,5,4,6 };
	int len = sizeof(arr) / sizeof(*arr);
	cout << "min -> max: " << endl;
	Sort::Bubble(arr, len);
	for (int i = 0; i < len; i++)
	{
		cout << arr[i] << endl;
	}
	cout << "max -> min: " << endl;
	Sort::Quick(arr, len, false);
	for (int i = 0; i < len; i++)
	{
		cout << arr[i] << endl;
	}
}
void testArray()
{
	double arr[] = { 0.5,0.2,0.3,0.4,0.1 };
	int len = sizeof(arr) / sizeof(*arr);
	StaticArray<double, 10> sa;
	DynamicArray<double> da;
	da.resize(len);
	for (int i = 0; i < len; i++)
	{
		sa[i] = arr[i];
		da[i] = arr[i];
	}
	cout << "StaticArray: " << endl;
	for (int i = 0; i < sa.length(); i++)
	{
		cout << sa[i] << endl;
	}
	cout << "DynamicArray: " << endl;
	for (int i = 0; i < da.length(); i++)
	{
		cout << da[i] << endl;
	}
}

void testlist()
{
	cout << "static list" << endl;
	StaticList<int, 10> slist;
	for (int i = 0; i < 10; i++)
	{
		slist.insert(i);
	}
	for (int i = 0; i < slist.length(); i++)
	{
		cout << slist[i] << endl;
	}
	cout << "dynamic list" << endl;
	DynamicList<int> dlist(10);
	for (int i = 0; i < dlist.capacity(); i++)
	{
		dlist.insert(i);
	}
	for (int i = 0; i < dlist.length(); i++)
	{
		cout << dlist[i] << endl;
	}
	LinkList<int> linkList;
	cout << "link list" << endl;
	for (int i = 0; i < 10; i++)
	{
		linkList.insert(i);
	}
	for (int i = 0; i < linkList.length(); i++)
	{
		cout << linkList.get(i) << endl;
	}
	cout << "StaticLink list" << endl;
	StaticLinkList<int, 10> slinkList;
	for (int i = 0; i < slinkList.capacity(); i++)
	{
		slinkList.insert(i);
	}
	for (int i = 0; i < slinkList.length(); i++)
	{
		cout << slinkList.get(i) << endl;
	}
	cout << "Circle list" << endl;
	CircleList<int> circleList;
	for (int i = 0; i < 10; i++)
	{
		circleList.insert(i);
	}
	for (circleList.move(0); !circleList.end(); circleList.next())
	{
		cout << circleList.current() << endl;
		if (circleList.find(circleList.current()) == circleList.length() - 1)
		{
			break;
		}
	}
	cout << "DualLink list" << endl;
	DualLinkList<int> dualLinkList;
	for (int i = 0; i < 10; i++)
	{
		dualLinkList.insert(i);
	}
	for (dualLinkList.move(9); !dualLinkList.end(); dualLinkList.pre())
	{
		cout << dualLinkList.current() << endl;
	}
	cout << "DualLink list" << endl;
	DualCircleList<int> dualCircleList;
	for (int i = 0; i < 10; i++)
	{
		dualCircleList.insert(i);
	}
	for (dualCircleList.move(9); !dualCircleList.end(); dualCircleList.pre())
	{
		cout << dualCircleList.current() << endl;
		if (dualCircleList.find(dualCircleList.current()) == 0)
		{
			break;
		}
	}
}

void teststack()
{
	StaticStack<int, 10> s_stack;
	for (int i = 0; i < 10; i++)
	{
		s_stack.push(i);
	}
	while (s_stack.size() != 0)
	{
		cout << s_stack.top() << endl;
		s_stack.pop();
	}
	LinkStack<int> l_stack;
	for (int i = 0; i < 10; i++)
	{
		l_stack.push(i);
	}
	while (l_stack.size() != 0)
	{
		cout << l_stack.top() << endl;
		l_stack.pop();
	}
}

void testQueue()
{
	StaticQueue<int, 10> s_queue;
	for (int i = 0; i < 10; i++)
	{
		s_queue.add(i);
	}
	while (s_queue.length() != 0)
	{
		cout << s_queue.front() << endl;
		s_queue.remove();
	}
	LinkQueue<int> l_queue;
	for (int i = 0; i < 10; i++)
	{
		l_queue.add(i);
	}
	while (l_queue.length() != 0)
	{
		cout << l_queue.front() << endl;
		l_queue.remove();
	}
}

void testBTree()
{
	BTree<int> bt;
	BTreeNode<int>* node = NULL;
	bt.insert(1, NULL);
	node = bt.root();
	bt.insert(2, node);
	bt.insert(3, node);
	node = bt.find(2);
	bt.insert(4, node);
	bt.insert(5, node);
	node = bt.find(3);
	bt.insert(6, node, LEFT);
	bt.insert(7, node, RIGHT);
	node = bt.find(4);
	bt.insert(8, node, LEFT);
	bt.insert(9, node, RIGHT);
	cout << "After construct: " << endl;
	cout << "Height: " << bt.height() << endl;
	cout << "Count: " << bt.count() << endl;
	cout << "Degree: " << bt.degree() << endl;
	cout << "BFS to access node value:" << endl;
	for (bt.begin(); !bt.end(); bt.next())
	{
		cout << bt.curent() << endl;
	}
	SharedPointer< Array<int> > arr = bt.traversal(PreOrder);
	for (int i = 0; i < arr->length(); i++)
	{
		cout << (*arr)[i] << endl;
	}
}
void testListGraph()
{
	cout << "ListGraph" << endl;
	ListGraph<char, double> graph;
	graph.addVertex('A');
	graph.addVertex('B');
	graph.addVertex('C');
	graph.addVertex('D');
	graph.addVertex('E');
	graph.setEdge(0, 1, 0.2);
	graph.setEdge(0, 4, 1.0);
	graph.setEdge(1, 2, 0.3);
	graph.setEdge(1, 4, 0.7);
	graph.setEdge(2, 0, 0.4);
	graph.setEdge(2, 3, 0.4);
	graph.setEdge(2, 4, 0.3);
	graph.setEdge(3, 4, 0.5);
	graph.setEdge(4, 2, 0.2);
	SharedPointer<Array<int>> r = graph.dijkstra(0, 4, 0xffff);
	double d = 0;
	cout << graph.getVertex((*r)[0]);
	for (int i = 1; i < r->length(); i++)
	{
		d += graph.getEdge((*r)[i - 1], (*r)[i]);
		cout << " -> " << graph.getVertex((*r)[i]);
	}
	cout << endl;
	cout << "distance:" << d << endl;
}

void testMatrixGraph()
{
	cout << "MatrixGraph" << endl;
	MatrixGraph<5, char, double> graph;
	graph.setVertex(0, 'A');
	graph.setVertex(1, 'B');
	graph.setVertex(2, 'C');
	graph.setVertex(3, 'D');
	graph.setVertex(4, 'E');
	graph.setEdge(0, 1, 0.2);
	graph.setEdge(0, 4, 1.0);
	graph.setEdge(1, 2, 0.3);
	graph.setEdge(1, 4, 0.7);
	graph.setEdge(2, 0, 0.4);
	graph.setEdge(2, 3, 0.4);
	graph.setEdge(2, 4, 0.3);
	graph.setEdge(3, 4, 0.5);
	graph.setEdge(4, 2, 0.2);
	SharedPointer<Array<int>> r = graph.dijkstra(0, 4, 0xffff);
	double d = 0;
	cout << graph.getVertex((*r)[0]);
	for (int i = 1; i < r->length(); i++)
	{
		d += graph.getEdge((*r)[i - 1], (*r)[i]);
		cout << " -> " << graph.getVertex((*r)[i]);
	}
	cout << endl;
	cout << "distance:" << d << endl;
}