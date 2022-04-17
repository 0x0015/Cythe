#include "Shape.hpp"

class RectangleShape : public Shape{
public:
	Buffered<bool> rounded = false;
	Buffered<float> radius = 0;
	Buffered<std::pair<float, float>> size;
	void Initialize();
	void Load();
	void Draw();
	void Update();
	~RectangleShape();
};
