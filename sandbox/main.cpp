#define STB_IMAGE_IMPLEMENTATION

#include <Core/engine.h>
#include "expositionGame.h"


int main()
{
	Engine engine;
	bool is_engine_init = engine.initialize();

	if (!is_engine_init) return -1;

	engine.loadGame(std::make_shared<ExpositionGame>());

	engine.run();
	engine.close();

	return 0;
}