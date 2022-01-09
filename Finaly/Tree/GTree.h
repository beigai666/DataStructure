#pragma once

#include <List/LinkList.h>
#include "GTreeNode.h"
#include "Tree.h"
namespace FinlayLib {
	template <typename T>
	class GTree : public Tree<T>
	{
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
		virtual SharePointer< Tree<T>>remove(TreeNode<T>* node) {
			return NULL;
		}
		virtual GTreeNode<T>* find(const T& value)const {
			return NULL;
		}
		virtual GTreeNode<T>* find(TreeNode<T>* node) const {
			return NULL;
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
			return 0;
		}

	private:

	};
}