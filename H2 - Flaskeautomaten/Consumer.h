#pragma once
#include "Buffer.h"

class Consumer
{
public:
	Consumer(Buffer buffer) : Buffer(buffer) {}
	~Consumer() {}
	void Consume(std::mutex mtx, std::condition_variable cv);
	int GetConsumedBottles() { return consumedBottles; }

private:
	// The buffer to consume from 
	Buffer Buffer;
	int consumedBottles = 0;
};
