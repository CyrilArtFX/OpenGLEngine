#pragma once
#include <Core/game.h>
#include <Scenes/testFpsScene.h>

#include <Actors/player.h>


class DoomlikeGame : public Game
{
public:
	DoomlikeGame();

	void updateGame(float dt) override;

	Camera& getActiveCamera() override;

protected:
	void loadGameAssets() override;
	void loadGame() override;

	void unloadGame() override;

private:
	//  scenes
	TestFpsScene testScene;

	//  player
	Player player;
};

