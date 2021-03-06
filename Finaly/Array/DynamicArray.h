#pragma once
#include <Array/Array.h>
#include <Exception/NoEnoughMemoryException.h>


namespace FinlayLib {
	template<typename T>
	class DynamicArray : public Array<T>
	{
		int m_length;
	protected:
		T* copy(T* array, int len, int newLen) {
			T* ret = new T[newLen];
			if (ret) {
				int size = (len < newLen) ? len : newLen;
				for (int i = 0; i < size; i++)
				{
					ret[i] = array[i];
				}
			}
			return ret;
		}

		void updata(T* array, int length) {
			if (array) {
				T* temp = this->m_array;
				this->m_array = array;
				this->m_length = length;
				delete temp;
			}
			else
			{
				THROW_EXCEPTION(NoEnoughMemoryException, "No memory to update DynamicaArray object ...");
			}
		}

		void init(T* array, int length) {
			if (array) {
				this->m_array = array;
				this->m_length = length;
			}
			else
			{
				THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create DynamicaArray object ...");
			}
		}
	public:
		DynamicArray(int length=0) {
			if (length == 0) {
				this->m_length = 0;
				this->m_array = NULL;
			}
			else
			{
				init(new T[length], length);
			}
			
		}

		DynamicArray(const DynamicArray<T>& obj) {
			init(copy(obj.m_array, obj.m_length, obj.m_length), obj.m_length);
		}

		DynamicArray<T>& operator = (const DynamicArray<T>& obj) {
			if (this != &obj) {
				updata(copy(obj.m_array, obj.m_length, obj.m_length), obj.m_length);
			}
			return *this;
		}
		int length()const {
			return m_length;
		}

		void resize(int length) {
			if (length != m_length) {
				updata(copy(this->m_array,this->m_length,length),length);
			}
		}

		~DynamicArray() {
			delete[] this->m_array;
		}

	private:

	};
}