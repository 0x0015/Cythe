#include "Shape.hpp"

class Arc : public Shape{
	Buffered<float> radius = 0;
	Buffered<float> startAngle;
	Buffered<float> endAngle;
	void Initialize();
	void Load();
	void Draw();
	void Update();
	~Arc();
};
