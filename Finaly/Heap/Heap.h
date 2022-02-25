#pragma once
#include <Queue/Queue.h>
namespace FinlayLib {
	template <typename T>
	class Heap : public Queue<T>
	{
	protected:
		bool m_isMax;
		int m_length;

		virtual bool compare(const T& lv, const T& rv)
		{
			return m_isMax ? (lv > rv) : (lv < rv);
		}
		virtual T& get(int i) = 0;
		virtual T& get(int i)const
		{
			return const_cast<Heap<T>*>(this)->get(i);
		}

		int left(int i)const
		{
			return 2 * i;
		}
		int right(int i)const
		{
			return 2 * i + 1;
		}

		int parent(int i)const
		{
			return i / 2;
		}

	public:
		Heap(bool isMax)
		{
			m_isMax = isMax;
			m_length = 0;
		}

		void add(const T& e)
		{
			int i = length() + 1;
			if (i <= capatity()) {
				while ( (i>1) && compare(e, get(parent(i))) )
				{
						get(i) = get(parent(i));
						i = parent(i);
				}
				get(i) = e;
				this->m_length++;
			}
		}

		T front()const
		{
			if (length() > 0)
			{
				return get(1);
			}
			else
			{
				THROW_EXCEPTION(InvalidOperationException, "Heap is empty ...");
			}
			
		}

		bool front(T& e)const
		{
			bool ret = (length() > 0);
			if (ret)
			{
				e = front();
			}
			return ret;
		}

		void remove()
		{
			T& e = get(length());
			int i = 1;
			int ci = left(i);
			while (ci<length())
			{
				if ((ci + 1) < length() && compare(get(ci + 1), get(ci)))
				{
					ci++;
				}
				if (compare(e,get(ci)))
				{
					break;
				}
				else
				{
					get(i) = get(ci);
					i = ci;
					ci = left(ci);
				}
			}
			get(i) = e;
			this->m_length--;
		}

		int length()const
		{
			return this->m_length;
		}

		void clear()
		{
			m_length = 0;
		}

		virtual int capatity() const = 0;
	};

}
