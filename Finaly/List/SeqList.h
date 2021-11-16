#pragma once
#include "List.h"
#include "SeqList.h"
#include <Exception/IndexOutOfBoundsException.h>
namespace FinlayLib {

	template <typename T>
	class SeqList :public List<T>
	{
	protected:
		T* m_array;
		int m_length;
	public:
		virtual bool insert(int i, const T& e) {
			//判断i的范围，需要满足0 <= i && i <= m_length
			bool ret = (0 <= i && i <= m_length);
			//插入元素时需要满足m_length < capaity()
			ret = ret & (m_length < capacity());
			if (ret) {
				for (int index = m_length-1; index >= i; index--)
				{
					m_array[index+1] = m_array[index];
				}
				m_array[i] = e;
				m_length++;
			}
			return ret;
		}

		virtual bool insert(const T& e) {
			return insert(this->m_length, e);
		}

		virtual bool remove(int i) {
			bool ret = (0 <= i && i < m_length);
			if (ret) {
				for (int index = i; index<m_length-1; index++)
				{
					m_array[index] = m_array[index + 1];
				}
				m_length--;
			}
			return ret;
		}
		virtual bool set(int i, const T& e) {
			bool ret = (0 <= i && i < m_length);
			if (ret) {
				m_array[i] = e;
			}
			return ret;
		}
		virtual bool get(int i, T& e)const {
			bool ret = (0 <= i && i < m_length);
			if (ret) {
				e = m_array[i];
			}
			return ret;
		}
		virtual int length() const {
			return m_length;
		}
		virtual void clear() {
			m_length = 0;
		}

		T& operator [](int i) {
			bool ret = (0 <= i && i < m_length);
			if (ret) {
				return m_array[i];
			}
			else
			{
				THEOW_EXCEPTION(IndexOutOfBoundsException, "Paranmeter i is invalid ...");
			}
		}

		T operator[] (int i)const{
			/*
			bool ret = (0 <= i && i < m_length);
			if (ret) {
				return m_array[i];
			}
			else
			{
				THEOW_EXCEPTION(IndexOutOfBoundsException, "Paranmeter i is invalid ...")
			}
			*/
			//复用T& operator [](int i)
			return (const_cast<SeqList<T>&>(*this))[i];
		}

		virtual int capacity()const = 0;

	private:

	};

}