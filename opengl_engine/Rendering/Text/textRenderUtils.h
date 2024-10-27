#pragma once
#include <Maths/Vector2Int.h>

struct FontCharacter
{
	unsigned int TextureID;
	Vector2Int Size;
	Vector2Int Bearing;
	int Advance;
};