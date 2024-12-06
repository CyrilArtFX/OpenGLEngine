#pragma once

class DefaultAssets
{
public:
	/**
	* Load every default assets (textures, meshes, materials)
	*/
	static void LoadDefaultAssets();

	/**
	* Load assets that are needed for the engine to run properly
	*/
	static void LoadEngineAssets();
};

