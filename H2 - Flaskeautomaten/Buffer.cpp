#include "Buffer.h"

// Add the bottle to the buffer
void Buffer::AddBottle(std::string bottleType)
{
	BufferQueue.push(bottleType);
}

// Remove bottle from the buffer
std::string Buffer::RemoveBottle() {

	// Grab the first element in the queue as per FIFO, then remove it from the queue and return its value
	std::string bottle = BufferQueue.front();
	BufferQueue.pop();
	return bottle;
}