#pragma once
#include "BTreeNode.h"

namespace FinlayLib
{
	template <typename T>
	class AVLTreeNode : public BTreeNode<T>
	{
	public:
		int bf;//ƽ������
		AVLTreeNode()
		{
			bf = 0;
		}
		~AVLTreeNode()
		{

		}
		static AVLTreeNode<T>* NewNode()
		{
			AVLTreeNode<T>* ret = new AVLTreeNode<T>();
			if (ret != NULL)
			{
				ret->m_flag = true;
			}
			return ret;
		}
	private:

	};

}