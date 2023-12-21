#pragma once
#include <Core/game.h>

class ExpositionGame : public Game
{
public:
	ExpositionGame();

	void load(Renderer* renderer_) override;
	void unloadGame() override;

	void updateGame(float dt) override;
};