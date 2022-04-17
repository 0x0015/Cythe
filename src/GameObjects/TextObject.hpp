#include "GameObject.hpp"

class NFont;

class TextObject : public GameObject{
public:
	NFont* font;
	std::string fontPath;
	Buffered<SDL_Color> drawColor = SDL_Color{0, 0, 0, 255};
	Buffered<std::string> text;
	Buffered<std::pair<float, float>> size = std::pair<float, float>(0,0);
	Buffered<int> defaultTextSize = 20;
	Buffered<float> scale = 1;
	void Initialize();
	void Load();
	void Update();
	void Draw();
	~TextObject();
	//blueprint
	static inline std::unordered_map<std::string, std::string> Blueprint = {
		{"position", "Buffered<std::pair<float,float>>"},
		{"SpawnTime", "int"},
		{"depth", "Buffered<float>"},
		{"name", "std::string"},
		{"fontPath", "std::string"},
		{"drawColor", "Buffered<SDL_Color>"},
		{"text", "Buffered<std::string>"},
		{"size", "Buffered<std::pair<float,float>>"},
		{"defaultTextSize", "Buffered<int>"},
		{"scale", "Buffered<float>"}
	};
	std::unordered_map<std::string, void*> Create_Bp = {
		{"position", &position},
		{"SpawnTime", &SpawnTime},
		{"depth", &depth},
		{"name", &name},
		{"fontPath", &fontPath},
		{"drawColor", &drawColor},
		{"text", &text},
		{"size", &size},
		{"defaultTextSize", &defaultTextSize},
		{"scale", &scale}
	};

};
