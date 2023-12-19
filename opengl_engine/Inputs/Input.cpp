#include "Input.h"
#include <iostream>

std::unordered_map<int, KeyState> Input::keys;
std::unordered_map<uint8_t, std::vector<int>> Input::pendingKeys;
std::unordered_map<uint8_t, std::unordered_map<int, KeyState>> Input::processingKeys;

void Input::InitializeArrays()
{
	processingKeys.reserve(3);
	pendingKeys.reserve(3);
}

void Input::UpdateKeys(uint8_t currentFrameIndex)
{
	uint8_t frame_minus_one = FrameIndexMinus(currentFrameIndex);
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
