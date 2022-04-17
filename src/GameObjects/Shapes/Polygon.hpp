#include "Shape.hpp"
#include <vector>

class Polygon : public Shape{
	Buffered<std::vector<std::pair<float, float>>> vertices;
	void Initialize();
	void Load();
	void Draw();
	void Update();
	~Polygon();
};
