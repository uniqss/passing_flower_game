#include "fake_rand.h"
#include <stdlib.h>

#include <chrono>

#include "mersenne_rand.h"


void FakeRandInit()
{
	auto time_now = std::chrono::system_clock::now();
	auto duration_in_us = std::chrono::duration_cast<std::chrono::nanoseconds>(time_now.time_since_epoch());

#if 0
	mtsrand(duration_in_us.count());
#else
	// for test
	mtsrand(12345);
#endif
}

size_t FakeRand()
{
	return mtrandi();
}
