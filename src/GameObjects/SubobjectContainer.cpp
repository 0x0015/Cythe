#include "SubobjectContainer.hpp"
#include "Sprite.hpp"
#include "../Cythe.hpp"
#include "../TPScheduler/TPScheduler.hpp"
#include <algorithm>
#include <execution>

void SubobjectContainer::Initialize(){
	for(auto& o : GameObjects){
		o->mainWindow = mainWindow;
		o->renderWindow = renderWindow;
	}
	for(auto& o : GameObjects){
		o->Initialize();
	}
}
void SubobjectContainer::Load(){
	for(auto& o : GameObjects){
		o->Load();
	}
}
void SubobjectContainer::Draw(){
	
	for(auto& o : GameObjects){
		o->Draw();
	}
}
void SubobjectContainer::Update(){
	for(auto& o : GameObjects){
		mainWindow->TPSchedule->queueFunction(1, [&](){o->Update();});
	}
	//for(int i=0;i<GameObjects.size();i++){
	//	if(GameObjects[i]->toDelete){
	//		delete(GameObjects[i]);
	//		GameObjects.erase(GameObjects.begin()+i);
	//		i--;
	//		continue;
	//	}else{
	//		GameObjects[i]->Update();
	//	}
	//}
	//std::sort(GameObjects.begin(), GameObjects.end(), [](const std::shared_ptr<GameObject> obj1, const std::shared_ptr<GameObject> obj2){
	//		return(obj1->depth < obj2->depth);
	//		});//sort of clunky, using std::sort to sort the z buffer, but I guess it's fine.

}


void SubobjectContainer::printHirearchy(){
	std::cout<<"{"<<std::endl;
	for(auto& o : GameObjects){
		if(dynamic_cast<RenderObject*>(o.get()) != 0){
			// is a render object
			std::cout<<typeid(*o).name()<<" "<<o->name;
			dynamic_cast<RenderObject*>(o.get())->printHirearchy();
		}else{
			std::cout<<typeid(*o).name()<<" "<<o->name<<std::endl;
		}
	}
	std::cout<<"}"<<std::endl;
}

void SubobjectContainer::RemoveDeletedChildren(){
	for(auto i = GameObjects.begin(); i != GameObjects.end();){
		if((*i)->toDelete){
			GameObjects.erase(i);
		}else{
			if(dynamic_cast<SubobjectContainer*>((*i).get()) != 0){
				dynamic_cast<SubobjectContainer*>((*i).get())->RemoveDeletedChildren();
			}
			i++;
		}
	}
}

SubobjectContainer::~SubobjectContainer(){
}
