#pragma once
#include <thread>
#include <mutex>
#include <list>
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

	std::mutex m_mutex, m_mutex1;
	std::condition_variable m_cv;
	std::list<int> m_list;
	auto customer = [&]() {
		/*std::this_thread::sleep_for(std::chrono::seconds(1));*/
		while (1) {
			std::unique_lock<std::mutex> lk(m_mutex);
			m_cv.wait(lk/*, [&]() {return !m_list.empty(); }*/);
			for (const auto& item : m_list) {
				std::cout << "Custom Finished " << item << std::endl;
			}
			m_list.clear();
			m_cv.notify_one();
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		}
		
		
	};
	auto producter = [&]() {
		std::this_thread::sleep_for(std::chrono::seconds(1));
		while (1) {
			{
				std::lock_guard<std::mutex> lk(m_mutex);
				m_list.push_back(rand());
				std::cout << "Product Create " << std::endl;
			}
			m_cv.notify_one();
			std::unique_lock<std::mutex> lk(m_mutex);
			m_cv.wait(lk/*, [&]() {return m_list.empty(); }*/);
			lk.unlock();
			std::this_thread::sleep_for(std::chrono::milliseconds(300));
		}
	};

	std::thread t1(customer), t2(producter);
	t1.join();
	t2.join();
}