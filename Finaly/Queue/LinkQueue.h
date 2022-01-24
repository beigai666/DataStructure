#pragma once
#include "Queue.h"
#include <List/LinuxList.h>
#include <Exception/InvalidOperationException.h>
namespace FinlayLib {
	template <typename T>
	class LinkQueue : public Queue<T>
	{

	protected:
		struct Node : public Object
		{
			list_head head;
			T value;
		};
		list_head m_header;
		int m_length;
	public:
		LinkQueue() {
			m_length = 0;
			INIT_LIST_HEAD(&m_header);
		}
		~LinkQueue() {
			clear();
		}
		virtual void add(const T& e) {
			Node* node = new Node();
			if (node != NULL) {
				node->value = e;
				list_add_tail(&node->head, &m_header);
				m_length++;
			}
			else
			{
				THROW_EXCEPTION(InvalidOperationException, "No memory to add new element ...");
			}
		}
		virtual void remove() {
			if (m_length > 0) {
				list_head* toDel = m_header.next;
				list_del(toDel);
				m_length--;
				delete list_entry(toDel, Node, head);
			}
			else {
				THROW_EXCEPTION(InvalidOperationException, "No element in current queue ...");
			}
		}
		virtual T front()const {
			if (m_length > 0) {
				return list_entry(m_header.next,Node,head)->value;
			}
			else {
				THROW_EXCEPTION(InvalidOperationException, "No element in current queue ...");
			}
		}
		virtual void clear() {
			while (m_length>0)
			{
				remove();
			}
		}
		virtual int length()const {
			return m_length;
		}
	private:

	};
}

