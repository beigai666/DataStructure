#include <Windows.h>
#include <Graph/MatrixGraph.h>
#include <Graph/ListGraph.h>
#include <iostream>
using namespace FinlayLib;
bool SetMark(Graph<int, int>& g, Array<int>& mark,int i,int flag)
{
	bool ret = true;
	if (mark[i] == -1)
	{
		mark[i] = flag;
		SharedPointer<Array<int>>p =  g.getAdjacent(i);
		for (int j = 0; ret&&(j < p->length()); j++)
		{
			ret = SetMark(g, mark, (*p)[j], 1 - mark[i]) && (mark[(*p)[j]] != mark[i]);
		}
	}
	return ret;
}

bool IsBipartite(Graph<int, int>& g)
{
	bool ret = true;
	DynamicArray<int> mark(g.vCount());
	for (int i = 0; i < mark.length(); i++)
	{
		mark[i] = -1;
	}
	for (int i = 0; ret && (i < mark.length()); i++)
	{
		ret = SetMark(g, mark, i, 0);
	}
	return ret;
}

void BigprtiteGraph()
{
	MatrixGraph<4, int, int> graph;
	for (int i = 0; i < graph.vCount(); i++)
	{
		graph.setVertex(i, 1);
	}
	graph.setEdge(0, 1, 1);
	graph.setEdge(1, 0, 1);
	graph.setEdge(0, 3, 1);
	graph.setEdge(3, 0, 1);
	graph.setEdge(1, 2, 1);
	graph.setEdge(2, 1, 1);
	graph.setEdge(2, 3, 1);
	graph.setEdge(3, 2, 1);

	//graph.setEdge(2, 0, 1);
	//graph.setEdge(0, 2, 1);

	std::cout << IsBipartite(graph) << std::endl;
}
void updateMinDistance(Graph<int, int>& g, int v, Array<int>& r)
{
	SharedPointer<Array<int>> p = g.getAdjacent(v);
	Array<int>& adj = *p;
	for (int i = 0; i < adj.length(); i++)
	{
		if (r[adj[i]] > (r[v] + 1))
		{
			r[adj[i]] = r[v] + 1;
			updateMinDistance(g, adj[i], r);
		}
	}
}
void MinDistance(Graph<int, int>& g, int v, Array<int>& path, Array<int>& r)
{
	path[v] = 1;
	if (g.getVertex(v))
	{
		if (r[v] == -1)
		{
			SharedPointer<Array<int>> p = g.getAdjacent(v);
			Array<int>& adj = *p;
			for (int i = 0; i < adj.length(); i++)
			{
				if (g.getVertex(adj[i]) == 0)
				{
					r[v] = 1;
					break;
				}
			}
			if (r[v] == -1)
			{
				for (int i = 0; i < adj.length(); i++)
				{
					if (!path[adj[i]])
					{
						MinDistance(g, adj[i], path, r);
					}
				}
				int dis = -1;
				for (int i = 0; i < adj.length(); i++)
				{
					if ((unsigned int)dis>((unsigned int)r[adj[i]]))
					{
						dis = r[adj[i]];
					}
				}
				if (dis != -1)
				{
					r[v] = dis + 1;
				}
				updateMinDistance(g, v, r);
			}
		}
	}
	else
	{
		r[v] = 0;
	}
	path[v] = 0;
}

DynamicArray<int> MatrixMinDistance(Graph<int, int>& g)
{
	DynamicArray<int> ret(g.vCount());
	DynamicArray<int> path(g.vCount());
	for (int i = 0; i < ret.length(); i++)
	{
		ret[i] = -1;
		path[i] = 0;
	}
	for (int i = 0; i < g.vCount(); i++)
	{
		MinDistance(g, i, path, ret);
	}
	return ret;
}

void MatrixMinDistance()
{
	const int ROW = 5;
	const int COL = 5;
	int matrix[5][5] =
	{
		{0,0,0,0,0},
		{1,1,1,1,1},
		{1,1,1,1,1},
		{1,1,1,1,1},
		{1,1,1,1,1}
	};
	ListGraph<int, int> g(ROW * COL);
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			g.setVertex(i * COL + j, matrix[i][j]);
		}
	}
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL-1; j++)
		{
			g.setEdge(i * COL + j, i * COL + j + 1, 1);
			g.setEdge(i * COL + j + 1, i * COL + j, 1);
		}
	}

	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL-1; j++)
		{
			g.setEdge(j * COL + i, (j + 1) * COL + i, 1);
			g.setEdge((j + 1) * COL + i, j * COL + i, 1);
		}
	}
	DynamicArray<int> d = MatrixMinDistance(g);
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			std::cout << d[i * COL + j] << " ";
		}
		std::cout << std::endl;
	}
}