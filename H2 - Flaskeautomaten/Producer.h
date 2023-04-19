#pragma once
#include <iostream>

/// <summary>
/// Producer class that handles the production of bottles.
/// </summary>
class Producer
{
public:
	Producer() {}
	~Producer() {}

	// Produce bottles
	void Produce();
private:

	// Counters for produced bottles of each type
	inline static int WatersProduced = 0;
	inline static int BeersProduced = 0;

	// Produce a bottle of the given type
	void ProduceBottle(std::string bottleType);
};