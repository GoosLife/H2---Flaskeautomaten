#include "ArrayBuffer.h"

void ArrayBuffer::AddBottle(std::string bottleType)
{
	// Add the bottle to the buffer
	buffer[size] = bottleType;
	size++;
}

std::string ArrayBuffer::RemoveBottle()
{
	// Remove bottle from the buffer
	std::string bottle = buffer[0];
	for (int i = 0; i < size; i++)
	{
		buffer[i] = buffer[i + 1];
	}
	size--;
	return bottle;
}