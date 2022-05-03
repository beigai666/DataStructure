#pragma once
#include "BTreeNode.h"
namespace FinlayLib
{
	enum Color
	{
		BLACK,
		RED
	};
	template <typename T>
	class RBTreeNode : public  BTreeNode<T>
	{

	public:
		Color color;
		RBTreeNode()
		{
			color = RED;
		}
		~RBTreeNode()
		{

		}
		static RBTreeNode<T>* NewNode()
		{
			RBTreeNode<T>* ret = new RBTreeNode<T>();
			if (ret != NULL)
			{
				ret->m_flag = true;
			}
			return ret;
		}
	private:

	};

}