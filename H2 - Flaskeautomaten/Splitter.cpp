#include "Splitter.h"
#include "Buffer.h"
#include "Globals.h"
#include <queue>
#include <string>

/// <summary>
/// The splitter takes the bottles from the global buffer and splits them into the water and beer buffers.
/// </summary>
void Splitter::Run()
{
	while (true) {
		// Wait for the global buffer to be available
		std::unique_lock<std::mutex> globalUniqueLock(globalBufferLock, std::defer_lock);
		globalBufferConditionVariable.wait(globalUniqueLock, [this] {
			// Take the bottles out of the global buffer and store them in the local "buffer" (which is actually an integer value - the splitter can handle many more bottles than the buffers)
			SplitBottles();
			return true;
			});
		// Notify the condition variable that the global buffer is available
		globalBufferConditionVariable.notify_all();

		// Split the bottles into the water and beer buffers
		SplitBeer();
		SplitWater();

		std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1500 + 500)); // Sleep for 0.5 - 2 seconds
	}
}

/// <summary>
/// Sort all the bottles from the global buffer into the water and beer buffers
/// </summary>
void Splitter::SplitBottles() {
	// Here we take the bottles out of the global buffer, and split them based on their type.
	// A very simplistic method of splitting is used here, because we know that there can only be two types of bottles.
	// If there were more bottles, we would have to use a more complex method of splitting, such as a hash table or a map.
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

/// <summary>
/// Send the beers to the beer buffer
/// </summary>
void Splitter::SplitBeer() {

	// Wait for the beer buffer to be available
	std::unique_lock uniqueBeerLock(beerBufferLock, std::defer_lock);
	beerBufferConditionVariable.wait(uniqueBeerLock, [this] {

		int times = amountOfBeers; // This is needed because amountOfBeers is decremented in the for loop

		for (int i = 0; i < times; i++) {

			if (beerBuffer.IsFull()) // If the beer buffer is full, stop adding bottles
			{
				break;
			}

			// Add the bottle to the beer buffer
			beerBuffer.AddBottle("Beer");
			// And remove it from the splitter's "buffer"
			amountOfBeers--;
		}

		// Return true to notify the condition variable
		return true;
		});

	// Notify the condition variable that the beer buffer is available
	beerBufferConditionVariable.notify_all();
}

/// <summary>
///	Send the waters to the water buffer
/// </summary>
void Splitter::SplitWater() {

	// Wait for the water buffer to be available
	std::unique_lock uniqueWaterLock(waterBufferLock, std::defer_lock);
	waterBufferConditionVariable.wait(uniqueWaterLock, [this] {

		int times = amountOfWaters; // This is needed because amountOfWaters is decremented in the for loop
		
		for (int i = 0; i < times; i++) {

			// If the water buffer is full, stop adding bottles
			if (waterBuffer.IsFull())
			{
				break;
			}

			// Add the bottle to the water buffer
			waterBuffer.AddBottle("Water");
			// And remove it from the splitter's "buffer"
			amountOfWaters--;
		}

		// Return true to notify the condition variable
		return true;
		});

	// Notify the condition variable that the water buffer is available
	waterBufferConditionVariable.notify_all();
}