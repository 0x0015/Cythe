#pragma once
#include <iostream>
#include "BufferManager.hpp"

class Buffered_base{
public:
	bool toDelete = false;
	bool changed = false;
	virtual void copy();
	virtual void swap();
	Buffered_base();
};

template <typename T> class Buffered_base_t : public Buffered_base{
public:
	T o1;
	T o2;
	T* front = &o1;
	T* back = &o2;
	void copy(){
		*back = *front;
	}
	void swap(){
		T* temp = back;
		back = front;
		front = temp;
	}
	Buffered_base_t(){}
	Buffered_base_t(const T& init){
		o1 = init;
		o2 = init;
	}
};

template <typename T> class Buffered{
private:
	std::shared_ptr<Buffered_base_t<T>> be;
public:
	const T& get() const {
		return(*be->back);
	}
	void set(const T& nval){
		*be->front = nval;
		be->changed = true;
	}
	T& operator=(const T& other){
		*be->front = other;
		be->changed = true;
		return(*be->front);
	}
	operator T() const {
		return(*be->back);
	}
	Buffered(){
		be = std::make_shared<Buffered_base_t<T>>();
		currentBufferManager.bufferedObjs.push_back(std::static_pointer_cast<Buffered_base>(be));
	}
	Buffered(const T& val){
		be = std::make_shared<Buffered_base_t<T>>(val);
		currentBufferManager.bufferedObjs.push_back(std::static_pointer_cast<Buffered_base>(be));
	}
	~Buffered(){
		be->toDelete = true;
	}
};
