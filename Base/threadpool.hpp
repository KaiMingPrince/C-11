#pragma once
#include <iostream>
#include <queue>
#include <functional>
#include <mutex>
#include <atomic>

std::vector<std::shared_ptr<std::thread> > thread_vec;
std::queue <std::function<void()> > task_queue;
std::mutex task_queue_mutex;
std::condition_variable task_cond_get;
std::condition_variable task_cond_put;
std::atomic<bool> is_task_stop = false;
const int max_task_queue_size = 1000;
const int max_thread_size = 30;

void run_task() {
	while (1) {
		std::unique_lock<std::mutex> locker(task_queue_mutex);
		if (task_queue.empty() && !is_task_stop) {
			task_cond_get.wait(locker);
		}

		if (is_task_stop)
			break;

		if (!task_queue.empty())
		{
			auto task = std::move(task_queue.front());
			task_queue.pop();
			if (task) {
				task();
				task_cond_put.notify_one();
			}
		}
	}
}

void add_task(std::function<void()>&& task)
{
	std::unique_lock<std::mutex> locker(task_queue_mutex);
	if (task_queue.size() == max_task_queue_size && !is_task_stop){
		task_cond_put.wait(locker);
	}
	task_queue.push(task);
	task_cond_get.notify_one();
}

void create_thread(int num)
{
	if (num < 0 || num > max_thread_size) {
		printf("The Thread Number is out of range\n");
		return;
	}
	for (size_t i = 0; i < num; ++i)
	{
		thread_vec.push_back(std::move(std::make_shared<std::thread>(run_task)));
	}
}

void terminate_all()
{
	is_task_stop = true;
	task_cond_get.notify_all();

	for (auto& thread_ptr : thread_vec)
	{
		if (thread_ptr && thread_ptr->joinable()) {
			thread_ptr->join();
		}
	}
	thread_vec.clear();

	std::lock_guard<std::mutex> locker(task_queue_mutex);
	while (!task_queue.empty()) {
		task_queue.pop();
	}
}

void test_task(int arg)
{
	std::cout << "Current thread id: " << std::this_thread::get_id() << "  arg: " << arg << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(400));
}

void test_demo() {
	create_thread(20);
	for (size_t i = 0; i < 900; ++i)
	{
		if (i == 400)
			terminate_all();
		add_task(std::bind(test_task, i));
	}
}