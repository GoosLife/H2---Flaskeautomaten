#include "Buffer.h"

void Buffer::AddBottle(std::string bottleType)
{
	// Add the bottle to the buffer
	BufferQueue.push(bottleType);
}

std::string Buffer::RemoveBottle() {
	// Remove bottle from the buffer
	std::string bottle = BufferQueue.front();
	BufferQueue.pop();
	return bottle;
}