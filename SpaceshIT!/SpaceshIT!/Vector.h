#pragma once
#include <iostream>

typedef int size_type;
#define interval_rate 20

template <class T>
class Vector
{
private:
	T* internal_array;
	int capacity;
	size_type size;

	// Reserve space to allocate new array
	void reserve(size_type new_capacity);

public:

	// Member functions

	Vector();

	/*
	Description: Initialize a vector
	*/
	explicit Vector(size_type n, T& value = T());

	/*
	Description: Initialize a vector with another vector
	*/
	Vector(Vector& copier);

	/*
	Description: Destructor
	*/
	~Vector();

	/*
	Description: Assign another vector to the current vector object
	*/
	Vector<T>& operator=(const Vector<T>&);

	// Iterators
	T* begin();
	T* end();


	// Capacity
	size_type getsize();
	bool resize(size_type size);
	size_type getcapacity();
	bool empty();


	// Accessors
	T operator[] (size_type index);
	T at(size_type index);
	T front();
	T back();

	// Modifiers
	void push_back(T& item);

	/*
	Description: Remove last item, effectively reducing size of vector by 1
	*/
	void pop_back();

	/*
	Description: Single value insert
	*/
	void insert(T position, T& value);

	/*
	Description: Removes a single element from the vector
	*/
	T* erase(size_type position);

	// DEBUG AND EXTRAS
	void print();

};



///////////////////////////////
///     IMPLEMENTATIONS     ///
//////////////////////////////

////////////////////////////////////////////////////////////
/// \brief Assign a new array to local internal_array
///
/// This function creates a new array with specified size and
/// assign it to the local internal_array variable set by the
/// arguments given.
///
/// \param new_capacity     New capacity to allocate to new array (defines the capacity of the newly created and soon to be asigned internal_array)
////////////////////////////////////////////////////////////

template<class T>
inline void Vector<T>::reserve(size_type new_capacity)
{
	if (this->internal_array == 0)
	{
		this->capacity = 0;
		this->size = 0;
	}
	T* temp = new T[new_capacity];
	size_type temp_size = (new_capacity < this->size) ? new_capacity : this->size;

	for (size_type i = 0; i < temp_size; i++)
		temp[i] = this->internal_array[i];

	this->capacity = new_capacity;
	delete[] this->internal_array;
	this->internal_array = temp;
}

////////////////////////////////////////////////////////////
/// \brief Default constructor for Vector
///
/// This constructor takes no arguments and initializes
/// the Vector with a starting size of 0 and a capacity
/// specified by the defined interval_rate
///
////////////////////////////////////////////////////////////

template<class T>
inline Vector<T>::Vector()
{
	this->size = 0;
	this->capacity = interval_rate;
	this->internal_array = new T[this->capacity];
}

////////////////////////////////////////////////////////////
/// \brief Constructor for Vector
///
/// This constructor takes takes the number of times and the
/// value to be duplicated. The result of the Vector is a vector
/// of size specified the user with the value being duplicated
/// X number of times, where X is the size given.
/// 
/// \param n	The number of time 
///
////////////////////////////////////////////////////////////

template<class T>
inline Vector<T>::Vector(size_type n, T& value)
{
	this->size = n;
	this->capacity = (n % 20 < 20) ? 20 : n % 20;
	this->internal_array = new T[this->capacity];

	for (size_type i = 0; i < n; i++)
	{
		this->internal_array[i] = value;
	}
}

template<class T>
inline Vector<T>::Vector(Vector& copier)
{
	this->size = copier.size;
	this->capacity = copier.capacity;
	this->internal_array = new T[this->capacity];

	for (size_type i = 0; i < copier.size; i++)
	{
		this->internal_array[i] = copier[i];
	}
}

template<class T>
inline Vector<T>::~Vector()
{
	delete[] this->internal_array;
}

template<class T>
inline Vector<T>& Vector<T>::operator=(const Vector<T>& copier)
{
	delete[] this->internal_array;
	this->size = copier.size;
	this->capacity = copier.capacity;
	this->internal_array = new T[this->size];
	for (size_type i = 0; i < this->size; i++)
		this->internal_array[i] = copier.internal_array[i];
	return *this;
}

template<class T>
inline T* Vector<T>::begin()
{
	return this->internal_array;
}

template<class T>
inline T* Vector<T>::end()
{
	return this->internal_array + this->size;
}

template<class T>
inline size_type Vector<T>::getsize()
{
	return this->size;
}

template<class T>
inline bool Vector<T>::resize(size_type size)
{
	reserve(size);
	this->size = size;
	return true;
}

template<class T>
inline size_type Vector<T>::getcapacity()
{
	return this->capacity;
}

template<class T>
inline bool Vector<T>::empty()
{
	return !size;
}

template<class T>
inline T Vector<T>::operator[](size_type index)
{
	if (index > this->size)
		throw "Index out of bounds";
	return this->internal_array[index];
}

template<class T>
inline T Vector<T>::at(size_type index)
{
	return this->internal_array[index];
}

template<class T>
inline T Vector<T>::front()
{
	return this->internal_array[0];
}

template<class T>
inline T Vector<T>::back()
{
	return this->internal_array[this->size - 1];
}

template<class T>
inline void Vector<T>::push_back(T& item)
{
	if (this->size >= this->capacity)
		reserve(this->capacity + interval_rate);
	this->internal_array[this->size++] = item;
}

template<class T>
inline void Vector<T>::pop_back()
{
	// Calling T's class destructor
	(this->internal_array[this->size])->~T();
	this->size--;
}

template<class T>
inline void Vector<T>::insert(T position, T& value)
{
	T temp1;
	T temp2;
	if (this->size >= this->capacity)
		reserve(this->capacity + interval_rate);
	temp1 = this->internal_array[position];
	this->internal_array[position] = value;
	for (size_type i = position; i < this->size; i++)
	{
		temp2 = this->internal_array[i + 1];
		this->internal_array[i + 1] = temp1;
		temp1 = temp2;
	}
	this->size++;
}

template<class T>
inline T* Vector<T>::erase(size_type position)
{
	T ret_value = this->internal_array[position];
	for (size_type i = position; i < this->size; i++)
	{
		this->internal_array[i] = this->internal_array[i + 1];
	}
	this->size--;
	return &ret_value;
}

template<class T>
inline void Vector<T>::print()
{
	for (size_type i = 0; i < this->size; i++)
		std::cout << i << " " << this->internal_array[i] << std::endl;
	std::cout << "===" << std::endl;
}
