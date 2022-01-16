#pragma once

#include <List/LinkList.h>
#include <Exception/InvalidParameterException.h>
#include <Exception/InvalidOperationException.h>
#include "GTreeNode.h"
#include "Tree.h"
#include <Queue/LinkQueue.h>
namespace FinlayLib {
	template <typename T>
	class GTree : public Tree<T>
	{
	protected:

		LinkQueue<GTreeNode<T>*> m_queue;

		GTree(const GTree<T>&);

		GTree<T>& operator= (const GTree<T>&);

		GTreeNode<T>* find(GTreeNode<T>* node, const T& value)const
		{
			GTreeNode<T>* ret = NULL;
			if (node != NULL)
			{
				if (node->value == value)
				{
					return node;
				}
				else
				{
					for (node->child.move(0); !node->child.end() && (ret == NULL); node->child.next())
					{
						ret = find(node->child.current(), value);
					}
				}
			}
			return ret;
		}

		GTreeNode<T>* find(GTreeNode<T>* node, const TreeNode<T>* obj)const
		{
			GTreeNode<T>* ret = NULL;
			if (node == obj)
			{
				return node;
			}
			else
			{
				if (node != NULL) {
					for (node->child.move(0); !node->child.end() && (ret == NULL); node->child.next())
					{
						ret = find(node->child.current(), obj);
					}
				}

			}
			return ret;
		}

		void free(GTreeNode<T>* node)
		{
			if (node != NULL)
			{
				for (node->child.move(0); !node->child.end(); node->child.next())
				{
					free(node->child.current());
				}
				//std::cout <<"free: " << node->value << endl;
				if (node->flag()) {
					delete node;
				}
				
			}
		}
		void remove(GTreeNode<T>* node, GTree<T>*& ret)
		{
			ret = new GTree<T>();
			if (ret == NULL)
			{
				THEOW_EXCEPTION(NoEnoughMemoryException, "No memory to create new tree ...");
			}
			else
			{
				if (root() == node)
				{
					this->m_root = NULL;
				}
				else
				{
					LinkList<GTreeNode<T>*>& child = dynamic_cast<GTreeNode<T>*>(node->parent)->child;
					child.remove(child.find(node));
					node->parent = NULL;
				}
				ret->m_root = node;
			}
		}

		int count(GTreeNode<T>* node) const
		{
			int ret = 0;
			if (node != NULL)
			{
				ret = 1;
				for (node->child.move(0); !node->child.end(); node->child.next())
				{
					ret += count(node->child.current());
				}
			}
			return ret;
		}

		int height(GTreeNode<T>* node)const
		{
			int ret = 0;
			if (node != NULL)
			{
				for (node->child.move(0); !node->child.end(); node->child.next())
				{
					int h= height(node->child.current());
					if (ret < h)
					{
						ret = h;
					}
				}
				ret += 1;
			}
			return ret;
		}

		int degree(GTreeNode<T>* node)const
		{
			int ret = 0;
			if (node != NULL)
			{
				ret = node->child.length();
				for (node->child.move(0); !node->child.end(); node->child.next())
				{
					int d = degree(node->child.current());
					if (ret < d)
					{
						ret = d;
					}
				}
			}
			return ret;
		}

	public:
		GTree()
		{

		}
		~GTree()
		{
			clear();
		}

		virtual bool insert(TreeNode<T>* node)
		{
			bool ret = true;
			if (node != NULL) {
				if (this->m_root == NULL) {
					node->parent = NULL;
					this->m_root = node;
				}
				else
				{
					GTreeNode<T>* np = find(node->parent);
					if (np != NULL)
					{
						GTreeNode<T>* n = dynamic_cast<GTreeNode<T>*>(node);
						if (np->child.find(n) < 0)
						{
							np->child.insert(n);
						}
					}
					else
					{
						THEOW_EXCEPTION(InvalidParameterException, "Invalid parent tree node ...");
					}
				}
			}
			else
			{
				THEOW_EXCEPTION(InvalidParameterException, "Parameter node cannot be NULL ...");
			}
			
			return ret;
		}
		virtual bool insert(const T& value, TreeNode<T>* parent)
		{
			bool ret = true;
			GTreeNode<T>* node = GTreeNode<T>::NewNode();
			if (node != NULL) {
				node->value = value;
				node->parent = parent;
				insert(node);
			}
			else
			{
				THEOW_EXCEPTION(NoEnoughMemoryException, "No memory to create new tree node ...");
			}
			return ret;
		}
		virtual SharePointer< Tree<T>>remove(const T& value)
		{
			GTree<T>* ret = NULL;
			GTreeNode<T>* node = find(value);
			if (node == NULL)
			{
				THEOW_EXCEPTION(InvalidParameterException, "Can not find node via parameter value ...");
			}
			else
			{
				remove(node, ret);
				m_queue.clear();
			}
			return ret;
		}
		virtual SharePointer< Tree<T>>remove(TreeNode<T>* node) {
			GTree<T>* ret = NULL;
			node = find(node);
			if (node == NULL)
			{
				THEOW_EXCEPTION(InvalidParameterException, "Parameter node is invalid ...");
			}
			else
			{
				remove(dynamic_cast<GTreeNode<T>*>(node), ret);
				m_queue.clear();
			}
			return ret;
		}
		virtual GTreeNode<T>* find(const T& value)const {
			return find(root(),value);
		}
		virtual GTreeNode<T>* find(TreeNode<T>* node) const {
			return find(root(),node);
		}
		virtual GTreeNode<T>* root() const {
			return dynamic_cast<GTreeNode<T>*> (this->m_root);
		}
		virtual int degree()const {
			GTreeNode<T>* node = root();
			return degree(node);
		}
		virtual int count()const {
			GTreeNode<T>* node = root();
			return count(node);
		}
		virtual int height() const {
			GTreeNode<T>* node = root();
			return height(node);
		}
		virtual void clear() {
			free(root());
			this->m_root = NULL;
			m_queue.clear();
			return;
		}

		bool begin()
		{
			bool ret = (root() != NULL);
			if (ret)
			{
				m_queue.clear();
				m_queue.add(root());
			}
			return ret;
		}

		bool end()
		{
			return (m_queue.length() == 0);
		}

		bool next()
		{
			bool ret = (m_queue.length() > 0);
			if (ret) {
				GTreeNode<T>* node = m_queue.front();
				m_queue.remove();
				for (node->child.move(0); !node->child.end(); node->child.next())
				{
					m_queue.add(node->child.current());
				}
			}
			return ret;
		}
		T current()
		{
			if (!end())
			{
				GTreeNode<T>* node = m_queue.front();
				return node->value;
			}
			else
			{
				THEOW_EXCEPTION(InvalidOperationException, "No value at current position ...");
			}
		}
	private:

	};
}