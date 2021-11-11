#pragma once
#include "SeqList.h"
namespace FinlayLib {
	template<typename T,int N>
	class StaticList : public SeqList<T>
	{
		T m_space[N];
	public:
		StaticList() {
			this->m_array = m_space;
			this->m_length = 0;
		}
		~StaticList() {

		}
		int capaity()const {
			return N;
		}
	private:

	};

}