#pragma once
#include <Object/Object.h>

namespace FinlayLib {
	template <typename T>
	class TreeNode : public Object
	{
	protected:
		bool m_flag;

		void* operator new(size_t size)throw()
		{
			return Object::operator new(size);
		}


		TreeNode(const TreeNode<T>&);

		TreeNode<T>& operator= (const TreeNode<T>&);

	public:
		T value;
		TreeNode<T>* parent;
		TreeNode()
		{
			m_flag = false;
			parent = NULL;
		}
		bool flag()
		{
			return m_flag;
		}
		virtual ~TreeNode() {

		}
	private:

	};
}

