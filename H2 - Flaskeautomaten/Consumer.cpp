#include "Consumer.h"
#include "Buffer.h"

// Take a bottle from the buffer and consume it
void Consumer::Consume(std::mutex mtx, std::condition_variable cv) {
	while (true) {
		std::unique_lock uniqueLock(mtx, std::defer_lock);
		cv.wait(uniqueLock, [this] {
			// Get the next bottle from the buffer
			std::string bottleType = Buffer.GetBufferQueue().front();
			Buffer.GetBufferQueue().pop();
			return true;
			});

		// Consume the bottle
		consumedBottles++;
	}
}