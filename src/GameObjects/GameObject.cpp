#include "GameObject.hpp"
#include <numbers>
#include "../Cythe.hpp"
#include "../Logger/Logger.hpp"

void GameObject::Initialize(){

}
void GameObject::Load(){

}
void GameObject::Draw(){

}
void GameObject::Update(){

}
void GameObject::Spawn(){

}
GameObject::~GameObject(){
	Logger::log("Deleting GameObject ", name, ": ",this);
}
void GameObject::moveAtAngle(float angle, float units){
	float pos1 = position.get().first + units * std::cos(angle * (std::numbers::pi/(float)180));
	float pos2 = position.get().second + units * std::sin(angle * (std::numbers::pi/(float)180));
	position = std::make_pair(pos1, pos2);
	//std::cout<<"moveAtAngle:  angle="<<angle<<" move by ("<<units * std::cos(angle * ((float)std::numbers::pi/(float)180))<<", "<<units * std::sin(angle * ((float)std::numbers::pi/(float)180))<<std::endl;

}
