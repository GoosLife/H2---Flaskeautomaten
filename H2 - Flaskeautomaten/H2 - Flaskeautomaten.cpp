#include "Buffer.h"
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
    Consumer waterConsumer = Consumer(waterBuffer);
    Consumer beerConsumer = Consumer(beerConsumer);
    Splitter splitter;

    // Start a thread for each consumer and the producer 
    std::thread producerThread(&Producer::Produce, &producer);
    std::thread splitterThread(&Splitter::Run, &splitter);
    std::thread waterConsumerThread(&Consumer::Consume, &waterConsumer, &waterBufferLock, &waterBufferConditionVariable);
    std::thread beerConsumerThread(&Consumer::Consume, &beerConsumer, &beerBufferLock, &beerBufferConditionVariable);

    // start a water consumer thread that passes the waterBufferLock and waterBufferConditionVariable to the consume function as parameters
    std::thread waterConsumerThreadWithParameters([waterConsumer] {waterConsumer.Consume(waterBufferLock, waterBufferConditionVariable);});

    while (true) {
        system("CLS");
        // Output status of the producer/consumer threads
        // Bottles in global buffer
        std::cout << "Bottles in global buffer: " << globalBuffer.GetBufferQueue().size() << std::endl;
        // Bottles in water buffer
        std::cout << "Bottles in water buffer: " << waterBuffer.GetBufferQueue().size() << std::endl;
        // Bottles in beer buffer
        std::cout << "Bottles in beer buffer: " << beerBuffer.GetBufferQueue().size() << std::endl;
        // Consumed water bottles
         std::cout << "Consumed water bottles: " << waterConsumer.GetConsumedBottles() << std::endl;
        // Consumed beer bottles
        std::cout << "Consumed beer bottles: " << beerConsumer.GetConsumedBottles() << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    producerThread.join();

    // Wait for user input before exiting
    char c;
    std::cin >> c;
}