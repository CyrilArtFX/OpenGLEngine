#include "Input.h"

std::unordered_map<int, KeyState> Input::keys;
std::vector<int> Input::pendingKeys;

void Input::UpdateKeys()
{
	if (!pendingKeys.empty())
	{
		for (auto itr = pendingKeys.begin(); itr != pendingKeys.end(); itr++)
		{
			int key_code = *itr;
			switch (GetKeyState(key_code))
			{
			case KeyState::KeyPressed:
				keys[key_code] = KeyState::KeyDown;
				break;
			case KeyState::KeyReleased:
				keys[key_code] = KeyState::KeyUp;
				break;
			}
		}
		pendingKeys.clear();
	}
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
