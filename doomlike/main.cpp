#define STB_IMAGE_IMPLEMENTATION

#include <Core/engine.h>
#include <Scenes/testFpsScene.h>


int main()
{
	Engine engine;
	bool is_engine_init = engine.initialize();

	if (!is_engine_init) return -1;

	engine.loadScene(std::make_shared<TestFpsScene>());

	engine.run();
	engine.close();

	return 0;
}