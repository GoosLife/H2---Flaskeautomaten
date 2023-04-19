#pragma once
#include "Buffer.h"
#include "Globals.h"

/// <summary>
/// Consumer class that handles the consumption of bottles from the buffer.
/// </summary>
class Consumer
{
public:
	Consumer(std::string type) : type(type) {}
	~Consumer() {}

	// Take a bottle from the buffer and consume it
	void Consume();

	// Getters
	int GetConsumedWaterBottles() { return consumedWaterBottles; }
	int GetConsumedBeerBottles() { return consumedBeerBottles; }

private:
	std::string type;
	
	// Counters for consumed bottles of each type - they are atomic to make sure they are thread safe and synchronized between threads. 
	// In this case, they are used by the main thread to print the results as well as the consumer threads to increment them.
	inline static std::atomic<int> consumedWaterBottles = 0;
	inline static std::atomic<int> consumedBeerBottles = 0;
};