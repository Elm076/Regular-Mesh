#pragma once
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <math.h>

/**
 * @author Adrián González Pérez agp00118@red.ujaen.es
 * @brief Data structure similar to STL vector
 * @class Dynamic_container
 */
template<class T>
class Dynamic_container
{	
	private:
		T* pointer_list = nullptr;
		unsigned int size = 0;
		unsigned int used_size = 0;
        unsigned int last_index = 0;
		void copy_elements(bool increment);
	
	public:
		Dynamic_container();
	
		explicit Dynamic_container(unsigned int _size);
	
		Dynamic_container(const Dynamic_container& origin);

		Dynamic_container(const Dynamic_container& origin, unsigned int initial_position, unsigned int elements_copied);

		Dynamic_container& operator=(const Dynamic_container& origin);

		void push(const T& data, unsigned int position = UINT_MAX);

		T& get(unsigned int position);

        T pop(unsigned int position = UINT_MAX);

        T& operator[](unsigned int i);

		void sort_container();

		void reverse_sort_container();

        int binary_search(T& data);

        T* binary_search_dir(T& data);

		unsigned int used_tam();

		~Dynamic_container();

};


/**
 * @brief static method of the data structure which returns the following power of 2 from the given param
 * @param num unsigned int number used to determine the next power of 2
 * @return the next power of 2 found
 */
 static unsigned int next_power2(unsigned int num){
     unsigned int result = 2;
     while (result <= num) {
         result = result * 2;
     }
     return result;
}

/**
 * @brief static method used to obtain the square root of the size of pointer_list
 * @param num size of pointer_list
 * @return square root of given param
 */
static unsigned int previous_power2(unsigned int num){
     return num/2;
 }


/**
* Default constructor. It creates a new object
* @brief	Default Constructor
* @return	New object with 1 position available
*/
template<class T>
Dynamic_container<T>::Dynamic_container() {
	size = 1;
	used_size = 0;
	pointer_list = new T[size];
}

/**
* Constructor that creates the object with a max size
* @brief	Constructor
* @param	log_size Length of the vector that contains pointer_list
* @return	New object with length log_size
*/
template<class T>
Dynamic_container<T>::Dynamic_container(unsigned int _used_size) {
	this->size = next_power2(_used_size);
	this->used_size = 0;
	pointer_list = new T[this->size];
}

/**
* Copy constructor that copies the origin object
* @brief Copy Constructor
* @param origin Object that will be copied
* @return New object copied from origin
*/
template<class T>
Dynamic_container<T>::Dynamic_container(const Dynamic_container& origin) {
    this->size = next_power2(origin.used_size);
    this->pointer_list = new T[this->size];
	this->used_size = origin.used_size;
	for (unsigned int i = 0; i < this->size; i++) {
		*(this->pointer_list + i) = *(origin.pointer_list + i);
	}
}
/**
* Copy Constructor that copies partially the origin object
* @brief	Partial Copy Constructor
* @param	origin Object that is gonna be copied
* @param	initial_position Position of origin where it will start copying
* @param	elements_copied Number of elements it will copy from origin
* @return	Object copied given the correct params
*/
template<class T>
Dynamic_container<T>::Dynamic_container(const Dynamic_container& origin, unsigned int initial_position, unsigned int elements_copied) {
    this->size = next_power2(elements_copied);
	this->pointer_list = new T[size];
	this->used_size = elements_copied;
	for (unsigned int i = 0; i < this->size; i++) {
		*(this->pointer_list + i) = *(origin.pointer_list + initial_position + i);
	}
}

/**
* Copy the origin object on destiny object
* @brief	operator =
* @param	origin Object origin that is gonna be copied
* @return	The copied object
*/
template<class T>
Dynamic_container<T>& Dynamic_container<T>::operator=(const Dynamic_container& origin) {
    if(this != &origin) {
        if (origin.pointer_list) {
            this->size = origin.size;
            this->used_size = origin.used_size;
            this->pointer_list = origin.pointer_list;
            for (unsigned int i = 0; i < this->size; i++) {
                *(this->pointer_list + i) = *(origin.pointer_list + i);
            }
            return *this;
        }
    }
    throw std::invalid_argument("---ERROR--- in Dynamic_container<T>::operator= ----- Left operand can't have same memory alloc than the left one.");
}

/**
 * @brief Method that gives the tam used (NOT TEH REAL ONE) in the container
 * @return The num of elements that contains the container
 */
template<class T>
unsigned int Dynamic_container<T>::used_tam() {
	return used_size;
}

/**
 * @brief Private method that creates a new pointer_list with the new correct size and copy the old elements to the new pointer_list
 * @param increment Bool value which will determine if the new pointer_list will grow or decrease
 */
template<class T>
void Dynamic_container<T>::copy_elements(bool increment) {
    unsigned int new_size;
    if (increment){
        new_size = next_power2(size);
    }
    else{
         new_size = previous_power2(size);
    }
    T* aux_pointer_list = new T[new_size];
	for (unsigned int i = 0; i < this->used_size; i++) {
		//aux_container.pointer_list[i] = this->pointer_list[i];
		aux_pointer_list[i] = this->pointer_list[i];
	}

	delete[] pointer_list;
    this->size = new_size;
	this->pointer_list = aux_pointer_list;
}

/**
 * @brief Method to push an object in the end of used positions of the container
 * @param data T& object
 * @param position index where we will insert the given data inside the data structure
 */
template<class T>
void Dynamic_container<T>::push(const T& data, unsigned int position) {
	if (used_size == size) {
        copy_elements(true);
	}
    if(position == UINT_MAX or position == used_size){
        *(pointer_list + last_index) = data;
    }
    else{
            for (unsigned i = used_size - 1; i >= position; i--) {
                pointer_list[i+1] = pointer_list[i];
            }
        pointer_list[position] = data;
    }
    used_size += 1;
    last_index += 1;


}

/**
 * @brief Method to get an existing object in the container given his position
 * @param position index of the object inside the structure
 * @return The object indexed by the given position
 */
template<class T>
T& Dynamic_container<T>::get(unsigned int position) {
	if (position >= this->size and position != UINT_MAX) {
		throw std::out_of_range("The given position exceed the max tam of the container");
	}
	else {
		return *(this->pointer_list + position);
	}
}

/**
 * @brief Method that remove the object indexed by given position
 * @param position index of the element that will be removed
 * @return A copy object of the data previously deleted
 */
template<class T>
T Dynamic_container<T>::pop(unsigned int position){
    T deleted_data = pointer_list[position];
    if (position >= size and position != UINT_MAX ){
        throw std::out_of_range("The given position exceed the max tam of the container");
    }
    else if (position != UINT_MAX){
        for (unsigned int i = position; i < used_size; i++){
            pointer_list[i] = pointer_list[i+1];
        }
    }
    used_size -= 1;
    last_index -= 1;
    if(used_size <= (int)(size/3)){
        copy_elements(false);
    }
    return deleted_data;
}

/**
 * @brief Operator to achieve a object contained in the structure
 * @param position index of the object inside the structure
 * @return The object indexed by the given position
 */
template<class T>
T& Dynamic_container<T>::operator[](unsigned int position) {
    if (position >= this->size and position != UINT_MAX ) {
        throw std::out_of_range("The given position exceed the max tam of the container");
    }
    else {
        return *(this->pointer_list + position);
    }
}

/**
 * @brief Method to order the container from the minor to the greatest object
 */
template<class T>
void Dynamic_container<T>::sort_container() {
	std::sort(this->pointer_list, this->pointer_list + this->used_size);
}

/**
 * @brief Method to order the container from the greatest to the minor object
 */
template<class T>
void Dynamic_container<T>::reverse_sort_container() {
	std::sort(this->pointer_list, this->pointer_list + this->used_size, [](T& a, const T& b) {
		return a > b;
		});
}

/**
 * @brief Method that search data in the data structure
 * @param data Object that will be searched in the data structure
 * @return position where the data was found
 */
template<class T>
int Dynamic_container<T>::binary_search(T& data) {
    sort_container();
    int left = 0;
    int right = used_size-1;

    while (left <= right) {
        int mid = (int) left+(right-left)/2;
        if (data == pointer_list[mid]) {
            return mid;
        }
        else if(data < pointer_list[mid]){
            right = mid-1;
        }
        else{
            left = mid+1;
        }
    }
    return -1;
}

/**
 * @brief Method that search data in the data structure
 * @param data Object that will be searched in the data structure
 * @return memory dir where the data was found
 */
template<class T>
T *Dynamic_container<T>::binary_search_dir(T &data) {
    int left = 0;
    int right = used_size-1;

    while (left <= right) {
        int mid = (int) left+(right-left)/2;
        if (data == pointer_list[mid]) {
            return (pointer_list + mid);
        }
        else if(data < pointer_list[mid]){
            right = mid-1;
        }
        else{
            left = mid+1;
        }
    }
    return nullptr;
}

/**
 * @brief Destructor of the class Dynamic_container. It delete pointer_list from dynamic memory management
 */
template<class T>
Dynamic_container<T>::~Dynamic_container() {
	delete[] pointer_list;
}
