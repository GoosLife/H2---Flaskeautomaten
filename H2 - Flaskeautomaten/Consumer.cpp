#include "Consumer.h"
#include "Buffer.h"

// Take a bottle from the buffer and consume it
void Consumer::Consume() {
	while (true)
	{
		if (type == "Water")
		{
			std::unique_lock waterUniqueLock(waterBufferLock, std::defer_lock);
			waterBufferConditionVariable.wait(waterUniqueLock, [this]
				{
					// If the buffer is empty, wait for a new bottle
					if (waterBuffer.GetBufferQueue().empty())
					{
						return true;
					}

					// Get the next bottle from the buffer
					std::string bottleType = waterBuffer.GetBufferQueue().front();
					waterBuffer.GetBufferQueue().pop();

					// Consume the bottle
					consumedWaterBottles++;

					return true;

				});

			waterBufferConditionVariable.notify_all();
		}
		else if (type == "Beer")
		{
			std::unique_lock beerUniqueLock(beerBufferLock, std::defer_lock);
			beerBufferConditionVariable.wait(beerUniqueLock, [this]
				{
					// If the buffer is empty, wait for a new bottle
					if (beerBuffer.GetBufferQueue().empty())
					{
						return true;
					}

					// Get the next bottle from the buffer
					std::string bottleType = beerBuffer.GetBufferQueue().front();
					beerBuffer.GetBufferQueue().pop();

					// Consume the bottle
					consumedBeerBottles++;

					return true;

				});

			beerBufferConditionVariable.notify_all();
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1500 + 500));
	}
}