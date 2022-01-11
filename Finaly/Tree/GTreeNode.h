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
	private:

	};
}

