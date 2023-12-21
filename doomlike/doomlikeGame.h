#pragma once
#include <Core/game.h>
#include <Scenes/testFpsScene.h>

class DoomlikeGame : public Game
{
public:
	DoomlikeGame();

	void updateGame(float dt) override;

protected:
	void loadGameAssets() override;
	void loadGame() override;

	void unloadGame() override;

private:
	TestFpsScene testScene;
};

