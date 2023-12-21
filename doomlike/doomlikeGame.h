#pragma once
#include <Core/game.h>
#include <Scenes/testFpsScene.h>

class DoomlikeGame : public Game
{
public:
	DoomlikeGame();

	void load(Renderer* renderer_) override;
	void unloadGame() override;

	void updateGame(float dt) override;

private:
	TestFpsScene testScene;
};

