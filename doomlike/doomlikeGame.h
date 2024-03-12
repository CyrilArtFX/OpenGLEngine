#pragma once
#include <Core/game.h>
#include <Scenes/testFpsScene.h>
#include <Scenes/doomlikeLevelDebug.h>
#include <Scenes/doomlikeLevelStart.h>

#include <Actors/player.h>


class DoomlikeGame : public Game
{
public:
	DoomlikeGame();

	void updateGame(float dt) override;

	Camera& getActiveCamera() override;

	Player* getPlayer() { return &player; }

	void restartLevel();

protected:
	void loadGameAssets() override;
	void loadGame() override;

	void unloadGame() override;

private:
	void loadLevel(int index);

	//  scenes
	TestFpsScene testScene;
	DoomlikeLevelDebug levelDebugScene;
	DoomlikeLevelStart levelStartScene;
	int currentLevel = 0;
	bool mustRestartLevel{ false };

	//  player
	Player player;
};

