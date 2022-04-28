#pragma once
#include "BTreeNode.h"

namespace FinlayLib
{
#define LH +1
#define EH  0
#define RH -1
	template <typename T>
	class AVLTreeNode : public BTreeNode<T>
	{
	public:
		int bf;//Æ½ºâÒò×Ó
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