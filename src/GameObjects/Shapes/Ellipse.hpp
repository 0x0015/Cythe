#include "Shape.hpp"

class Ellipse : public Shape{
	Buffered<float> radius = 0;
	Buffered<std::pair<float, float>> size = std::pair<float, float>(0, 0);
	Buffered<float> rotation;
	void Initialize();
	void Load();
	void Draw();
	void Update();
	~Ellipse();
};
