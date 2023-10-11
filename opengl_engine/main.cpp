//  if this line is not here, the project don't compile (bruh)
#define STB_IMAGE_IMPLEMENTATION

#include <Core/game.h>


int main()
{
	auto& game = Game::instance();
	bool is_game_init = game.initialize();

	if (!is_game_init) return -1;

	game.loop();
	game.close();

	return 0;
}