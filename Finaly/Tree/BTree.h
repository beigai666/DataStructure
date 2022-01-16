#pragma once

#include <List/LinkList.h>
#include <Exception/InvalidParameterException.h>
#include <Exception/InvalidOperationException.h>
#include "BTreeNode.h"
#include "Tree.h"
#include <Queue/LinkQueue.h>
namespace FinlayLib {
	template <typename T>
	class BTree : public Tree<T>
	{
	protected:
		

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
			bool ret = true;
			return ret;
		}
		virtual bool insert(const T& value, TreeNode<T>* parent)
		{
			bool ret = true;
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
		virtual TreeNode<T>* find(const T& value)const
		{
			return NULL;
		}
		virtual TreeNode<T>* find(TreeNode<T>* node) const
		{
			return NULL;
		}
		virtual TreeNode<T>* root() const
		{
			return NULL;
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