#pragma once

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>

#define MAX_SIZE 10 // Set the max size of the buffer

/// <summary>
/// The buffer class that handles the buffer for the water and beer bottles.
/// This class has been replaced by the ArrayBuffer class, which uses an array as the buffer instead of a queue.
/// </summary>
class Buffer
{
public:
	Buffer() {}
	~Buffer() {}

	// Add and remove bottles from the buffer
	void AddBottle(std::string bottleType);
	std::string RemoveBottle();

	// Getters
	bool IsEmpty() { return BufferQueue.empty(); }
	int GetSize() { return (int)BufferQueue.size(); }
	bool IsFull() { return BufferQueue.size() == maxSize; }

private:
	std::queue<std::string> BufferQueue; // Allocate the buffer
	int maxSize = MAX_SIZE; // Set the max size of the buffer
};