#pragma once
#include <Maths/Vector2Int.h>
#include <Maths/Vector2.h>

struct FontCharacter
{
	int TextureID;
	Vector2Int Size;
	Vector2Int Bearing;
	int Advance;
};