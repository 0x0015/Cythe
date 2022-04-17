#pragma once
#include <iostream>
#include <unordered_map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_gpu.h>
#include <memory>
#include "../DBuffer/Buffered.hpp"

class RenderObject;
class Cythe;

class GameObject{
public:
	Cythe* mainWindow;
	RenderObject* renderWindow;
	Buffered<std::pair<float, float>> position;
	int SpawnTime = 0;
	Buffered<float> depth;
	std::string name = "";
	bool toDelete = false;
	void moveAtAngle(float angle, float units);
	virtual void Initialize();
	virtual void Load();
	virtual void Draw();
	virtual void Update();
	virtual void Spawn();
	virtual ~GameObject();
	//blueprint
	static inline std::unordered_map<std::string, std::string> Blueprint = {
		{"position", "Buffered<std::pair<float,float>>"},
		{"SpawnTime", "int"},
		{"depth", "Buffered<float>"},
		{"name", "std::string"}
	};
	std::unordered_map<std::string, void*> Create_Bp = {
		{"position", &position},
		{"SpawnTime", &SpawnTime},
		{"depth", &depth},
		{"name", &name}
	};
};
