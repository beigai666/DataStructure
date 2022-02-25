#pragma once
#include "Heap.h"
#include <Array/DynamicArray.h>
namespace FinlayLib {
	template <typename T>
	class DynamicHeap : public Heap<T>
	{
		DynamicArray<T> m_array;
		int m_capacity;
		T& get(int i)
		{
			return m_array[i - 1];
		}
	public:
		DynamicHeap(int capacity, bool isMax = true) :Heap<T>(isMax), m_array(capacity)
		{
			m_capacity = capacity;
		}
		~DynamicHeap()
		{

		}
		virtual int capatity() const
		{
			return m_capacity;
		}
		void resize(int length) {
			m_array.resize(length);
		}
	private:

	};

}
