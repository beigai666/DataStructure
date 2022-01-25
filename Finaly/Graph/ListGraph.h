#pragma once
#include "Graph.h"
#include <List/LinkList.h>
namespace FinlayLib
{
	template<typename V,typename E>
	class ListGraph : public Graph<V,E>
	{
	protected:
		struct Vertex : public Object
		{
			V* data;
			LinkList<Edge<E>> edge;
			Vertex() {
				data = NULL;
			}
		};
		LinkList<Vertex*> m_list;
	public:
		ListGraph(unsigned int n = 0)
		{
			for (unsigned i = 0; i < n; i++)
			{
				addVertex();
			}
		}
		int addVertex()
		{
			int ret = -1;
			Vertex* v = new Vertex();
			if (v != NULL)
			{
				m_list.insert(v);
				ret = m_list.length()-1;
			}
			else
			{
				THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new vertex object ...");
			}
			return ret;
		}
		int addVertex(const V& value)
		{
			int ret = addVertex();
			if (ret >= 0)
			{
				setVertex(ret, value);
			}
			return ret;
		}
		bool setVertex(int i, const V& value)
		{
			int ret = ((0 <= i) && (i < vCount()));
			if (ret)
			{
				Vertex* vertex = m_list.get(i);
				V* data = vertex->data;
				if (data == NULL)
				{
					data = new V();
				}
				if (data != NULL)
				{
					*data = value;
					vertex->data = data;
				}
				else
				{
					THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new vertex value ...");
				}
			}
			return ret;
		}

		V getVertex(int i)
		{
			V ret;
			if (!getVertex(i, ret))
			{
				THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ...");
			}
			return ret;
		}

		virtual bool getVertex(int i, V& value)
		{
			bool ret = (0 <= i) && (i < vCount());
			if (ret)
			{
				Vertex* vertex = m_list.get(i);
				if (vertex->data != NULL)
				{
					value = *(vertex->data);
				}
				else
				{
					THROW_EXCEPTION(InvalidOperationException, "No value assigned to this vertex ...");
				}
			}
			return ret;
		}
		void removeVertex()
		{
			if (m_list.length() > 0)
			{
				int index = m_list.length() - 1;
				Vertex* v = m_list.get(index);
				if (m_list.remove(index)) {
					for (int i = (m_list.move(0), 0); !m_list.end(); m_list.next(), i++)
					{
						int pos = m_list.current()->edge.find(Edge<E>(i, index));
						if (pos >= 0)
						{
							m_list.current()->edge.remove(pos);
						}
					}
					delete v->data;
					delete v;
				}
				
			}
			else
			{
				THROW_EXCEPTION(InvalidOperationException, "No vertex in current graph ...");
			}
		}
		virtual SharedPointer< Array<int> > getAdjacent(int i)
		{
			DynamicArray<int> *array = NULL;
			if ((0 <= i) && (i < vCount()))
			{
				Vertex* v = m_list.get(i);
				array = new DynamicArray<int>(v->edge.length());
				if (array) {
					for (int k = (v->edge.move(0), 0); !v->edge.end(); v->edge.next(), k++)
					{
						array->set(k, v->edge.current().e);
					}
				}
				else
				{
					THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create ret object ...");
				}
			}
			else
			{
				THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ...");
			}
			return array;
		}
		virtual bool isAdjacent(int i, int j)
		{
			return (0 <= i) && (i < vCount()) && (0 <= j) && (j < vCount()) && (m_list.get(i)->edge.find(Edge<E>(i, j))>=0);
		}
		virtual E getEdge(int i, int j)
		{
			E ret;
			if (!getEdge(i, j, ret))
			{
				THROW_EXCEPTION(InvalidParameterException, "Edge <i, j> is invalid ...");
			}
			return ret;
		}
		virtual bool getEdge(int i, int j, E& value)
		{
			bool ret = (0 <= i) && (i < vCount()) && (0 <= j) && (j < vCount());
			if (ret)
			{
				Vertex* ver = m_list.get(i);
				int index = ver->edge.find(Edge<E>(i, j));
				if(index>=0)
				{
					value = ver->edge.get(index).data;
				}
				else
				{
					THROW_EXCEPTION(InvalidOperationException, "No value assigned to this edge ...");
				}
			}
			return ret;
		}
		virtual bool setEdge(int i, int j, const E& value)
		{
			bool ret = (0 <= i) && (i < vCount()) && (0 <= j) && (j < vCount());
			if (ret)
			{
				Vertex* ver = m_list.get(i);
				int pos = ver->edge.find(Edge<E>(i, j));
				if (pos >= 0)
				{
					ver->edge.set(pos,Edge<E>(i, j, value));
				}
				else
				{
					ver->edge.insert(0,Edge<E>(i,j,value));
				}
			}
			return ret;
		}
		virtual bool removeEdge(int i, int j)
		{
			bool ret = (0 <= i) && (i < vCount()) && (0 <= j) && (j < vCount());
			if (ret)
			{
				Vertex* ver = m_list.get(i);
				int pos = ver->edge.find(Edge<E>(i, j));
				if (pos >= 0)
				{
					ver->edge.remove(pos);
				}
			}
			return ret;
		}
		virtual int vCount()
		{
			return m_list.length();
		}
		virtual int eCount()
		{
			int ret = 0;
			for (m_list.move(0); !m_list.end(); m_list.next())
			{
				ret += m_list.current()->edge.length();
			}
			return ret;
		}
		virtual int OD(int i)
		{
			int ret = 0;

			if ((0 <= i) && (i < vCount()))
			{
				ret = m_list.get(i)->edge.length();
			}
			else
			{
				THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ...");
			}

			return ret;
		}
		virtual int ID(int i)
		{
			int ret = 0;
			if ((0 <= i) && (i < vCount()))
			{
				for (m_list.move(0); !m_list.end(); m_list.next())
				{
					LinkList< Edge<E> >& edge = m_list.current()->edge;
					for (edge.move(0); !edge.end(); edge.next())
					{
						if (edge.current().e == i)
						{
							ret++;
							break;
						}
					}
				}
			}
			return ret;
		}
		~ListGraph()
		{
			while (m_list.length() > 0)
			{
				Vertex* toDel = m_list.get(0);
				m_list.remove(0);
				delete toDel->data;
				delete toDel;
			}
		}
	private:

	};

}