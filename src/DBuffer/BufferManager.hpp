#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <memory>

class Buffered_base;

class BufferManager_{
public:
	std::list<std::shared_ptr<Buffered_base>> bufferedObjs;
	BufferManager_();
	void swap();
};

inline BufferManager_ currentBufferManager;
