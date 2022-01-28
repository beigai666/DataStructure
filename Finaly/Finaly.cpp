// Finaly.cpp : 定义静态库的函数。
//
#include <Windows.h>
#include <iostream>
#include "pch.h"
#include "Graph/MatrixGraph.h"
#include "Graph/ListGraph.h"
using namespace std;
using namespace FinlayLib;

void print(int var)
{
	cout << var << endl;
}
// TODO: 这是一个库函数示例
void fnFinaly()
{
	
	try
	{
		MatrixGraph<9, char, int> g;
		const char* VD = "ABEDCGFHI";
		for (int i = 0; i < 9; i++)
		{
			g.setVertex(i, i);
		}
		g.setEdge(0, 1, 10);
		g.setEdge(1, 0, 10);
		g.setEdge(0, 5, 11);
		g.setEdge(5, 0, 11);

		g.setEdge(1, 2, 18);
		g.setEdge(2, 1, 18);
		g.setEdge(1, 6, 16);
		g.setEdge(6, 1, 16);
		g.setEdge(1, 8, 12);
		g.setEdge(8, 1, 12);

		g.setEdge(2, 8, 8);
		g.setEdge(8, 2, 8);
		g.setEdge(2, 3, 22);
		g.setEdge(3, 2, 22);

		g.setEdge(3, 8, 21);
		g.setEdge(8, 3, 21);
		g.setEdge(3, 6, 24);
		g.setEdge(6, 3, 24);
		g.setEdge(3, 7, 16);
		g.setEdge(7, 3, 16);
		g.setEdge(3, 4, 20);
		g.setEdge(4, 3, 20);

		g.setEdge(4, 7, 7);
		g.setEdge(7, 4, 7);
		g.setEdge(4, 5, 26);
		g.setEdge(5, 4, 26);

		g.setEdge(5, 6, 17);
		g.setEdge(6, 5, 17);

		g.setEdge(6, 7, 19);
		g.setEdge(7, 6, 19);
		int w = 0;
		//SharedPointer< Array< Edge<int> > > sa= g.prim(65535);
		SharedPointer< Array< Edge<int> > > sa = g.kruskal();
		for (int i = 0; i < sa->length(); i++)
		{
			w += (*sa)[i].data;
			cout << (*sa)[i].b << " " << (*sa)[i].e <<" " << (*sa)[i].data << endl;
		}
		cout << "Weight: " << w << endl;
	}
	catch (Exception & e)
	{
		cout << e.location() << endl;
		cout << e.message() << endl;
	}
	
}