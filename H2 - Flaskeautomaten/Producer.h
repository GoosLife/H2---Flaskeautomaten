#pragma once
#include "Buffer.h"
#include <iostream>

class Producer
{
public:
	Producer() {}
	~Producer() {}
	void Produce();
private:
	inline static int WatersProduced = 0;
	inline static int BeersProduced = 0;

	void ProduceBottle(std::string bottleType);
};