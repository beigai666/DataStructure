// Finaly.cpp : 定义静态库的函数。
//
#include <Windows.h>
#include <iostream>
#include <Array/RangeArray.h>
#include <Queue/DualEndQueue.h>
#include <Tree/BTreeArray.h>
#include <Graph/ListGraph.h>
#include <Graph/MatrixGraph.h>
// TODO: 这是一个库函数示例
using namespace FinlayLib;
using namespace std;
bool IsSym(int n)
{
	DualEndQueue<int> q;
	if (n < 0) n = -n;
	while (n)
	{
		q.add(n % 10);
		n /= 10;
	}
	while ((q.length() > 1) && (q.front() == q.back()))
	{
		q.remove();
		q.dismiss();
	}
	return (q.length() <= 1);
}
template <typename V, typename E>
void bipartiteGraph(Graph<V, E>& g, int v, Array<bool>& visited, DynamicArray<int>& tag)
{
	if ((0 <= v) && (v < g.vCount()))
	{
		cout << v << endl;
		visited[v] = true;
		SharedPointer<Array<int>> aj = g.getAdjacent(v);
		for (int i = 0; i < aj->length(); i++)
		{
			if (tag[v] == tag[(*aj)[i]])
			{
				cout << "tag[" << v << "] = " << tag[v] << endl;
				cout << "tag[" << (*aj)[i] << "] = " << tag[(*aj)[i]] << endl;
				cout << "不是二分图" << endl;
				return;
			}
			else if(tag[(*aj)[i]]==0)
			{
				if (tag[v] == 1)
				{
					tag[(*aj)[i]] = 2;
				}
				else if(tag[v] == 2)
				{
					tag[(*aj)[i]] = 1;
				}
			}
			if (!visited[(*aj)[i]])
			{
				bipartiteGraph(g, (*aj)[i], visited,tag);
			}
		}
	}
	else
	{
		THROW_EXCEPTION(InvalidParameterException, "Index v is invalid ...");
	}
}

template <typename V, typename E>
void bipartiteGraph(Graph<V, E>& g, int v)
{
	DynamicArray<bool> visited(g.eCount());
	for (int i = 0; i < visited.length(); i++)
	{
		visited[i] = false;
	}
	DynamicArray<int> tag(g.eCount());
	for (int i = 0; i < tag.length(); i++)
	{
		tag[i] = 0;
	}
	tag[v] = 1;
	//bipartiteGraph<V,E>(g, v, visited,tag);
	bipartiteGraph(g, v, visited, tag);
	cout << "endl" << endl;
}
void bipartiteGraph()
{
	cout << "MatrixGraph" << endl;
	MatrixGraph<5, int, int> graph;
	graph.setVertex(0, 0);
	graph.setVertex(1, 1);
	graph.setVertex(2, 2);
	graph.setVertex(3, 3);
	graph.setEdge(0, 1, 1);
	graph.setEdge(0, 2, 1);
	graph.setEdge(0, 3, 1);
	graph.setEdge(1, 0, 1);
	graph.setEdge(1, 3, 1);
	graph.setEdge(2, 0, 1);
	graph.setEdge(2, 3, 1);
	graph.setEdge(3, 1, 1);
	graph.setEdge(3, 2, 1);
	graph.setEdge(3, 0, 1);
	bipartiteGraph<int, int>(graph,0);
}

template <typename V,typename E>
Graph<V, E>& GraphComplex()
{
	static ListGraph<V, E> g(9);
	g.setEdge(0, 1, 10);
	g.setEdge(1, 0, 10);
	g.setEdge(0, 5, 11);
	g.setEdge(5, 0, 11);

	g.setEdge(2, 1, 18);
	g.setEdge(1, 2, 18);
	g.setEdge(1, 8, 12);
	g.setEdge(8, 1, 12);
	g.setEdge(1, 6, 16);
	g.setEdge(6, 1, 16);

	g.setEdge(2, 3, 22);
	g.setEdge(3, 2, 22);
	g.setEdge(2, 8, 8);
	g.setEdge(8, 2, 8);

	g.setEdge(3, 8, 21);
	g.setEdge(8, 3, 21);
	g.setEdge(3, 6, 24);
	g.setEdge(6, 3, 24);
	g.setEdge(3, 7, 16);
	g.setEdge(7, 3, 16);
	g.setEdge(3, 4, 20);
	g.setEdge(4, 3, 20);

	g.setEdge(4, 5, 26);
	g.setEdge(5, 4, 26);
	g.setEdge(4, 7, 7);
	g.setEdge(7, 4, 7);

	g.setEdge(5, 6, 17);
	g.setEdge(6, 5, 17);

	g.setEdge(6, 7, 19);
	g.setEdge(7, 6, 19);
	return g;
}
void fnFinaly()
{
	int a[6] = { 1,2,6,4,5,3 };
	int len = sizeof(a) / sizeof(*a);
	cout <<"len:" << len << endl;
	BTreeArray<int> arr(log2(len) + 1);
	for (int i = 1, j = 0; j < len; i++, j++)
	{
		arr.set(i, a[j]);
	}
	if (arr.ToHeap())
	{
		for (int i = 1; i <= arr.count(); i++)
		{
			cout << arr[i] << endl;
		}
	}
	cout << arr.IsHeap(1) << endl;
	Graph<int, int>& g = GraphComplex<int,int>();
	//SharedPointer<Array<Edge<int>>> sa = g.myprim(65535);
	SharedPointer<Array<Edge<int>>> sa = g.mykruskal();
	for (size_t i = 0; i < sa->length(); i++)
	{
		Edge<int> e = (*sa)[i];
		cout <<"(" << e.b <<"," << e.e<<")=" << e.data << endl;
	}
	
}