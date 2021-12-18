#pragma once

#include "LinuxList.h"
#include "DualLinkList.h"
#include <Exception/NoEnoughMemoryException.h>
namespace FinlayLib
{
	template <typename T>
	class DualCircleList : public DualLinkList<T>
	{
	protected:
		struct Node : public Object
		{
			list_head head;
			T value;
		};
		list_head m_header;
		list_head m_current;

		list_head* posotion(int i)
		{
			list_head* ret = const_cast<list_head*>(&m_header);
			for (int p = 0; p < i; p++)
			{
				ret = ret->next;
			}
			return ret;
		}

		int mod(int i) const {
			return (this->m_length == 0) ? 0 : (i % this->m_length);
		}

		bool insert(const T& e) {
			insert(this->m_length, e);
		}

		bool insert(int i, const T& e) {
			bool ret = true;
			Node* node = new Node();
			i = i % (this->m_length + 1);
			if (node != NULL) {
				node->value = e;
				list_add_tail(&node->head, posotion(i)->next);
				this->m_length++;
			}
			else
			{
				THEOW_EXCEPTION(NoEnoughMemoryException, "No memory to insert new element ...");
			}
			return ret;
		}

	public:
		DualCircleList() {
			this->m_length = 0;
			this->m_step = 1;
			m_current = NULL;
			INIT_HLIST_HEAD(&m_header);
		}
		~DualCircleList() {

		}

	private:

	};

}