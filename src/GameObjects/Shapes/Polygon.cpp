#include "Polygon.hpp"
#include "../RenderObject.hpp"
#include "../../Cythe.hpp"

void Polygon::Initialize(){

}

void Polygon::Load(){

}

void Polygon::Draw(){
	std::vector<float> verts;
	for(int i=0;i<vertices.get().size();i++){
		verts.push_back((position.get().first + vertices.get()[i].first));
		verts.push_back((position.get().second + vertices.get()[i].second));
	}
	float* float_verts = &verts[0];
	if(filled){
		GPU_Polygon(renderWindow->window, vertices.get().size(), float_verts, fillColor);
	}else{
		GPU_PolygonFilled(renderWindow->window, vertices.get().size(), float_verts, fillColor);

	}
}

void Polygon::Update(){

}

Polygon::~Polygon()
{

}
