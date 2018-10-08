#include <chrono>
#include <ctime>
#include <iostream>

void SystemClockTest() {
	{
		std::chrono::system_clock::time_point t0 = std::chrono::system_clock::now();
		std::cout << t0.time_since_epoch().count() << std::endl;
		std::chrono::system_clock::time_point t1 = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed = t1 - t0;
		std::cout << elapsed.count() << std::endl;
		std::time_t st = std::chrono::system_clock::to_time_t(t1);
	}

	{
		std::chrono::high_resolution_clock::time_point t0 = std::chrono::high_resolution_clock::now();
		std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

		std::chrono::microseconds micro_t = std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0);

	}
}