#pragma once

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>

#define MAX_SIZE 10; // Set the max size of the buffer
class Buffer
{
public:
	Buffer() {}
	~Buffer() {}
	void AddBottle(std::string bottleType);
	std::string RemoveBottle();
	bool IsEmpty() { return BufferQueue.empty(); }
	int GetSize() { return (int)BufferQueue.size(); }
	bool IsFull() { return BufferQueue.size() == maxSize; }

	// std::queue<std::string> GetBufferQueue() { return BufferQueue; }

private:
	std::queue<std::string> BufferQueue;
	int maxSize = MAX_SIZE; // Set the max size of the buffer
};

// Create condition variables for the producer and consumers to use when accessing the buffers
inline std::condition_variable waterBufferConditionVariable;
inline std::condition_variable beerBufferConditionVariable;
inline std::condition_variable globalBufferConditionVariable;

// Create locks for the buffers and consumers to use when accessing the buffers
inline std::mutex waterBufferLock;
inline std::mutex beerBufferLock;
inline std::mutex globalBufferLock;