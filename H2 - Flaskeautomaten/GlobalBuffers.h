#pragma once
#include "ArrayBuffer.h"

// Create two buffers; one for water and one for beer
inline ArrayBuffer waterBuffer;
inline ArrayBuffer beerBuffer;

// Create a global buffer that collects all buffers before splitting them
inline ArrayBuffer globalBuffer;