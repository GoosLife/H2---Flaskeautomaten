#pragma once
#include "ArrayBuffer.h"
#include <condition_variable>
#include <mutex>

// Header file to store globally used variables
// This is done to avoid having to pass the variables as parameters to the functions
// It is not the prettiest solution, but it works for this project

// Create condition variables for the producer and consumers to use when accessing the buffers
inline std::condition_variable waterBufferConditionVariable;
inline std::condition_variable beerBufferConditionVariable;
inline std::condition_variable globalBufferConditionVariable;

// Create locks for the buffers and consumers to use when accessing the buffers
inline std::mutex waterBufferLock;
inline std::mutex beerBufferLock;
inline std::mutex globalBufferLock;

// Create two buffers; one for water and one for beer
inline ArrayBuffer waterBuffer;
inline ArrayBuffer beerBuffer;

// Create a global buffer that collects all buffers before splitting them
inline ArrayBuffer globalBuffer;