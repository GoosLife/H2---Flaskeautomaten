#include "ArrayBuffer.h"

// Add the bottle to the buffer
void ArrayBuffer::AddBottle(std::string bottleType)
{
	buffer[size] = bottleType;
	size++;
}

// Remove bottle from the buffer
std::string ArrayBuffer::RemoveBottle()
{
	std::string bottle = buffer[0]; // Get the first element in the buffer

	for (int i = 0; i < size; i++)
	{
		buffer[i] = buffer[i + 1]; // Shift the elements in the buffer to the left
	}
	
	size--; // Decrement the size of the buffer (as we removed an element)
	
	return bottle;
}