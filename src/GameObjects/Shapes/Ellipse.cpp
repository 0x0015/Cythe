#include "Ellipse.hpp"
#include "../RenderObject.hpp"
#include "../../Cythe.hpp"

void Ellipse::Initialize(){

}

void Ellipse::Load(){

}

void Ellipse::Draw(){
	std::pair<float, float> rad;
	if(size.get() == std::pair<float, float>(0, 0)){
		rad = std::pair<float, float>(radius, radius);
	}else{
		rad = size;
	}

	if(filled){
		GPU_EllipseFilled(renderWindow->window, position.get().first, position.get().second, rad.first, rad.second, rotation.get(), fillColor.get());

	}else{
		GPU_Ellipse(renderWindow->window, position.get().first, position.get().second, rad.first, rad.second, rotation.get(), fillColor.get());
	}
}

void Ellipse::Update(){

}

Ellipse::~Ellipse(){

}
