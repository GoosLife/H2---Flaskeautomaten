#pragma once
#include "Buffer.h"

class Consumer
{
public:
	Consumer(std::string type) : type(type) {}
	~Consumer() {}
	void Consume();
	int GetConsumedWaterBottles() { return consumedWaterBottles; }
	int GetConsumedBeerBottles() { return consumedBeerBottles; }

private:
	std::string type;
	inline static int consumedWaterBottles = 0;
	inline static int consumedBeerBottles = 0;
};
