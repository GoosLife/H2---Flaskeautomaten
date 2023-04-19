#include "Splitter.h"
#include "Buffer.h"
#include "GlobalBuffers.h"
#include <queue>
#include <string>

void Splitter::Run()
{
	while (true) {
		// Grab a bottle from the buffer
		std::unique_lock<std::mutex> globalUniqueLock(globalBufferLock, std::defer_lock);
		globalBufferConditionVariable.wait(globalUniqueLock, [this] {
			SplitBottles();
			return true;
			});
		globalBufferConditionVariable.notify_all();

		SplitBeer();
		SplitWater();

		std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1500 + 500)); // Sleep for 0.5 - 2 seconds
	}
}

void Splitter::SplitBottles() {
	for (int i = 0; i < globalBuffer.GetSize(); i++) {
		std::string bottle = globalBuffer.RemoveBottle();
		if (bottle == "Water") {
			amountOfWaters++;
		}
		else {
			amountOfBeers++;
		}
	}
}

void Splitter::SplitBeer() {
	std::unique_lock uniqueBeerLock(beerBufferLock, std::defer_lock);
	beerBufferConditionVariable.wait(uniqueBeerLock, [this] {
		int times = amountOfBeers; // This is needed because amountOfBeers is decremented in the for loop
		for (int i = 0; i < times; i++) {
			if (beerBuffer.IsFull())
			{
				break; // Stop and move the rest of the bottles next time
			}

			beerBuffer.AddBottle("Beer");
			amountOfBeers--;
		}

		return true;
		});
	beerBufferConditionVariable.notify_all();
}

void Splitter::SplitWater() {
	std::unique_lock uniqueWaterLock(waterBufferLock, std::defer_lock);
	waterBufferConditionVariable.wait(uniqueWaterLock, [this] {
		int times = amountOfWaters; // This is needed because amountOfWaters is decremented in the for loop
		for (int i = 0; i < times; i++) {
			if (waterBuffer.IsFull())
			{
				break; // Stop and move the rest of the bottles next time
			}

			waterBuffer.AddBottle("Water");
			amountOfWaters--;
		}

		return true;
		});
	waterBufferConditionVariable.notify_all();
}