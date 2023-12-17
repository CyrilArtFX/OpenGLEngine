#pragma once
#include <SDL/SDL.h>
#include <SDL/SDL_scancode.h>
#include <unordered_map>
#include <vector>


enum KeyState : uint8_t
{
	KeyUp = 0,
	KeyDown = 1,
	KeyPressed = 2,
	KeyReleased = 3
};


class Input
{
public:
	static void UpdateKeys();
	
	static KeyState GetKeyState(SDL_Scancode key);
	static bool IsKeyUp(SDL_Scancode key);
	static bool IsKeyDown(SDL_Scancode key);
	static bool IsKeyPressed(SDL_Scancode key);
	static bool IsKeyReleased(SDL_Scancode key);

private:
	static std::unordered_map<SDL_Scancode, KeyState> keys;
	static std::vector<SDL_Scancode> pendingKeys;
};

