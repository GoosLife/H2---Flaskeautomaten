#pragma once
#include "Buffer.h"
#include <string>

#define ARRAY_SIZE 10

/// <summary>
/// Buffer class that handles the buffer for the water and beer bottles,
/// using an array as the buffer instead of a queue making it faster.
/// </summary>
class ArrayBuffer : public Buffer
{
public:
	ArrayBuffer() {}
	~ArrayBuffer() {}

	// Add and remove bottles from the buffer
	void AddBottle(std::string bottleType);
	std::string RemoveBottle();
	
	// Getters
	int GetSize() { return size; } // Get the current size (index) of the buffer
	bool IsEmpty() { return size == 0; } // Check if the buffer is empty
	bool IsFull() { return size == maxSize; } // Check if the buffer is full

private:
		std::string buffer[MAX_SIZE]; // Allocate the buffer to the max size of the buffer (defined in Buffer.h)
		int size = 0; // Set the current size of the buffer (effectively the index of the last element in the buffer)
		int maxSize = MAX_SIZE; // Set the max size of the buffer
};

