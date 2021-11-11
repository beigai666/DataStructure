#pragma once
#include <stdexcept>
namespace FinlayLib {
	using namespace std;

	template <class T, int N>
	class Array {
		T array[N];
	public:
		Array();
		virtual ~Array();
		int leng();
		T& operator [](int index);
		T operator[](int index)const;
		bool set(int index, T var);
		bool get(int index, T& var);
	};

	template <class T, int N>
	Array<T, N>::Array() {


	}

	template <class T, int N>
	bool Array<T, N>::get(int index, T& var) {
		if (index > N) {
			return false;
		}
		var = array[index];
		return true;
	}

	template <class T, int N>
	bool Array<T, N>::set(int index, T var) {
		if (index > N) {
			return false;
		}
		array[index] = var;
		return true;
	}

	template <class T, int N>
	T& Array<T, N>::operator[](int index) {
		if ((0 <= index) && (index < N))
		{
			return array[index];
		}
		else
		{
			throw out_of_range("T& Array<T, N>::operator[] (int index)");
		}
	}

	template <typename T, int N>
	T Array<T, N>::operator[](int index)const {
		if ((0 <= index) && (index < N))
		{
			return array[index];
		}
		else
		{
			throw out_of_range("T Array<T, N>::operator[] (int index) const");
		}
	}

	template <class T, int N>
	Array<T, N>::~Array() {

	}
	template<class T, int N>
	inline int Array<T, N>::leng()
	{
		return N;
	}
}