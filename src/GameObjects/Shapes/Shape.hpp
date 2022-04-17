#include "../GameObject.hpp"

class Shape : public GameObject{
public:
	Buffered<SDL_Color> fillColor;
	Buffered<bool> filled = false;
	void Initialize();
	void Load();
	void Draw();
	void Update();
	~Shape();
};
