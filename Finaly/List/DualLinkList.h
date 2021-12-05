#pragma once
#include "List.h"
#include <Exception/InvalidOperationException.h>
namespace FinlayLib {
	template<typename T>
	class DualLinkList : public List<T>
	{
	protected:
		struct Node : public Object
		{
			T value;
			Node* next;
			Node* pre;
		};
		mutable struct : public Object
		{
			char reserved[sizeof(T)];
			Node* next;
			Node* pre;
		}m_header;

		int m_length;
		int m_step;
		Node* m_current;
		Node* position(int i) const {
			Node* ret = reinterpret_cast<Node*>(&m_header);
			for (int p = 0; p < i; p++)
			{
				ret = ret->next;
			}
			return ret;
		}
		virtual  Node* create() {
			return new Node();
		}

		virtual void destory(Node* pn) {
			delete pn;
		}
	public:
		DualLinkList() {
			this->m_header.next = NULL;
			this->m_header.pre=NULL;
			this->m_length = 0;
			this->m_step = 1;
			this->m_current = NULL;
		}
		~DualLinkList() {
			clear();
		}



		virtual bool insert(int i, const T& e) {
			bool ret = ((0 <= i) && (i <= m_length));
			if (ret) {
				Node* node = create();
				
				if (node != NULL) {
					Node* current = position(i);
					Node* next = current->next;
					node->value = e;
					node->next = next;
					current->next = node;
					if (current != reinterpret_cast<Node*>(&m_header))
					{
						node->pre = current;
					}
					else
					{
						node->pre = NULL;
					}
					if (next != NULL) {
						next->pre = node;
					}
					m_length++;
				}
				else
				{
					THEOW_EXCEPTION(NoEnoughMemoryException, "No memory to insert new element ...");
				}
			}
			return ret;
		}
		virtual bool insert(const T& e) {
			return insert(this->m_length, e);
		}
		virtual bool remove(int i) {
			bool ret = ((0 <= i) && (i < m_length));
			if (ret) {
				Node* current = position(i);
				
				Node* toDel = current->next;
				Node* next = toDel->next;
				if (m_current == toDel) {
					m_current = next;
				}
				current->next = next;
				if (next != NULL)
				{
					next->pre = toDel->pre;
				}
				m_length--;
				destory(toDel);;
			}
			return ret;
		}
		virtual bool set(int i, const T& e) {
			bool ret = ((0 <= i) && (i < m_length));
			if (ret) {
				Node* current = position(i);;
				current->next->value = e;
			}
			return ret;
		}

		virtual T get(int i)const
		{
			T ret;
			if (get(i, ret)) {
				return ret;
			}
			else
			{
				THEOW_EXCEPTION(IndexOutOfBoundsException, "Invalid parameter i to get element ...");
			}
			return ret;
		}

		virtual bool get(int i, T& e)const {
			bool ret = ((0 <= i) && (i < m_length));
			if (ret) {
				const Node* current = position(i);;
				e = current->next->value;
			}
			return ret;
		}


		virtual int find(const T& e)const {
			int ret = -1;
			int i = 0;
			Node* node = m_header.next;
			while (node)
			{
				if (node->value == e) {
					ret = i;
					break;
				}
				i++;
				node = node->next;
			}
			return ret;
		}
		virtual int length() const {
			return this->m_length;
		}

		virtual void clear() {

			while (m_length >0)
			{
				remove(0);
			}
		}
		virtual bool move(int i, int step = 1) {
			bool ret = (0 <= i) && (i < m_length) && (step > 0);
			if (ret) {
				m_current = position(i)->next;
				m_step = step;
			}
			return ret;
		}

		virtual bool end() {
			return (m_current == NULL);
		}

		virtual T current() {
			if (m_current != NULL) {
				return m_current->value;
			}
			else
			{
				THEOW_EXCEPTION(InvalidOperationException, "no value at current position ...");
			}
		}

		virtual bool next() {
			int i = 0;
			while (i < m_step)
			{
				m_current = m_current->next;
				i++;
			}
			return (i == m_step);
		}

		virtual bool pre()
		{
			int i = 0;
			while( (i < m_step)&& !end())
			{
				m_current = m_current->pre;
				i++;
			}
			return (i == m_step);
		}

	private:

	};
}