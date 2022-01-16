#pragma once
#include "TreeNode.h"

namespace FinlayLib {
	template <typename T>
	class BTreeNode : public TreeNode<T>
	{
	protected:

	public:
		BTreeNode<T>* left;
		BTreeNode<T>* right;

		BTreeNode() {
			left = NULL;
			right = NULL;
		}
		~BTreeNode()
		{

		}

		static BTreeNode<T>* NewNode()
		{
			BTreeNode<T>* ret = new BTreeNode<T>();
			if (ret != NULL)
			{
				ret->m_flag = true;
			}
			return ret;
		}

	private:

	};
}
