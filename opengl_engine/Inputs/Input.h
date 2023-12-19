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
	static void InitializeArrays();
	static void UpdateKeys(uint8_t currentFrameIndex);

	static void ProcessKey(uint8_t processFrameIndex, int key, KeyState state);
	
	static KeyState GetKeyState(int key);
	static bool IsKeyUp(int key);
	static bool IsKeyDown(int key);
	static bool IsKeyPressed(int key);
	static bool IsKeyReleased(int key);


	static uint8_t FrameIndexPlus(uint8_t frameIndex);
	static uint8_t FrameIndexMinus(uint8_t frameIndex);

private:
	static std::unordered_map<int, KeyState> keys;
	static std::unordered_map<uint8_t, std::vector<int>> pendingKeys;
	static std::unordered_map<uint8_t, std::unordered_map<int, KeyState>> processingKeys;
};

