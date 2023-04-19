#include "Consumer.h"
#include "Globals.h"
#include "Buffer.h"

// Take a bottle from the buffer and consume it
void Consumer::Consume() {
	while (true)
	{
		// Here I simply check the type of consumer to decide which buffers, locks and condition variables to use. It is not a very scalable solution, but it is very easy to implement as long as we only have two buffers.
		// If we had more buffers, we might use a map to store the buffers, locks and condition variables and use the type as the key to access the correct ones.
		if (type == "Water")
		{
			// Create a unique lock for the water buffer, then wait for the condition variable to be notified
			std::unique_lock waterUniqueLock(waterBufferLock, std::defer_lock);
			waterBufferConditionVariable.wait(waterUniqueLock, [this]
				{
					// If the buffer is empty, go back and try again later.
					if (waterBuffer.IsEmpty())
					{
						return true;
					}

					// Get the next bottle from the buffer
					std::string bottleType = waterBuffer.RemoveBottle();

					// Consume the bottle
					consumedWaterBottles.fetch_add(1);

					return true; // Return true to notify the condition variable that we are done

				});
			// Notify the condition variable that we are done
			waterBufferConditionVariable.notify_all();
		}
		// Exactly the same as above, but for the beer buffer (and associated locks and condition variables)
		else if (type == "Beer")
		{
			std::unique_lock beerUniqueLock(beerBufferLock, std::defer_lock);
			beerBufferConditionVariable.wait(beerUniqueLock, [this]
				{
					// If the buffer is empty, wait for a new bottle
					if (beerBuffer.IsEmpty())
					{
						return true;
					}

					// Get the next bottle from the buffer
					std::string bottleType = beerBuffer.RemoveBottle();

					// Consume the bottle
					consumedBeerBottles.fetch_add(1);

					return true; // Return true to notify the condition variable that we are done

				});

			beerBufferConditionVariable.notify_all();
		}

		// Every man, woman and thread deserves to rest after a hard day of work :)
		std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1500 + 500));
	}
}