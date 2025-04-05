#pragma once
#include <Maths/vector2.h>
#include <glad/glad.h>
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
	//  global
	static void Initialize();
	static void UpdateInputSystem();

	//  keys
	static KeyState GetKeyState(int key);
	static bool IsKeyUp(int key);
	static bool IsKeyDown(int key);
	static bool IsKeyPressed(int key);
	static bool IsKeyReleased(int key);

	//  mouse movement
	static Vector2 GetMousePos();
	static Vector2 GetMouseDelta();

	//  mouse scroll
	static float GetScrollOffset();


	//  glfw events
	static void ProcessMouse(GLFWwindow* glWindow, double xpos, double ypos);
	static void ProcessScroll(GLFWwindow* glWindow, double xoffset, double yoffset);
	static void ProcessKeyboard(GLFWwindow* glWindow, int key, int scancode, int action, int mods);
	static void ProcessMouseButton(GLFWwindow* glWindow, int button, int action, int mods);

private:
	//  keys
	static void ProcessKey(uint8_t processFrameIndex, int key, KeyState state);

	static std::unordered_map<int, KeyState> keys;
	static std::unordered_map<uint8_t, std::vector<int>> pendingKeys;
	static std::unordered_map<uint8_t, std::unordered_map<int, KeyState>> processingKeys;


	//  mouse movement
	static void ProcessMouseMovement(double mousePosX, double mousePosY);

	static bool firstMouseDelta;
	static Vector2 futureMousePos;
	static Vector2 currentMousePos;
	static Vector2 deltaMousePos;


	//  mouse scroll
	static void ProcessMouseScroll(double mouseScroll);

	static float futureScrollOffset;
	static float currentScrollOffset;


	//  frame index system
	static uint8_t FrameIndexPlus(uint8_t frameIndex);
	static uint8_t FrameIndexMinus(uint8_t frameIndex);

	static uint8_t frameIndex;
};