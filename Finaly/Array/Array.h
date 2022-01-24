#pragma once
#include <Object.h>
#include <Exception/IndexOutOfBoundsException.h>
namespace FinlayLib {
	using namespace std;

	template <class T>
	class Array : public Object{
	protected:
		T* m_array;
	public:
		Array();
		virtual ~Array();
		virtual int length()const =0;
		T& operator [](int index);
		T operator[](int index)const;
		virtual bool set(int index, T var);
		virtual bool get(int index, T& var);
		T* array()const
		{
			return m_array;
		}
	};

	template <class T>
	Array<T>::Array() {


	}

	template <class T>
	bool Array<T>::get(int i, T& var) {
		bool ret = ((0 <= i) && (i < length()));
		if (ret) {
			var = m_array[i];
		}
		
		return ret;
	}

	template <class T>
	bool Array<T>::set(int i, T var) {
		bool ret = ((0 <= i) && (i < length()));
		if (ret) {
			m_array[i] = var;
		}
		return ret;
	}

	template <class T>
	T& Array<T>::operator[](int i) {
		if ((0 <= i) && (i < length()))
		{
			return m_array[i];
		}
		else
		{
			THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid ...");
		}
	}

	template <typename T>
	T Array<T>::operator[](int i)const {
		if ((0 <= i) && (i < length()))
		{
			return m_array[i];
		}
		else
		{
			THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid ...");
		}
	}

	template <class T>
	Array<T>::~Array() {

	}
}