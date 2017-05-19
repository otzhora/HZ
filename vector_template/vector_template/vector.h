#pragma once

using namespace std;

template<typename T>
class vector_t
{
public:
	vector_t();

	vector_t(size_t size);

	vector_t(T* data, size_t size);

	~vector_t();

	void print();

	void push_back(T item);

	T& operator[](int i);

	void sort();

	void qsort(size_t l, size_t r);
private:
	T* data;
	size_t size;
	size_t top;
};

template<typename T>
vector_t<T>::vector_t()
{
	data = nullptr;
	size = 0;
	top = 0;
}

template<typename T>
vector_t<T>::vector_t(size_t size)
{
	this->size = size;
	data = new T[size];
	top = size;
}

template<typename T>
vector_t<T>::vector_t(T* data, size_t size)
{
	this->size = size;
	this->data = new T[size];
	this->top = size;
	for (size_t i = 0; i < size; i++)
		this->data[i] = data[i];
}

template<typename T>
vector_t<T>::~vector_t()
{
	delete data;
}

template<typename T>
void vector_t<T>::print()
{
	for (size_t i = 0; i < top; i++)
		cout << data[i] << " ";
	cout << endl;
}

template<typename T>
void vector_t<T>::push_back(T item)
{
	if (top < size)
	{
		data[top++] = item;
	}
	else
	{
		if (size == 0)
			size = 1;
		size *= 2;
		T* buf = new T[size];
		for (size_t i = 0; i < top; i++)
			buf[i] = data[i];
		buf[top++] = item;
		delete data;
		data = buf;
	}
}

template<typename T>
T& vector_t<T>::operator[](int i)
{
	return data[i];
}

template<typename T>
void vector_t<T>::sort()
{
	qsort(0, top-1);
}

template<typename T>
void vector_t<T>::qsort(size_t l, size_t r)
{
	T mid = data[l + (r - l) / 2];
	size_t i = l;
	size_t j = r;
	while (i <= j)
	{
		while (data[i] < mid) i++;
		while (data[j] > mid) j--;
		if (i <= j)
		{
			swap(data[i], data[j]);
			i++;
			if(j != 0)
				j--;
		}
	}
	if (l < j)
		qsort(l, j);
	if (i < r)
		qsort(i, r);
}

