#pragma once
template<typename T>
class HeapArray {
	int m_length;
	T* m_pointer;
private:
	HeapArray(int leng);
	HeapArray(const HeapArray<T>& obj);
	int length() const;
	bool construct();
public:
	static HeapArray<T>* NewInstance(int leng);
	T& operator[](int index);
	T operator[](int index)const;
	bool set(int index, T var);
	bool get(int index, T& var);
	virtual ~HeapArray();
};

template<typename T>
HeapArray<T>::HeapArray(int leng) {
	m_length = leng;
	
}

template
< typename T >
int HeapArray<T>::length() const
{
	return m_length;
}

template<typename T>
HeapArray<T>::HeapArray(const HeapArray<T>& obj) {
	m_length = obj.m_length;
	m_pointer = new T[m_length];
	for (int i = 0; i < m_length; i++) {
		T[i] = obj.m_pointer[i];
	}
}

template<typename T>
bool HeapArray<T>::construct() {
	m_pointer = new T[m_length];
	return m_pointer != NULL;
}

template <typename T>
HeapArray<T>::~HeapArray() {
	delete[] m_pointer;
}

template <typename T>
HeapArray<T>* HeapArray<T>::NewInstance(int leng) {
	HeapArray<T>* obj = new HeapArray<T>(leng);
	if (!(obj && obj->construct())) {
		delete obj;
		obj = NULL;
	}
	return obj;
}

template <typename T>
T& HeapArray<T>::operator[](int index) {
	if ((0 <= index) && (index < length()))
	{
		return m_pointer[index];
	}
	else
	{
		throw out_of_range("T& HeapArray<T>::operator [] (int index)");
	}
}

template <typename T>
T HeapArray<T>::operator[](int index)const {
	if ((0 <= index) && (index < length()))
	{
		return m_pointer[index];
	}
	else
	{
		throw out_of_range("T HeapArray<T>::operator [] (int index) const");
	}
}

template <typename T>
bool HeapArray<T>::get(int index,T& var) {
	if (index < m_length) {
		var = m_pointer[index];
		return true;
	}
	return false;
}

template <typename T>
bool HeapArray<T>::set(int index, T var) {
	if (index < m_length) {
		m_pointer[index] = var;
		return true;
	}
	return false;
}