#include "Input.h"

std::unordered_map<int, KeyState> Input::keys;
std::unordered_map<uint8_t, std::vector<int>> Input::pendingKeys;
std::unordered_map<uint8_t, std::unordered_map<int, KeyState>> Input::processingKeys;

bool Input::firstMouseDelta;
Vector2 Input::futureMousePos;
Vector2 Input::currentMousePos;
Vector2 Input::deltaMousePos;

float Input::futureScrollOffset;
float Input::currentScrollOffset;

uint8_t Input::frameIndex;


void Input::Initialize()
{
	processingKeys.reserve(3);
	pendingKeys.reserve(3);

	firstMouseDelta = true;
	futureMousePos = Vector2::zero;
	currentMousePos = Vector2::zero;
	deltaMousePos = Vector2::zero;

	futureScrollOffset = 0.0f;
	currentScrollOffset = 0.0f;

	frameIndex = 0;
}

void Input::UpdateInputSystem()
{
	//  update frame index;
	frameIndex = FrameIndexPlus(frameIndex);


	uint8_t frame_minus_one = FrameIndexMinus(frameIndex);
	uint8_t frame_minus_two = FrameIndexMinus(frame_minus_one);

	//  register keys that were processed last frame
	if (!processingKeys[frame_minus_one].empty())
	{
		for (auto key_process : processingKeys[frame_minus_one])
		{
			keys[key_process.first] = key_process.second;
			pendingKeys[frame_minus_one].push_back(key_process.first);
		}

		processingKeys[frame_minus_one].clear();
	}

	//  update keys that were pending (those keys were registered two frames before)
	if (!pendingKeys[frame_minus_two].empty())
	{
		for (auto key_pending : pendingKeys[frame_minus_two])
		{
			switch (GetKeyState(key_pending))
			{
			case KeyState::KeyPressed:
				keys[key_pending] = KeyState::KeyDown;
				break;

			case KeyState::KeyReleased:
				keys[key_pending] = KeyState::KeyUp;
				break;
			}
		}

		pendingKeys[frame_minus_two].clear();
	}

	//  update mouse position
	deltaMousePos = currentMousePos - futureMousePos;
	currentMousePos = futureMousePos;

	//  update scroll offset
	currentScrollOffset = futureScrollOffset;
	futureScrollOffset = 0.0f;
}


void Input::ProcessKey(uint8_t processFrameIndex, int key, KeyState state)
{
	//  register the key in the process wait list
	processingKeys[processFrameIndex][key] = state;
}

KeyState Input::GetKeyState(int key)
{
	if (keys.find(key) == keys.end())
	{
		return KeyState::KeyUp;
	}
	else
	{
		return keys[key];
	}
}

bool Input::IsKeyUp(int key)
{
	KeyState state = GetKeyState(key);
	return state == KeyState::KeyUp || state == KeyState::KeyReleased;
}

bool Input::IsKeyDown(int key)
{
	KeyState state = GetKeyState(key);
	return state == KeyState::KeyDown || state == KeyState::KeyPressed;
}

bool Input::IsKeyPressed(int key)
{
	KeyState state = GetKeyState(key);
	return state == KeyState::KeyPressed;
}

bool Input::IsKeyReleased(int key)
{
	KeyState state = GetKeyState(key);
	return state == KeyState::KeyReleased;
}


void Input::ProcessMouseMovement(double mousePosX, double mousePosY)
{
	futureMousePos = Vector2{ (float)mousePosX, (float)mousePosY };
	if (firstMouseDelta)
	{
		currentMousePos = futureMousePos;
		firstMouseDelta = false;
	}
}

Vector2 Input::GetMousePos()
{
	return currentMousePos;
}

Vector2 Input::GetMouseDelta()
{
	return deltaMousePos;
}

void Input::ProcessMouseScroll(double mouseScroll)
{
	futureScrollOffset += (float)mouseScroll;
}

float Input::GetScrollOffset()
{
	return currentScrollOffset;
}



void Input::ProcessMouse(GLFWwindow* glWindow, double xpos, double ypos)
{
	ProcessMouseMovement(xpos, ypos);
}

void Input::ProcessScroll(GLFWwindow* glWindow, double xoffset, double yoffset)
{
	ProcessMouseScroll(yoffset);
}

void Input::ProcessKeyboard(GLFWwindow* glWindow, int key, int scancode, int action, int mods)
{
	switch (action)
	{
	case GLFW_PRESS:
		ProcessKey(frameIndex, key, KeyState::KeyPressed);
		break;

	case GLFW_REPEAT:
		//  currently doesn't use repeat, but may in the future
		break;

	case GLFW_RELEASE:
		ProcessKey(frameIndex, key, KeyState::KeyReleased);
		break;
	}
}

void Input::ProcessMouseButton(GLFWwindow* glWindow, int button, int action, int mods)
{
	switch (action)
	{
	case GLFW_PRESS:
		Input::ProcessKey(frameIndex, button, KeyState::KeyPressed);
		break;

	case GLFW_RELEASE:
		Input::ProcessKey(frameIndex, button, KeyState::KeyReleased);
		break;
	}
}




uint8_t Input::FrameIndexPlus(uint8_t frameIndex)
{
	if (frameIndex < 2) return frameIndex + 1;
	else return 0;
}

uint8_t Input::FrameIndexMinus(uint8_t frameIndex)
{
	if (frameIndex > 0) return frameIndex - 1;
	else return 2;
}
