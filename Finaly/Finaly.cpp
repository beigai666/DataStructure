// Finaly.cpp : 定义静态库的函数。
//
#include <Windows.h>
#include <iostream>
#include "pch.h"
#include "Graph/MatrixGraph.h"
#include "Graph/ListGraph.h"
using namespace std;
using namespace FinlayLib;


// TODO: 这是一个库函数示例
void fnFinaly()
{
	
	try
	{
		ListGraph<char, int> g;
		g.addVertex('A');
		g.addVertex('B');
		g.addVertex('C');
		g.addVertex('D');
		//g.removeVertex();
		for (int i = 0; i < g.vCount(); i++)
		{
			cout << i << " : " << g.getVertex(i) << endl;
		}
		g.setEdge(0, 1, 5);
		g.setEdge(0, 3, 5);
		g.setEdge(1, 2, 8);
		g.setEdge(2, 3, 2);
		g.setEdge(3, 1, 9);
		cout << "W(0,1) : " << g.getEdge(0, 1) << endl;
		cout << "W(0,3) : " << g.getEdge(0, 3) << endl;
		cout << "W(1,2) : " << g.getEdge(1, 2) << endl;
		cout << "W(2,3) : " << g.getEdge(2, 3) << endl;
		cout << "W(3,1) : " << g.getEdge(3, 1) << endl;
		//
		//cout << "W(3,1) : " << g.getEdge(3, 1) << endl;
		cout << "eCount:" << g.eCount()<<endl;
		cout << "vCount:" << g.vCount() << endl;
		//g.removeEdge(3, 1);
		cout << "eCount:" << g.eCount() << endl;
		cout << "vCount:" << g.vCount() << endl;
		SharedPointer<Array<int>>aj = g.getAdjacent(0);
		for (int i = 0; i < aj->length(); i++)
		{
			cout << (*aj)[i] << endl;
		}
		cout << "ID(0)" << g.ID(0) << endl;
		cout << "OD(0)" << g.OD(0) << endl;
		cout << "ID(1)" << g.ID(1) << endl;
		cout << "OD(1)" << g.OD(1) << endl;
		cout << "ID(1)" << g.TD(1) << endl;
		g.removeVertex();
		cout << "eCount:" << g.eCount() << endl;
		cout << "vCount:" << g.vCount() << endl;
		cout << "W(0,1) : " << g.getEdge(0, 1) << endl;
		cout << "W(1,2) : " << g.getEdge(1, 2) << endl;
		cout << "W(0,3) : " << g.getEdge(0, 3) << endl;
	}
	catch (Exception & e)
	{
		cout << e.location() << endl;
		cout << e.message() << endl;
	}
	
}