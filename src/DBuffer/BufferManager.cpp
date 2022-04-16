#include "BufferManager.hpp"
#include "Buffered.hpp"

BufferManager_::BufferManager_(){}


void BufferManager_::swap(){
	for(auto it = bufferedObjs.begin();it!=bufferedObjs.end();it++){
		if((*it)->toDelete){
			bufferedObjs.erase(it);
		}else{
			if((*it)->changed){
				(*it)->swap();
			}
		}
	}
}
