#include "Game.hpp"
#include "../../src/GlobalParams.hpp"

int main(){
	Game g;
	GlobalParams::debug = true;
	g.Run();
	return(0);
}
