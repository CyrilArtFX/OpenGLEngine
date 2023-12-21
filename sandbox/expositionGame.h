#pragma once
#include <Core/game.h>
#include <DefaultScenes/expositionScene.h>

class ExpositionGame : public Game
{
public:
	ExpositionGame();

	void load(Renderer* renderer_) override;
	void unloadGame() override;

	void updateGame(float dt) override;

private:
	ExpositionScene expositionScene;
};