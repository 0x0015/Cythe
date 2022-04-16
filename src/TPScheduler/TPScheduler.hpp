#pragma once
#include <iostream>
#include <thread>
#include <functional>
#include <vector>
#include <map>
#include <atomic>
#include <condition_variable>
#include <semaphore>

class TPScheduler {
public:
	uint16_t reservedThreadCount = 1;//by default leave the main thread that controls the adding of functions.
	std::atomic<bool> stop = false;
	std::vector<std::thread> threadPool;
	std::atomic<unsigned int> waitingFuncNum = 0;
	std::multimap<uint32_t, std::function<void()>> waitingFunctions; //uint32_t for weight so more important functions will be called first
	std::mutex waitingFunctions_mutex;
	std::binary_semaphore waitingFunctions_semaphore{0};
	void queueFunction(uint32_t weight, std::function<void()> func);
	void waitForQueue();
	TPScheduler(uint16_t reservedThreadCount = 1);
	~TPScheduler();
private:
	void TP_F(uint16_t threadNum);
};
