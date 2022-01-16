#pragma once
#include <List/LinkList.h>
#include "TreeNode.h"

namespace FinlayLib {
	template <typename T>
	class GTreeNode : public TreeNode<T>
	{

	public:
		LinkList<GTreeNode<T>*> child;
		GTreeNode() {
			
		}
		~GTreeNode()
		{

		}
		static GTreeNode<T>* NewNode()
		{
			GTreeNode<T>* ret = new GTreeNode<T>();
			if (ret != NULL)
			{
				ret->m_flag = true;
			}
			return ret;
		}

	private:

	};
}

