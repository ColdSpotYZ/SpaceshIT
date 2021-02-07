/* 
Team member: Jason Chua
Group: CookieZ
studentID: S10195450H
*/

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

	// Sorting function
	void swap(int* a, int* b);
	int partition(int left, int right);
	void quicksort(int left, int right);

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

	// Sort wrapper
	void sort();

	// Accessors
	T operator[] (size_type index);
	T at(size_type index);
	T front();
	T back();

	// Modifiers
	void push_back(T& item);
	void trim(size_type start, size_type end);

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

	template<typename T>
	struct is_pointer { static const bool value = false; };

	template<typename T>
	struct is_pointer<T*> { static const bool value = true; };


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
/// \param new_capacity	New capacity to allocate to new array (defines the capacity of the newly created and soon to be asigned internal_array)
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
/// \brief Internal function to swap 2 different values in the internal array
///
/// This function swaps the location of 2 specified values
/// in the internal array.
///
/// \param a    first value to be swapped
/// \param b	second value to be swapped
////////////////////////////////////////////////////////////

template<class T>
inline void Vector<T>::swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

////////////////////////////////////////////////////////////
/// \brief Partitioning for quicksort
///
/// This function creates a partition and select a pivot value.
/// All other values will then be compared to the pivot value
/// and will be moved to the left of the pivot if it is of a 
/// lower value and moved to the right if it is of a higher value.
///
/// \param left	start value to partition
/// \param right	end value to partition
////////////////////////////////////////////////////////////

template<class T>
inline int Vector<T>::partition(int left, int right)
{
	int mid = (left + right) / 2;
	int pivot = this->internal_array[mid];
	int i = left;
	int j = right;

	while (i < j)
	{
		while (this->internal_array[i] < pivot)
			i++;
		while (this->internal_array[j] > pivot)
			j--;
		
		while (this->internal_array[i] == pivot && this->internal_array[j] == pivot)
		{
			if (i == mid)
				j--;
			else if (j == mid)
				i++;
			else
				j--;
		}
		
		if (i < j)
		{
			swap(&this->internal_array[i], &this->internal_array[j]);
		}
	}
	return i;
}

////////////////////////////////////////////////////////////
/// \brief Recursion for quicksort
///
/// This function checks if two local pointers intersects
/// and calls itself recursively to sort values.
///
/// \param left	start value to partition
/// \param right	end value to partition
////////////////////////////////////////////////////////////

template<class T>
inline void Vector<T>::quicksort(int left, int right)
{
	if (left < right)
	{
		int pivotIdx = partition(left, right);
		quicksort(left, pivotIdx - 1);
		quicksort(pivotIdx + 1, right);
	}
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
/// \param n	The number of times the value will be added
/// \param value	The value to be added
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

////////////////////////////////////////////////////////////
/// \brief Constructor for Vector
///
/// This constructor takes takes a vector object and copies it's
/// value into the new vector
/// 
/// \param copier	The vector to be copied from
///
////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////
/// \brief Destructor for Vector
///
/// TThe destructor destroys and unallocate the internal array
///
////////////////////////////////////////////////////////////

template<class T>
inline Vector<T>::~Vector()
{
	delete[] this->internal_array;
}

////////////////////////////////////////////////////////////
/// \brief Vector assignment
///
/// This operator copies a vector into the current vector
/// 
/// \param copier	The vector to be copied from
///
////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////
/// \brief Retrieve a pointer to the first item
///
/// This function returns a pointer to the first item in the vector
/// 
////////////////////////////////////////////////////////////

template<class T>
inline T* Vector<T>::begin()
{
	return this->internal_array;
}

////////////////////////////////////////////////////////////
/// \brief Retrieve a pointer to the last item
///
/// This function returns a pointer to the last item in the vector
/// 
////////////////////////////////////////////////////////////

template<class T>
inline T* Vector<T>::end()
{
	return this->internal_array + this->size;
}

////////////////////////////////////////////////////////////
/// \brief Retrieve the size of the vector
///
/// This function returns the size of the vector
/// 
////////////////////////////////////////////////////////////

template<class T>
inline size_type Vector<T>::getsize()
{
	return this->size;
}

////////////////////////////////////////////////////////////
/// \brief Resize the vector
///
/// This function resize the vector to a size greater than the current
/// 
/// \param size	size to resize
////////////////////////////////////////////////////////////

template<class T>
inline bool Vector<T>::resize(size_type size)
{
	reserve(size);
	this->size = size;
	return true;
}

////////////////////////////////////////////////////////////
/// \brief Retrieve the capacity of the vector
///
/// This function returns the capacity of the vector
/// 
////////////////////////////////////////////////////////////

template<class T>
inline size_type Vector<T>::getcapacity()
{
	return this->capacity;
}

////////////////////////////////////////////////////////////
/// \brief Check if vector is empty
///
/// This function returns the size of the vector
/// 
////////////////////////////////////////////////////////////

template<class T>
inline bool Vector<T>::empty()
{
	return !size;
}

////////////////////////////////////////////////////////////
/// \brief Sorts the array
///
/// This function sorts the array with quicksort algorithm 
/// from smaller value to greater. ie. ascending order
/// 
////////////////////////////////////////////////////////////

template<class T>
inline void Vector<T>::sort()
{
	if (typeid(this->internal_array[0]) == typeid(int))
	{
		quicksort(0, this->size - 1);
	}
}

////////////////////////////////////////////////////////////
/// \brief Access an item
///
/// This operator returns an item from the vector
/// 
/// \param index	index of the item to be returned
/// 
////////////////////////////////////////////////////////////


template<class T>
inline T Vector<T>::operator[](size_type index)
{
	if (index > this->size)
		throw "Index out of bounds";
	return this->internal_array[index];
}

////////////////////////////////////////////////////////////
/// \brief Retrieve an item in the vector
///
/// This function returns an item in the vector
/// 
/// \param index	index of the item to be returned
///
////////////////////////////////////////////////////////////

template<class T>
inline T Vector<T>::at(size_type index)
{
	return this->internal_array[index];
}

////////////////////////////////////////////////////////////
/// \brief Retrieve the first item
///
/// This function return the item at the front of the vector
///
////////////////////////////////////////////////////////////

template<class T>
inline T Vector<T>::front()
{
	return this->internal_array[0];
}

////////////////////////////////////////////////////////////
/// \brief Retrieve the last item
///
/// This function return the last item of the vector
///
////////////////////////////////////////////////////////////

template<class T>
inline T Vector<T>::back()
{
	return this->internal_array[this->size - 1];
}

////////////////////////////////////////////////////////////
/// \brief Adds an item to the back
///
/// This function adds an item to the back of the vector
/// 
/// \param item	The item to be added
///
////////////////////////////////////////////////////////////

template<class T>
inline void Vector<T>::push_back(T& item)
{
	if (this->size >= this->capacity)
		reserve(this->capacity + interval_rate);
	this->internal_array[this->size++] = item;
}

////////////////////////////////////////////////////////////
/// \brief Slice the vector
///
/// This function slices the vector into a smaller or same sized vector
/// 
/// \param start	Start index to slice
/// \param end	End index to slice
///
////////////////////////////////////////////////////////////

template<class T>
inline void Vector<T>::trim(size_type start, size_type end)
{
	if (start < 0)
		start = 0;
	if (end > this->size)
		end = this->size;
	T* temp = new T[end - start];
	for (unsigned i = start; i < end; i++)
	{
		temp[i - start] = this->internal_array[i];
	}
	this->internal_array = temp;
	this->size = end - start;
}

////////////////////////////////////////////////////////////
/// \brief Remove item from back
///
/// This function removes an item from the back of the array
/// decreasing the vector's size by 1
///
////////////////////////////////////////////////////////////

template<class T>
inline void Vector<T>::pop_back()
{
	this->internal_array[this->size] = NULL;
	// Calling T's class destructor
	if (is_pointer<T>::value == true)
		(this->internal_array[this->size])->~T();
	else
		(this->internal_array[this->size]).~T();
	this->size--;
}

////////////////////////////////////////////////////////////
/// \brief Insert item
///
/// This function inserts an item to a specified index,
/// pushing other values back
/// 
/// \param position	index to insert
/// \param value	item to insert
///
////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////
/// \brief Removes an item
///
/// This function removes an item at a specified index,
/// moving other items forward
/// 
/// \param position	index to be removed
///
////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////
/// \brief DEBUG PRINT
///
/// This functions prints all values and index in the vector
///
////////////////////////////////////////////////////////////

template<class T>
inline void Vector<T>::print()
{
	for (size_type i = 0; i < this->size; i++)
		std::cout << i << " " << this->internal_array[i] << std::endl;
	std::cout << "===" << std::endl;
}
