#pragma once
#include "Queue.h"
#include <Exception/InvalidOperationException.h>
namespace FinlayLib {
	template <typename T,int N>
	class StaticQueue : public Queue<T>
	{

	protected:
		T m_space[N];		//���д洢�ռ�,NΪģ�����
		int m_front;		//��ͷ����ʶ
		int m_rear;			//��β����ʶ
		int m_length;		//��ǰ���еĳ���
	public:
		StaticQueue() {
			this->m_front = 0;
			this->m_length = 0;
			this->m_rear = 0;
		}
		~StaticQueue() {

		}
		int capacity()const {
			return N;
		}
		virtual void add(const T& e) {
			if (this->m_length < N) {
				m_space[m_rear] = e;
				m_rear = (m_rear + 1) % N;
				m_length++;
			}
			else {
				THEOW_EXCEPTION(InvalidOperationException, "No space in current queue ...");
			}
		}
		virtual void remove() {
			if (m_length > 0) {
				m_front = (m_front + 1) % N;
				m_length--;
			}
			else {
				THEOW_EXCEPTION(InvalidOperationException, "No element in current queue ...");
			}
		}
		virtual T front()const {
			if (m_length > 0) {
				return m_space[m_front];
			}
			else {
				THEOW_EXCEPTION(InvalidOperationException, "No element in current queue ...");
			}
		}
		virtual void clear() {
			this->m_front = 0;
			this->m_length = 0;
			this->m_rear = 0;
		}
		virtual int length()const {
			return this->m_length;
		}
	private:

	};
}

