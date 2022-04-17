#pragma once
#include "GameObject.hpp"
#include "SubobjectContainer.hpp"
#include <vector>
#include <list>
#include <memory>

class RenderObject : public SubobjectContainer{
public:
	GPU_Target* window = 0;
	Buffered<std::pair<float, float>> size;
	std::pair<int, int> resolution;
	Buffered<float> rotation;
	Buffered<std::pair<float, float>> center;
	//SDL_Surface* ImageSurface = 0;
	//SDL_Texture* Texture = 0;
	GPU_Image* Image;
	GPU_Target* ImageTarget;
	std::string ImagePath = "";
	SDL_Color GetPixelColor(std::pair<int, int> pixelPos);
	void Initialize();
	void Load();
	void Draw();
	void Update();
	~RenderObject();
	//blueprint
	static inline std::unordered_map<std::string, std::string> Blueprint = {
		{"position", "Buffered<std::pair<float,float>>"},
		{"SpawnTime", "int"},
		{"depth", "Buffered<float>"},
		{"name", "std::string"},
		{"size", "Buffered<std::pair<float,float>>"},
		{"resolution", "std::pair<int,int>"},
		{"rotation", "Buffered<float>"},
		{"center", "Buffered<std::pair<float,float>>"},
		{"GameObjects", "std::vector<std::shared_ptr<GameObject>>"}
	};
	std::unordered_map<std::string, void*> Create_Bp = {
		{"position", &position},
		{"SpawnTime", &SpawnTime},
		{"depth", &depth},
		{"name", &name},
		{"size", &size},
		{"resolution", &resolution},
		{"rotation", &rotation},
		{"center", &center},
		{"GameObjects", &GameObjects}
	};

};
