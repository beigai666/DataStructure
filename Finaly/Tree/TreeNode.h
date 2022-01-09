#pragma once
#include <Object/Object.h>

namespace FinlayLib {
	template <typename T>
	class TreeNode : public Object
	{
	public:
		T value;
		TreeNode<T>* parent;
		TreeNode()
		{
			parent = NULL;
		}

		virtual ~TreeNode() = 0;
	private:

	};
}

