#pragma once
#include "Heap.h"
#include <Array/StaticArray.h>
namespace FinlayLib {

	template <typename T,int N>
	class StaticHeap : public Heap<T>
	{
		StaticArray<T, N> m_array;
	public:

		T& get(int i)
		{
			return m_array[i - 1];
		}

		StaticHeap(bool isMax=true):Heap<T>(isMax)
		{

		}
		~StaticHeap()
		{

		}
		virtual int capatity() const
		{
			return N;
		}
	private:

	};

}
