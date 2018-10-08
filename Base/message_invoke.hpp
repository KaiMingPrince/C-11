#pragma once
#include <thread>
#include <atomic>
#include <condition_variable>
class message_invoke_process {
public:
	using message_task_t = std::function<void(std::string, std::string, std::function<void()>, 
		std::function<void()>)>;
	message_invoke_process() {

	}
	~message_invoke_process() {

	}

	void add_message(message_task_t message);
	void process_thread();

private:
	std::atomic<bool>	m_b_is_finished = false;
	std::condition_
};