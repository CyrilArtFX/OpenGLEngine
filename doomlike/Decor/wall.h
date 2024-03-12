#pragma once

class Renderer;


class Wall
{
	//  TODO: make "built-in" objects for walls with an option to set a facing direction
	//  and having the mesh rotation and box collision setup automatically


public:
	static void SetupWalls(Renderer& rendererRef);
	static void ReleaseWalls(Renderer& rendererRef);
};