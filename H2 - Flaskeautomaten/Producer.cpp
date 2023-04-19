#include "Producer.h"
#include "GlobalBuffers.h"
#include <condition_variable>
#include <mutex>

void Producer::Produce() {
	while (true) {
		if (!globalBuffer.IsFull())
		{
			int bottleType = rand() % 2;

			if (bottleType == 1)
			{
				ProduceBottle("Water");
			}
			else
			{
				ProduceBottle("Beer");
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1500 + 500)); // Sleep for 0.5 - 2 seconds
		}
	}
}

void Producer::ProduceBottle(std::string bottleName) {
	std::unique_lock globalUniqueLock(globalBufferLock, std::defer_lock);
	globalBufferConditionVariable.wait(globalUniqueLock, [bottleName] {
		globalBuffer.AddBottle(bottleName); 
		return true; 
		});	

	globalBufferConditionVariable.notify_all();
}