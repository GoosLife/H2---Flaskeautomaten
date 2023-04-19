#pragma once
#include "Buffer.h"
#include <string>
class ArrayBuffer : public Buffer
{
public:
	ArrayBuffer() {}
	~ArrayBuffer() {}
	void AddBottle(std::string bottleType);
	std::string RemoveBottle();
	bool IsEmpty() { return size == 0; }
	int GetSize() { return size; }
	bool IsFull() { return size == maxSize; }

private:
		std::string buffer[10];
		int size = 0;
		int maxSize = MAX_SIZE;
};

