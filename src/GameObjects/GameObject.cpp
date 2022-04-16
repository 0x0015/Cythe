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
	position.first += units * std::cos(angle * (std::numbers::pi/(float)180));
	position.second += units * std::sin(angle * (std::numbers::pi/(float)180));
	//std::cout<<"moveAtAngle:  angle="<<angle<<" move by ("<<units * std::cos(angle * ((float)std::numbers::pi/(float)180))<<", "<<units * std::sin(angle * ((float)std::numbers::pi/(float)180))<<std::endl;

}
