#pragma once
#include <thread>
#include <iostream>
void simple_thread_demo() {
	std::thread t([]() {
		int i_count = 0;
		while (i_count < 100) {
			std::cout << "thread is running " << ++i_count << " times" << std::endl;
		}
	}
	);
	t.join();
	std::cout << "thread is finished" << std::endl;
}

void condition_variable_demo() {
	auto now = std::chrono::system_clock::now();
}