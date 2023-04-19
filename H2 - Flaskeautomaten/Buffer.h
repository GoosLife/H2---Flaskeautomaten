#pragma once

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>

class Buffer
{
public:
	Buffer() {}
	~Buffer() {}
	void AddBottle(std::string bottleType);
	std::string RemoveBottle();

	std::queue<std::string> GetBufferQueue() { return BufferQueue; }

private:
	std::queue<std::string> BufferQueue;
};

// Create condition variables for the producer and consumers to use when accessing the buffers
inline std::condition_variable waterBufferConditionVariable;
inline std::condition_variable beerBufferConditionVariable;
inline std::condition_variable globalBufferConditionVariable;

// Create locks for the buffers and consumers to use when accessing the buffers
inline std::mutex waterBufferLock;
inline std::mutex beerBufferLock;
inline std::mutex globalBufferLock;

// Create two buffers; one for water and one for beer
inline Buffer waterBuffer;
inline Buffer beerBuffer;

// Create a global buffer that collects all buffers before splitting them
inline Buffer globalBuffer;