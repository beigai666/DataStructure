#pragma once

#include <List/LinkList.h>
#include <Exception/InvalidParameterException.h>
#include <Exception/InvalidOperationException.h>
#include "BTreeNode.h"
#include "Tree.h"
#include <Queue/LinkQueue.h>
namespace FinlayLib {

	enum BTNodePos
	{
		ANY,
		LEFT,
		RIGHT
	};

	template <typename T>
	class BTree : public Tree<T>
	{
	protected:
		virtual BTreeNode<T>* find(BTreeNode<T>* node, const T& value)const
		{
			BTreeNode<T>* ret = NULL;
			if (node != NULL)
			{
				if (node->value == value)
				{
					ret = node;
				}
				else
				{
					if (ret == NULL)
					{
						ret = find(node->left, value);
					}
					if (ret == NULL)
					{
						ret = find(node->right, value);
					}
				}
			}
			return ret;
		}

		virtual BTreeNode<T>* find(BTreeNode<T>* node, const TreeNode<T>* obj)const
		{
			BTreeNode<T>* ret = NULL;
			if (node != NULL)
			{
				if (node == obj)
				{
					ret = node;
				}
				else
				{
					if (ret == NULL)
					{
						ret = find(node->left, obj);
					}
					if (ret == NULL)
					{
						ret = find(node->right, obj);
					}
				}
			}
			return ret;
		}

		virtual bool insert(BTreeNode<T>* n, BTreeNode<T>* np, BTNodePos pos)
		{
			bool ret = true;
			if (pos == ANY)
			{
				if (np->left == NULL)
				{
					np->left = n;
				}
				else if(np->right == NULL)
				{
					np->right = n;
				}
				else
				{
					ret = false;
				}
			}
			else if(pos == LEFT)
			{
				if (np->left == NULL)
				{
					np->left = n;
				}
				else
				{
					ret = false;
				}
			}
			else if(pos == RIGHT)
			{
				if (np->right == NULL)
				{
					np->right = n;
				}
				else
				{
					ret = false;
				}
			}
			else
			{
				ret = false;
			}
			return ret;

		}

	public:
		BTree()
		{

		}
		~BTree()
		{
			clear();
		}
		virtual bool insert(TreeNode<T>* node)
		{
			return insert(node,ANY);
		}

		virtual bool insert(TreeNode<T>* node, BTNodePos pos)
		{
			bool ret = false;
			if (node != NULL)
			{
				if (this->m_root == NULL)
				{
					node->parent = NULL;
					this->m_root = node;
					ret = true;
				}
				else
				{
					BTreeNode<T>* np = find(node->parent);
					if (np != NULL)
					{
						ret = insert(dynamic_cast<BTreeNode<T>*>(node), np, pos);
					}
					else
					{
						THEOW_EXCEPTION(InvalidParameterException, "Invalid parent tree node ...");
					}
				}
			}
			else
			{
				THEOW_EXCEPTION(InvalidParameterException, "Parameter node can not be NULL");
			}
			return ret;
		}
		virtual bool insert(const T& value, TreeNode<T>* parent)
		{
			return insert(value, parent, ANY);
		}

		virtual bool insert(const T& value, TreeNode<T>* parent,BTNodePos pos)
		{
			bool ret = false;
			BTreeNode<T>* node = BTreeNode<T>::NewNode();
			if (node == NULL)
			{
				THEOW_EXCEPTION(NoEnoughMemoryException, "No memory to cretae new node ...");
			}
			else
			{
				node->value = value;
				node->parent = parent;
				ret = insert(node, pos);
				if (!ret)
				{
					delete node;
				}
			}
			return ret;
		}
		virtual SharePointer< Tree<T>>remove(const T& value)
		{
			return NULL;
		}
		virtual SharePointer< Tree<T>>remove(TreeNode<T>* node) 
		{
			return NULL;
		}
		virtual BTreeNode<T>* find(const T& value)const
		{
			return find(root(),value);
		}
		virtual BTreeNode<T>* find(TreeNode<T>* node) const
		{
			return find(root(), node);
		}
		virtual BTreeNode<T>* root() const
		{
			return dynamic_cast<BTreeNode<T>*> (this->m_root);;
		}
		virtual int degree()const
		{
			return 0;
		}
		virtual int count()const
		{
			return 0;
		}
		virtual int height() const
		{
			return 0;
		}
		virtual void clear()
		{
			return ;
		}

	};
}