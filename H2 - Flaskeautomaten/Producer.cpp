#include "Producer.h"
#include "Globals.h"
#include <condition_variable>
#include <mutex>

void Producer::Produce() {
	while (true) {
		// If the global buffer is not full, produce a bottle.
		if (!globalBuffer.IsFull())
		{
			// Randomly choose between water and beer
			int bottleType = rand() % 2;

			// Produce a bottle of the chosen type
			if (bottleType == 1)
			{
				ProduceBottle("Water");
			}
			else
			{
				ProduceBottle("Beer");
			}

			// Producing bottles takes time, so sleep for a random amount of time
			std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1500 + 500)); // Sleep for 0.5 - 2 seconds
		}
	}
}

void Producer::ProduceBottle(std::string bottleName) {
	// Wait for the global buffer to be available
	std::unique_lock globalUniqueLock(globalBufferLock, std::defer_lock);
	globalBufferConditionVariable.wait(globalUniqueLock, [bottleName] {
		// Add the bottle to the global buffer
		globalBuffer.AddBottle(bottleName);
		// Return true to notify the condition variable
		return true; 
		});	

	// Notify the condition variable that the global buffer is available
	globalBufferConditionVariable.notify_all();
}