#pragma once
#include "LinkList.h"

namespace FinlayLib {
	template <typename T>
	//ѭ������
	class CircleList : public LinkList<T>
	{
	protected:
		typedef typename LinkList<T>::Node Node;
		int mod(int i) const{
			return (this->m_length == 0) ? 0 : (i % this->m_length);
		}

		Node* last()const {
			return this->position(this->m_length - 1)->next;
		}

		void last_to_first()const
		{
			last()->next = this->m_header.next;
		}
	public:
		
		CircleList() {

		}
		~CircleList() {
			clear();
		}

		bool insert(const T& e) {
			return insert(this->m_length, e);
		}

		bool insert(int i, const T& e) {
			bool ret = true;
			i = i % (this->m_length + 1);
			ret = LinkList<T>::insert(i, e);
			if (ret && (i == 0)) {
				last_to_first();
			}
			return ret;
		}

		bool remove(int i) {
			bool ret = true;
			i = mod(i);
			if (i == 0) {
				Node* toDel = this->m_header.next;
				if (toDel != NULL)
				{
					this->m_header.next = toDel->next;
					this->m_length--;
					if (this->m_length > 0) {
						last_to_first();

						if (this->m_current == toDel) {
							this->m_current = toDel->next;
						}
					}
					else
					{
						this->m_header.next = NULL;
						this->m_current = NULL;
					}
				}
				this->destory(toDel);
			}
			else
			{
				ret = LinkList<T>::remove(i);
			}

			return ret;
		}

		bool set(int i, const T& e)
		{
			return LinkList<T>::set(mod(i), e);
		}

		T get(int i) const{
			return LinkList<T>::get(mod(i));

		}

		bool get(int i, const T& e)const {
			return LinkList<T>::get(mod(i), e);
		}

		int find(const T& e)const {
			int ret = -1;
			Node* slider = this->m_header.next;

			for (int i = 0; i < this->m_length; i++)
			{
				if (slider->value == e) {
					ret = i;
					break;
				}
				slider = slider->next;
			}
			return ret;
		}

		void clear()
		{
			while (this->m_length > 1) {
				remove(1);
			}
			if (this->m_length == 1)
			{
				Node* toDel = this->m_header.next;
				this->m_header.next = NULL;
				this->m_length = 0;
				this->m_current = NULL;
				this->destory(toDel);
			}
		}

		bool move(int i, int step = 1) {
			return LinkList<T>::move(mod(i), step);
		}

		bool end() {
			return (this->m_length == 0) || (this->m_current == NULL);
		}

	private:
	
	};



}