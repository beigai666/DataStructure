#pragma once
#include "Queue.h"
#include <Exception/InvalidOperationException.h>
namespace FinlayLib {
	template <typename T,int N>
	class StaticQueue : public Queue<T>
	{

	protected:
		T m_space[N];		//队列存储空间,N为模板参数
		int m_front;		//队头顶标识
		int m_rear;			//队尾顶标识
		int m_length;		//当前队列的长度
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

