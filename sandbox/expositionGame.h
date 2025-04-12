#pragma once
#include <Core/game.h>
#include <DefaultScenes/expositionScene.h>
#include <DefaultScenes/demoreelSceneOne.h>


class ExpositionGame : public Game
{
public:
	ExpositionGame();

	void updateGame(float dt) override;

protected:
	void loadGameAssets() override;
	void loadGame() override;
	void unloadGame() override;

	void loadProps(const std::string& propsName, bool emissive = false);

private:
	ExpositionScene expositionScene;
	DemoreelSceneOne demoreelSceneOne;

	Entity* test_game_entity{ nullptr };
};