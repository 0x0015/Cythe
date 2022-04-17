#include "Rectangle.hpp"
#include "../RenderObject.hpp"
#include "../../Cythe.hpp"

void RectangleShape::Initialize(){

}

void RectangleShape::Load(){

}

void RectangleShape::Draw(){
	GPU_Rect DestR;
	DestR.x = position.get().first;
	DestR.y = position.get().second;
	DestR.w = size.get().first;
	DestR.h = size.get().second;

	if(!filled){
		if(rounded){
			GPU_RectangleRound2(renderWindow->window, DestR, radius, fillColor);
		}else{
			GPU_Rectangle2(renderWindow->window, DestR, fillColor);
		}
	}else{
		if(rounded){
			GPU_RectangleRoundFilled2(renderWindow->window, DestR, radius, fillColor);
		}else{
			GPU_RectangleFilled2(renderWindow->window, DestR, fillColor);
		}
	}
}

void RectangleShape::Update(){

}

RectangleShape::~RectangleShape(){

}
