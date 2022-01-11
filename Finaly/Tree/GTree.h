#pragma once

#include <List/LinkList.h>
#include <Exception/InvalidParameterException.h>
#include "GTreeNode.h"
#include "Tree.h"
namespace FinlayLib {
	template <typename T>
	class GTree : public Tree<T>
	{
	protected:
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

	public:
		GTree()
		{

		}
		~GTree()
		{

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
			GTreeNode<T>* node = new GTreeNode<T>();
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
			return NULL;
		}
		virtual SharePointer< Tree<T>>remove(TreeNode<T>* node) {
			return NULL;
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
			return 0;
		}
		virtual int count()const {
			return 0;
		}
		virtual int height() const {
			return 0;
		}
		virtual void clear() {
			return;
		}

	private:

	};
}