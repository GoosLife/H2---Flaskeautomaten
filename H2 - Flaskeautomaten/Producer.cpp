#include "Producer.h"
#include <condition_variable>
#include <mutex>

void Producer::Produce() {
	while (true) {
		int bottleType = rand() % 2;

		if (bottleType == 1) {
			ProduceBottle("Water");
		}
		else {
			ProduceBottle("Beer");
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1500 + 500)); // Sleep for 0.5 - 2 seconds
	}
}

void Producer::ProduceBottle(std::string bottleName) {
	std::unique_lock globalUniqueLock(globalBufferLock, std::defer_lock);
	globalBufferConditionVariable.wait(globalUniqueLock, [bottleName] {globalBuffer.AddBottle(bottleName); return true; });	

	globalBufferConditionVariable.notify_all();

	//if (bottleName == "Water") {
	//	std::unique_lock<std::mutex> waterUniqueLock(waterBufferLock, std::defer_lock);
	//	waterBufferConditionVariable.wait(waterUniqueLock, [bottleName] {waterBuffer.AddBottle(bottleName); WatersProduced++; return true; });
	//	waterBufferConditionVariable.notify_all();
	//	std::cout << " Total produced: " << WatersProduced << std::endl;
	//}
	//else {
	//	std::unique_lock<std::mutex> beerUniqueLock(beerBufferLock, std::defer_lock);
	//	beerBufferConditionVariable.wait(beerUniqueLock, [bottleName] {beerBuffer.AddBottle(bottleName); BeersProduced++; return true; });
	//	beerBufferConditionVariable.notify_all();
	//	std::cout << " Total produced: " << BeersProduced << std::endl;
	//}
}