/**
* @file collage.h
* @author Bo Liu (boliu1)
* @date Summer 2015
* cs225 mp1
*/

/* Class description:
 *
 * https://chara.cs.illinois.edu/sites/cs225/mps/2015/06/22/mp_memory.html
 *
 * A collage represents a collection of images layered on top of one another. 
 * Each index into the collection represents a “layer” of the collage, 
 * which may be either occupied or empty. The image at each “layer” 
 * also has coordinates which indicate where the upper left-hand corner of 
 * the image should begin in the final output. 
 * The collage class has functions for adding, removing, and accessing images, 
 * setting their coordinates, and adjusting the number of layers, among others. 
*/

#ifndef CS225_COLLAGE_H_
#define CS225_COLLAGE_H_
#include <cstdint>
#include <string>
#include <tuple>
#include "epng.h"
#include "scoped_ptr.h"
#include "dynamic_array.h"

namespace cs225
{
    class collage {
	public:
  	/** 
	 * Initializes this collage object to be able 
	 * to hold size number of images, accessible through 
	 * indices 0 through size - 1. 
	 * Each index is a "layer" of the collage—
	 * the lower numbered layers are "below" the higher numbered layers. 
	 * You should store these using an array structure containing pointers 
	 * to the images, which should start off with each pointing to nullptr. 
	 * Think about how you can leverage parts 1 and 2 for this... 
	 * Parameters 
	 * 	size	The size of the collage
	 */
	collage (uint64_t size);

	/**
	 * Collages can be copy constructed, 
	 * which should make an independent copy (as in, a deep copy) 
	 × of the given collage. 
	 */
	collage (const collage &other);
	
	/**
	 * Collages may be move constructed as well.
	 */
	collage (collage &&other);

	/** 
	 * Collages may be assigned to one another. 
	 * Remember to use the copy-and-swap idiom for exception safety!
	 */
	collage & operator= (collage rhs);

	/**
	 * Ensures that all of the resources associated with this collage are freed.
	 * If you implement collage() in the C++14 way, 
	 * you should be able to = default its implementation! How nice.
	 */
	~collage () = default;

	/**
	 * Swaps this collage with another.
	 */ 
	void swap (collage &other);

	/**
	 * Changes the number of layers in this collage. 
	 * If the resulting collage is smaller, 
	 * the extra images should be released. 
	 * Parameters 
	 * 	max	The new number of layers
	 */
	void layers (uint64_t max);

	/**
	 * 
	 */
	uint64_t layers () const;

	/**
	 * 
	 */
	uint64_t filled () const;

	/**
	 * Adds a new picture to the collage at the given index, 
	 * replacing any existing image at that location. 
	 * If the index is out of the range of allowed layers in the collage, 
	 * a std::out_of_range exception should be thrown. 
	 * Parameters 
	 * 	filename    The file to load the image from 
	 * 	index    The index (layer) to place the image
	 * 	x	The desired x coordinate for the image in the collage
	 * 	y	The desired y coordinate for the image in the collage
	 */
	void emplace_picture 
	(const std::string &filename, uint64_t index, uint64_t x, uint64_t y);
	
	/* 
	 * Moves an image between layers. 
	 * If the destination is occupied, the image at that location 
	 * should be freed. The source index should be empty after this operation. 
	 * If either index is outside the range of allowed layers in the collage, 
	 * a std::out_of_range exception should be thrown. 
	 * Parameters 
	 * 	src	The source index
	 * 	dest	The destination index
	 */
	void change_layer (uint64_t src, uint64_t dest);

	/* 
	 * Sets the position of the image at the given index. 
	 * If the index is outside the range of allowed layers in the collage, 
	 * a std::out_of_range exception should be thrown. 
	 * If there is no image at that location, 
	 * a std::invalid_argument exception should be thrown.
	 * Parameters
	 * 	index	The index of the image to be moved
	 * 	x	The new x coordinate for that image
	 *	y	The new y coordinate for that timage
	 */
	void position (uint64_t index, uint64_t x, uint64_t y);

	/* Removes the image at the given index.
	 * If the index is outside the range of allowed layers in the collage, 
	 * a std::out_of_range exception should be thrown.
	 * Parameters
	 * 	index	The index of the image to be removed.
	 */
	void erase (uint64_t index);

	/**
	 * Accessor function for the underlying images. 
	 * If the index is outside the valid range, 
	 * a std::out_of_range exception should be thrown. 
	 * Parameters:
	 * 	index	The index in the image to access 
	 * Returns a const pointer to the image at that index
	 */
	const epng::png * at (uint64_t index) const;

	/**
	 * Accessor function for the underlying images. 
	 * If the index is outside the valid range, 
	 * a std::out_of_range exception should be thrown. 
	 * Parameters 
	 * 	index	The index in the image to access
	 * Returns a pointer to the image at that index
	 */
	epng::png * at (uint64_t index);

	/**
	 * Draws the collage onto a new image, respecting the layer structure 
	 * and the image coordinates, and returns that new image. 
	 */
	epng::png draw () const;

    private:
	uint64_t size_;
	typedef int PosX;
	typedef int PosY;
	typedef scoped_ptr<epng::png> Img_ptr;
	typedef std::tuple<PosX, PosY, Img_ptr> Layer;
	dynamic_array<Layer> layers_;

    };
} // namespace cs225
#endif
