#pragma once
#include <Core/game.h>
#include <Scenes/testFpsScene.h>
#include <Scenes/doomlikeLevelDebug.h>
#include <Scenes/doomlikeLevelStart.h>
#include <Scenes/doomlikeLevelAdvanced.h>

//#include <Actors/player.h>


class DoomlikeGame : public Game
{
public:
	//Player* getPlayer() { return &player; }

	void restartLevel();
	void changeLevel(int levelIndex);

protected:
	void loadGameAssets() override;
	void loadGame() override;
	void unloadGame() override;
	void updateGame(float dt) override;

private:
	void loadLevel(int index);

	//  scenes
	TestFpsScene testScene;
	DoomlikeLevelDebug levelDebugScene;
	DoomlikeLevelStart levelStartScene;
	DoomlikeLevelAdvanced levelAdvancedScene;
	int currentLevel = 0;
	bool mustRestartLevel{ false };

	//  player
	//Player player;
};

