#pragma once

#include <chrono>

auto GetTimeMS()
{
	auto time_now = std::chrono::system_clock::now();
	auto duration_in_ms = std::chrono::duration_cast<std::chrono::milliseconds>(time_now.time_since_epoch());

	return duration_in_ms.count();
}

auto GetTimeUS()
{
	auto time_now = std::chrono::system_clock::now();
	auto duration_in_us = std::chrono::duration_cast<std::chrono::nanoseconds>(time_now.time_since_epoch());

	return duration_in_us.count();
}
