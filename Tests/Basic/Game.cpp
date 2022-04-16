#include "Game.hpp"

void Game::Update(){
	Cythe::Update();
}

void Game::Initialize(){
	resolution = {720, 480};
	
	Cythe::Initialize();
}

void Game::Load(){
	Cythe::Load();
}

void Game::Draw(){
	Cythe::Draw();
}
