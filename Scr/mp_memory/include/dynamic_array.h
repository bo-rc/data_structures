/**
* @file dynamic_array.tcc
* @author Bo Liu (boliu1)
* @date Summer 2015
* cs225 mp1
*/

#ifndef CS225_DYNAMIC_ARRAY_H_
#define CS225_DYNAMIC_ARRAY_H_
#include <cstdint>

namespace cs225
{
	template <typename T>
	class dynamic_array
	{
	public:
		/**
		 * Default constructed dynamic_arrays 
		 * should have a null array and a size of 0. 
		 */
		dynamic_array();

                /** 
		 * Constructs a new dynamic_array with 
		 * sze number of elements.
		 *	Parameters: 
		 *		sze	
		 *		The number of elements to be present 
		 *		in the new array
		 */
		dynamic_array(uint64_t sze);
		
		/**
		 * Copying dynamic_arrays is allowed.
		 * This shall perform a deep copy
		 */
		dynamic_array(const dynamic_array &other);

		/**
		 * Move construction for dynamic_arrays is allowed.
		 */
		dynamic_array(dynamic_array &&other);

		/**
		 * Unifying assignment operator.
		 * This allows dynamic_arrays to be copy assigned 
		 * or move assigned.
		 */
		dynamic_array & operator= (dynamic_array rhs);

		/**
		 * The destructor for dynamic_array frees 
		 * all resources associated with the array instance. 
		 */
		~dynamic_array();

		/**
		 * Clears all resources associated with the array instance 
		 * and sets it to have a 0 size.
		 * (This should make it equivalent to 
		 * a default constructed dynamic_array.)
		 */
		void clear();

		/**
		 * Swaps the current dynamic_array with an existing one.
		 */
		void swap(dynamic_array &other);

		/**
		 * Changes the size of the current dynamic_array to the desired amount.
		 * This should change the size of the internal array, 
		 * deleting elements that are beyond the desired size 
		 * if shrinking or adding new ones if increasing in size.
		 */
		void resize(uint64_t size);

		/**
		 * Non-checking subscript operator.
		 */
		const T & operator[] (uint64_t idx) const;

		/**
		 * Non-checking subscript operator.
		 */
		T & operator[] (uint64_t idx);

		/**
		 * Bounds-checking accessor function.
		 * This function should throw a std::out_of_range exception 
		 * if the desired index is invalid 
		 * (larger than the size of the array).
		 */
		const T & at(uint64_t idx) const;

		/**
		 * Bounds-checking accessor function.
		 * This function should throw a std::out_of_range exception 
		 * if the desired index is invalid 
		 * (larger than the size of the array).
		 */
		T & at(uint64_t idx);

		/**
		 * returns the size of the current array
		 */
		uint64_t size() const;

		/**
		 * returns whether the array is empty
		 */
		bool empty() const;

	private:
		/**
		 * The pointer to the array owned (nullptr if empty) 
		 */
		T* arr_;

		/**
		 * The number of elements in the owned array. 
		 */
		uint64_t size_;
	};
} // namespace cs225
#include "dynamic_array.tcc"
#endif
