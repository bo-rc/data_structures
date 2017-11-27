/**
* @file collage.cpp
* @author Bo Liu (boliu1)
* @date Summer 2015
* cs225 mp1
*/

#include "collage.h"
#include <algorithm>

namespace cs225
{

collage::collage (uint64_t size) : size_{size}, layers_{size}
{
    /* empty */
}

/**
* Collages can be copy constructed, 
* which should make an independent copy (as in, a deep copy) 
* of the given collage. 
*/
collage::collage (const collage &other) : size_{other.size_}, layers_{other.size_}
{
    for (uint64_t i = 0; i < size_; ++i)
    {
	if(!((std::get<2>(other.layers_[i])).empty()))
	{
		auto temp = scoped_ptr<epng::png> {new epng::png{*((std::get<2>(other.layers_[i])).get())}};

		std::get<2>(layers_[i]).swap(temp);
		std::get<2>(layers_[i]).swap(temp);
		std::get<2>(layers_[i]).swap(temp);
		std::get<0>(layers_[i]) = std::get<0>(other.layers_[i]); 
		std::get<1>(layers_[i]) = std::get<1>(other.layers_[i]);
	}
    }
};
	
/**
* Collages may be move constructed as well.
*/
collage::collage (collage &&other) : size_{std::move(other.size_)}, layers_{std::move(other.layers_)}
{
    /* empty */
}

/** 
* Collages may be assigned to one another. 
* Remember to use the copy-and-swap idiom for exception safety!
*/
collage & collage::operator= (collage rhs)
{
    swap(rhs);
    return *this;
}
/**
* Ensures that all of the resources associated with this collage are freed.
* If you implement collage() in the C++14 way, 
* you should be able to = default its implementation! How nice.
*/
//collage::~collage ()
//{
//    /* empty */
//}
/**
* Swaps this collage with another.
*/ 
void collage::swap (collage &other)
{
    std::swap(this->size_, other.size_);
    std::swap(this->layers_, other.layers_);
}

/**
* Changes the number of layers in this collage. 
* If the resulting collage is smaller, 
* the extra images should be released. 
* Parameters 
* 	max	The new number of layers
*/
void collage::layers (uint64_t max)
{
    size_ = max;
    layers_.resize(max);
}

/**
* 
*/
uint64_t collage::layers () const
{
    return size_;
}

/**
* 
*/
uint64_t collage::filled () const
{
    int counter = 0;
    for(uint64_t i = 0; i < layers_.size(); ++i)
    {
	if(!((std::get<2>(layers_[i])).empty()))
	    ++counter;
    }

    return counter;
}
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
void collage::emplace_picture 
(const std::string &filename, uint64_t index, uint64_t x, uint64_t y)
{
    if(index > size_)
	throw std::out_of_range("index out of bounds");
    else if (((std::get<2>(layers_[index])).empty()))
    {
	std::get<2>(layers_[index]) = scoped_ptr<epng::png>{new epng::png{filename}};
	std::get<0>(layers_[index]) = x;
	std::get<1>(layers_[index]) = y;
    } else {
	erase(index);
	std::get<2>(layers_[index]) = scoped_ptr<epng::png>{new epng::png{filename}};
	std::get<0>(layers_[index]) = x;
	std::get<1>(layers_[index]) = y;
    }
}
	
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
void collage::change_layer (uint64_t src, uint64_t dest)
{
    if(src > size_)
	throw std::out_of_range("source index out of bounds");
    else if(dest > size_)
	throw std::out_of_range("destination index out of bounds");
    else
    { 
	layers_[dest] = std::move(layers_[src]);
    }
}

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
void collage::position (uint64_t index, uint64_t x, uint64_t y)
{
    if(index >= size_)
    {
	throw std::out_of_range("index out of bounds");
    } 
    if ((std::get<2>(layers_[index])).empty()) 
    {
	throw std::invalid_argument("invalid argument");
    }
    std::get<0>(layers_[index]) = x;
    std::get<1>(layers_[index]) = y;
}

/* Removes the image at the given index.
* If the index is outside the range of allowed layers in the collage, 
* a std::out_of_range exception should be thrown.
* Parameters
* 	index	The index of the image to be removed.
*/
void collage::erase (uint64_t index)
{
    if(index > size_)
	throw std::out_of_range("index out of bounds");
    else
    {
	std::get<2>(layers_[index]).clear();
	std::get<0>(layers_[index]) = 0;
	std::get<1>(layers_[index]) = 0;
    }

}

/**
* Accessor function for the underlying images. 
* If the index is outside the valid range, 
* a std::out_of_range exception should be thrown. 
* Parameters:
* 	index	The index in the image to access 
* Returns a const pointer to the image at that index
*/
const epng::png * collage::at (uint64_t index) const
{
    if(index > size_)
	throw std::out_of_range("index out of bounds");
    else
    {
	return std::get<2>(layers_[index]).get();
    }

}

/**
* Accessor function for the underlying images. 
* If the index is outside the valid range, 
* a std::out_of_range exception should be thrown. 
* Parameters 
* 	index	The index in the image to access
* Returns a pointer to the image at that index
*/
epng::png * collage::at (uint64_t index)
{
    if(index > size_)
	throw std::out_of_range("index out of bounds");
    else
    {
	return std::get<2>(layers_[index]).get();
    }

}

/**
* Draws the collage onto a new image, respecting the layer structure 
* and the image coordinates, and returns that new image. 
*/
epng::png collage::draw () const
{
    uint64_t w = 0;
    uint64_t h = 0;

    for (uint64_t i = 0; i < size_; ++i)
    {
	if (!((std::get<2>(layers_[i])).empty()))
	{
	    w = std::max(w, std::get<0>(layers_[i]) + std::get<2>(layers_[i])->width());
	    h = std::max(h, std::get<1>(layers_[i]) + std::get<2>(layers_[i])->height());
	}
    }

    epng::png canvas(w, h);
    epng::rgba_pixel* canvas_pixel = nullptr;

    for (uint64_t i = 0; i < size_; ++i)
    {
	if (!((std::get<2>(layers_[i])).empty()))
	{ 
	    auto width = std::get<2>(layers_[i])->width();
	    auto height = std::get<2>(layers_[i])->height();

	    const int x_offset = std::get<0>(layers_[i]);
	    const int y_offset = std::get<1>(layers_[i]);

	    for (size_t x = 0; x < width; ++x)
	    {
	    	for (size_t y = 0; y < height; ++y)
		{
		    canvas_pixel = canvas(x_offset + x, y_offset + y);
		    canvas_pixel->red = (*(std::get<2>(layers_[i]).get()))(x, y)->red;
		    canvas_pixel->blue = (*(std::get<2>(layers_[i]).get()))(x, y)->blue;
		    canvas_pixel->green = (*(std::get<2>(layers_[i]).get()))(x, y)->green;
		    canvas_pixel->alpha = (*(std::get<2>(layers_[i]).get()))(x, y)->alpha;
		}
	    }
	}
    }

    return canvas;

}

} // namespace cs225
