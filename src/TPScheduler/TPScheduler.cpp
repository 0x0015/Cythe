#include "TPScheduler.hpp"
#include "../Logger/Logger.hpp"

void TPScheduler::TP_F(uint16_t threadNum){
	while(true){
		waitingFunctions_semaphore.acquire();
		if(stop){
			waitingFunctions_semaphore.release();
			return;
		}
		Logger::log("Thread ",threadNum," unlocked.");
		while(waitingFuncNum > 0){
			waitingFunctions_mutex.lock();
			auto bg = waitingFunctions.begin();
			std::function<void()> item = (*bg).second;
			waitingFunctions.erase(bg);
			waitingFunctions_mutex.unlock();
			waitingFuncNum--;
			item();
		}
	}
}

void TPScheduler::queueFunction(uint32_t weight, std::function<void()> func){
	waitingFunctions_mutex.lock();
	waitingFunctions.insert(std::pair{weight, func});
	waitingFunctions_mutex.unlock();
	waitingFuncNum++;
	waitingFunctions_semaphore.release();
}

void TPScheduler::waitForQueue(){
	while(waitingFuncNum > 0){
		waitingFunctions_semaphore.acquire();
	}
}

TPScheduler::TPScheduler(uint16_t reservedThreadCount){
	int hardT = (int)std::thread::hardware_concurrency() - (int)reservedThreadCount;
	if(hardT <= 0){
		hardT = 1;
	}
	Logger::log("Starting ",hardT," threads.");
	for(int i=0;i<hardT;i++){
		threadPool.push_back(std::thread(&TPScheduler::TP_F, this, i));
	}
}

TPScheduler::~TPScheduler(){
	stop = true;
	for(auto& o : threadPool){
		waitingFunctions_semaphore.release();
		o.join();
	}
	Logger::log("Successfully ended all threads in threadpool");
}
