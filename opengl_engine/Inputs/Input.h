#pragma once
#include <SDL/SDL.h>
#include <unordered_map>
#include <vector>


enum KeyState
{
	Up,
	Down,
	Pressed,
	Released
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
	std::unordered_map<SDL_Scancode, KeyState> keys;
	std::vector<SDL_Scancode> pendingKeys;
};

