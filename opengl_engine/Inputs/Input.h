#pragma once
#include <glfw/glfw3.h>
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
	
	static KeyState GetKeyState(int key);
	static bool IsKeyUp(int key);
	static bool IsKeyDown(int key);
	static bool IsKeyPressed(int key);
	static bool IsKeyReleased(int key);

private:
	static std::unordered_map<int, KeyState> keys;
	static std::vector<int> pendingKeys;
};

