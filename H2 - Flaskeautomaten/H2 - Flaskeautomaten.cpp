#include "Buffer.h"
#include "Globals.h"
#include "Consumer.h"
#include "Producer.h"
#include "Splitter.h"

#include <iostream>

int main()
{
    // Initialize the random number generator with a seed value
    srand((unsigned)time(NULL));

    // Create a producer and two consumers
    Producer producer;
    Consumer waterConsumer = Consumer("Water");
    Consumer beerConsumer = Consumer("Beer");
    Splitter splitter;

    // Start a thread for each consumer and the producer 
    std::thread producerThread(&Producer::Produce, &producer);
    std::thread splitterThread(&Splitter::Run, &splitter);
    std::thread waterConsumerThread(&Consumer::Consume, &waterConsumer);
    std::thread beerConsumerThread(&Consumer::Consume, &beerConsumer);

    while (true) {
        system("CLS");
        // Output status of the producer/consumer threads
        // Bottles in global buffer
        std::cout << "Bottles in global buffer: " << globalBuffer.GetSize() << std::endl;
        // Bottles in water buffer
        std::cout << "Bottles in water buffer: " << waterBuffer.GetSize() << std::endl;
        // Bottles in beer buffer
        std::cout << "Bottles in beer buffer: " << beerBuffer.GetSize() << std::endl;
        // Consumed water bottles
         std::cout << "Consumed water bottles: " << waterConsumer.GetConsumedWaterBottles() << std::endl;
        // Consumed beer bottles
        std::cout << "Consumed beer bottles: " << beerConsumer.GetConsumedBeerBottles() << std::endl;
        // Updating the console once per second is more than enough for human readability
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    // Join the threads
    producerThread.join();
    splitterThread.join();
    waterConsumerThread.join();
    beerConsumerThread.join();

    // Wait for user input before exiting
    char c;
    std::cin >> c;
}