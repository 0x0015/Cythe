#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_gpu.h>
#include "GameObjects/RenderObject.hpp"
 
class TPScheduler;
class InputHandler;
class AssetLoader;

class Cythe : public RenderObject{
public:
	std::shared_ptr<TPScheduler> TPSchedule;
	std::shared_ptr<InputHandler> Input;
	std::shared_ptr<AssetLoader> Assets;
	std::string WindowTitle = "Hello Cythe";
	SDL_Event event;
	GPU_Target* window;
	bool Running = false;
	unsigned int ticks = 0;
	virtual void Initialize();
	virtual void Load();
	virtual void Update();
	virtual void Draw();
	void Run();
	Cythe();
	~Cythe();
};
