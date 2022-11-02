#pragma once
#include <Array/Array.h>
#include <Array/RangeArray.h>
namespace FinlayLib {
	template <typename T>
	class BTreeArray : public Array<T>
	{
	protected:
		RangeArray<T> m_value;
		RangeArray<int> m_mark;
		int m_toplimit;
		int height(int i)const
		{
			int ret = 0;
			if (!isNull(i)) {
				int lh = height(left(i));
				int rh = height(right(i));
				ret = ((lh > rh) ? lh : rh) + 1;
			}
			return ret;
		}
	public:
		BTreeArray(int height):m_value(1,(1<<height)-1), m_mark(m_value.lower(),m_value.upper()), m_toplimit(height)
		{
			for (int i = m_mark.lower(); i <= m_mark.upper(); i++)
			{
				m_mark[i] = 0;
			}
			this->m_array = NULL;
		}

		BTreeArray(BTreeArray<T>& obj):m_value(obj.m_value), m_mark(obj.m_mark), m_toplimit(obj.m_toplimit)
		{
			this->m_array = NULL;
		}

		BTreeArray<T>& operator= (BTreeArray<T> obj) {
			if (this != &obj)
			{
				m_value = obj.m_value;
				m_mark = obj.m_mark;
				m_toplimit = obj.m_toplimit;
				this->m_array = NULL;
			}
			return *this;
		}

		~BTreeArray()
		{
			clear();
		}

		bool set(int i, const T& e)
		{
			int tmp = 0;
			bool ret = m_mark.get(i,tmp) && (i == 1 || m_mark[i / 2]);
			if (ret)
			{
				m_value[i] = e;
				m_mark[i] = 1;
			}
			return ret;
		}

		bool get(int i, T& e)
		{
			int tmp = 0;
			bool ret = m_mark.get(i,tmp)&&tmp;
			if (ret)
			{
				e = m_value[i];
			}
			return ret;
		}

		T& operator[](int i) {
			if (m_mark[i])
			{
				return m_value[i];
			}
			else
			{
				THROW_EXCEPTION(InvalidOperationException, "Point i is invalid ...");
			}
		}

		T operator[](int i) const
		{
			return (const_cast<BTreeArray<T>&>(*this))[i];
		}

		void remove(int i) {
			if ((i >= m_mark.lower()) && (i <= m_mark.upper()))
			{
				m_mark[i] = 0;
				remove(this->left(i));
				remove(this->right(i));
			}
			return;
		}

		void resize(int nh)
		{
			if (nh != m_toplimit) {
				int len = (1 << nh) - 1;
				RangeArray<T> value(1, len);
				RangeArray<int> mark(1, len);
				for (int i = mark.lower(); i <= mark.upper(); i++)
				{
					mark[i] = 0;
				}
				len = (len < length()) ? len : length();
				for (int i = 1; i <= len; i++)
				{
					value[i] = m_value[i];
					mark[i] = m_mark[i];
				}
				this->m_value = value;
				this->m_mark = mark;
				this->m_toplimit = nh;
			}
			
		}

		void clear()
		{
			remove(1);
		}

		int toplimit()const
		{
			return this->m_toplimit;
		}

		int height() const
		{
			return height(1);
		}

		int count()const
		{
			int cn = 0;
			for (int i = m_mark.lower(); i <= m_mark.upper(); i++)
			{
				cn += m_mark[i];
			}
			return cn;
		}

		int length()const
		{
			return m_value.length();
		}

		int left(int i)const
		{
			return i * 2;
		}

		int right(int i)const
		{
			return i * 2 + 1;
		}

		int parent(int i)const
		{
			return i / 2;
		}

		int isNull(int i)const
		{
			return !((1<= i)&&(i<=length()) && m_mark[i]);
		}

		int find(const T& e)const
		{
			int ret = 0;
			for (int i = m_value.lower(); i <= m_value.upper(); i++)
			{
				if ((m_mark[i]>0)&&(m_value[i] == e))
				{
					ret = i;
					break;
				}
			}
			return ret;
		}

		bool ToHeap()
		{
			int size = count();
			
			for (int i = size / 2; i > 0; i--)
			{
				int index = i*2;
				T value = m_value[i];
				while (index<=size)
				{
					if ((index < size) && (m_value[index] < m_value[index + 1]))
					{
						index++;
					}
					if (value > m_value[index])
					{
						break;
					}
					else
					{
						m_value[index/2] = m_value[index];
						index = index*2;
					}
				}
				m_value[index/2] = value;
			}
			return true;
		}

		bool IsHeap(int i) {
			bool ret = true;
			if (!isNull(i))
			{
				int l = left(i);
				int r = right(i);
				if (!isNull(l) && !isNull(r)) {
					ret = (m_value[i] >= m_value[l]) 
						&& (m_value[i] >= m_value[r])
						&& IsHeap(r) 
						&& IsHeap(l);
				}
				else if(!isNull(l) && isNull(r))
				{
					ret = (m_value[i] >= m_value[l])
						&&IsHeap(l);
				}
				else if(isNull(l) && !isNull(r))
				{
					ret = false;
				}
				else if(isNull(l) && isNull(r))
				{
					ret = true;
				}
			}
			return ret;
		}
	private:

	};

	
}
