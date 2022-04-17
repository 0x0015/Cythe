#include "Arc.hpp"
#include "../RenderObject.hpp"
#include "../../Cythe.hpp"
void Arc::Initialize(){

}

void Arc::Load(){

}

void Arc::Draw(){
	if(filled){
		GPU_Arc(renderWindow->window, position.get().first, position.get().second, radius.get(), startAngle.get(), endAngle.get(), fillColor.get());
	}else{
		GPU_ArcFilled(renderWindow->window, position.get().first, position.get().second, radius.get(), startAngle.get(), endAngle.get(), fillColor.get());
	}
}

void Arc::Update(){

}

Arc::~Arc(){

}
