#pragma once
#include "Stack.h"
#include <List/LinkList.h>
namespace FinlayLib {
	template<typename T>
	class  LinkStatck: public Stack<T>
	{
	protected:
		LinkList<T> m_list;

	public:
		LinkStatck()
		 {
		 }
		 ~LinkStatck()
		 {
		 }
		 void push(const T& e)
		 {
			 m_list.insert(0, e);
		 }

		 void pop()
		 {
			 if (m_list.length() > 0)
			 {
				 m_list.remove(0);
			 }
			 else
			 {
				 THEOW_EXCEPTION(InvalidOperationException, "No element in current stack ...");
			 }
		 }

		 T top()const
		 {
			 if (m_list.length() > 0)
			 {
				 return m_list.get(0);
			 }
			 else
			 {
				 THEOW_EXCEPTION(InvalidOperationException, "No element in current stack ...");
			 }
		 }
		 void clear()
		 {
			 m_list.clear();
		 }

		 int size()const
		 {
			 return m_list.length();
		 }

	private:

	};

}