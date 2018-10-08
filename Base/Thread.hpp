#pragma once
#include <thread>
#include <mutex>
#include <future>
#include <list>
#include <iostream>
void simple_thread_demo() {
	std::cout << "main thread id is " << std::this_thread::get_id() << std::endl;
	std::thread empty_thread;
	//线程对象不能拷贝，但是可以转移，如下
	std::thread move_thread;
	move_thread = std::move(std::thread([] {
		std::cout << "a new thread id is " << std::this_thread::get_id() << std::endl;
		int i_count = 0;
		while (i_count < 100) {
			std::cout << "thread is running " << ++i_count << " times" << std::endl;
		}
	}));
	//转移后的线程会成为空线程对象
	if (move_thread.joinable()) {//检查线程是否可以join
		std::cout << "thread is joinable" << std::endl;
	}
	move_thread.join();
	std::cout << "thread is finished" << std::endl;
}

void mutex_simple_demo() {
	int id = 0;
	std::mutex mutex;
	std::thread array_thread[10];
	for (int i = 0; i < 10; ++i) {
		array_thread[i] = std::thread([&] {
			mutex.lock();
			std::cout << ++id << std::endl;
			mutex.unlock();
		});
	}
	for (auto& thread : array_thread) {
		thread.join();
	}
}

void mutex_recursive_demo() {

}

void muex_time_demo() {

}

void condition_variable_demo() {
	auto now = std::chrono::system_clock::now();

	std::mutex m_mutex, m_mutex1;
	std::condition_variable m_cv;
	std::list<int> m_list;
	auto customer = [&]() {
		//std::this_thread::sleep_for(std::chrono::seconds(1));
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

void promise_test_demo() {
	std::promise<int> promise;
	auto future = promise.get_future();
	std::thread([](std::future<int>&& future) {
		std::cout << "future get: " << future.get() << std::endl;
	}, std::move(future)).detach();
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	promise.set_value(20);
}

void packaged_task_demo() {
	std::packaged_task<int()> task([]()->int {
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
		return 20;
	});
	auto future = task.get_future();

	std::thread(std::move(task)).detach();

	std::cout << future.get() << std::endl;
}

void async_test_demo() {
	auto future = std::async(packaged_task_demo);
}