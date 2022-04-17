#pragma once
#include "GameObject.hpp"
#include <vector>
#include <list>
#include <memory>

class RenderObject : public GameObject{
public:
	std::list<std::shared_ptr<GameObject>> GameObjects;
	template<typename T> std::shared_ptr<T> FindObject(std::string name = ""){	
		if(name == ""){
			for(auto& o : GameObjects){
				T* GOi = dynamic_cast<T*>(o.get());
				//std::cout<<"Dynamically casting"<<GOi<<std::endl;
				if(GOi != 0){
					//std::cout<<"Successfully dynamically casted"<<std::endl;
					return(std::dynamic_pointer_cast<T>(o));
				}
			}
		}else{
			for(auto& o : GameObjects){
				T* GOi = dynamic_cast<T*>(o.get());
				//std::cout<<"Dynamically casting name "<<name<<GOi<<std::endl;
				if(GOi != 0){
					//std::cout<<"Successfully dynamically casted"<<std::endl;
					if(o->name == name){
						return(std::dynamic_pointer_cast<T>(o));
					}
				}
			}
		}
		return(0);
	}
	template<typename T> std::shared_ptr<T> FindObjectRecursive(std::string name = ""){
		if(name == ""){
			for(auto& o : GameObjects){
				T* GOi = dynamic_cast<T*>(o.get());
				//std::cout<<"Dynamically casting"<<GOi<<std::endl;
				if(GOi != 0){
					//std::cout<<"Successfully dynamically casted"<<std::endl;
					return(std::dynamic_pointer_cast<T>(o));
				}
			}
		}else{
			for(auto& o : GameObjects){
				T* GOi = dynamic_cast<T*>(o.get());
				//std::cout<<"Dynamically casting name "<<name<<GOi<<std::endl;
				if(GOi != 0){
					//std::cout<<"Successfully dynamically casted"<<std::endl;
					if(o->name == name){
						return(std::dynamic_pointer_cast<T>(o));
					}
				}
			}
		}
		//in order to get here you have to have not found either named or unnamed
		if(renderWindow){
			if(renderWindow != this){
				return(renderWindow->FindObjectRecursive<T>(name));
			}
		}
		//if(mainWindow->debug){NEVER MESS WITH THIS.  if you do IT MEANS DEATH(eg. don't try to include the main class from this file)
		//	std::cout<<"couldn't find object "<<name<<" in recursive check"<<std::endl;
		//}
		return(0);
	}
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
	void printHirearchy();
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
