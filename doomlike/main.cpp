#include <Core/engine.h>
#include "doomlikeGame.h"


int main()
{
	Engine engine;
	bool is_engine_init = engine.initialize();

	if (!is_engine_init) return -1;

	engine.loadGame(std::make_shared<DoomlikeGame>());

	engine.run();
	engine.close();

	return 0;
}