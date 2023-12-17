#include "Input.h"
#include <iostream>

std::unordered_map<SDL_Scancode, KeyState> Input::keys;
std::vector<SDL_Scancode> Input::pendingKeys;

void Input::UpdateKeys()
{
	if (!pendingKeys.empty())
	{
		for (auto itr = pendingKeys.begin(); itr != pendingKeys.end(); itr++)
		{
			SDL_Scancode key_code = *itr;
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

	int mouse_pos_x, mouse_pos_y;
	Uint32 mouse_state = SDL_GetMouseState(&mouse_pos_x, &mouse_pos_y); //  register mouse position and get mouse button states
	//mousePosition = Vector2{ mouse_pos_x * 1.0f, mouse_pos_y * 1.0f };

	// SDL Event
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		std::cout << "bruh\n";
		switch (event.type) //  register all type of keys (keyboard) in the map when they are pressed or released
		{
		case SDL_KEYDOWN: //  register the key as pressed in the map
			if (keys.find(event.key.keysym.scancode) == keys.end())
			{
				keys.emplace(event.key.keysym.scancode, KeyState::KeyPressed);
				pendingKeys.push_back(event.key.keysym.scancode);
			}
			else
			{
				if (keys[event.key.keysym.scancode] != KeyState::KeyDown) //  prevent key to be set as pressed every two frames
				{
					keys[event.key.keysym.scancode] = KeyState::KeyPressed;
					pendingKeys.push_back(event.key.keysym.scancode);
				}
			}
			break;

		case SDL_KEYUP: //  register the key as released in the map
			if (keys[event.key.keysym.scancode] != KeyState::KeyUp) //  prevent key to be set as released every two frames
			{
				keys[event.key.keysym.scancode] = KeyState::KeyReleased;
				pendingKeys.push_back(event.key.keysym.scancode);
			}
			break;
		}
	}

	//  register mouse button manually cause the way SDL treat them is different of keyboard inputs
	
	if ((mouse_state & 1) == 1) //  left mouse button is currently down
	{
		if (keys.find(SDL_MOUSE_LEFT) == keys.end())
		{
			keys.emplace(SDL_MOUSE_LEFT, KeyState::KeyPressed);
			pendingKeys.push_back(SDL_MOUSE_LEFT);
		}
		else
		{
			if (keys[SDL_MOUSE_LEFT] != KeyState::KeyDown)
			{
				keys[SDL_MOUSE_LEFT] = KeyState::KeyPressed;
				pendingKeys.push_back(SDL_MOUSE_LEFT);
			}
		}
	}
	else //  left mouse button is currently up
	{
		if (keys[SDL_MOUSE_LEFT] != KeyState::KeyUp)
		{
			keys[SDL_MOUSE_LEFT] = KeyState::KeyReleased;
			pendingKeys.push_back(SDL_MOUSE_LEFT);
		}
	}

	if ((mouse_state & 2) == 2) //  middle mouse button is currently down
	{
		if (keys.find(SDL_MOUSE_MIDDLE) == keys.end())
		{
			keys.emplace(SDL_MOUSE_MIDDLE, KeyState::KeyPressed);
			pendingKeys.push_back(SDL_MOUSE_MIDDLE);
		}
		else
		{
			if (keys[SDL_MOUSE_MIDDLE] != KeyState::KeyDown)
			{
				keys[SDL_MOUSE_MIDDLE] = KeyState::KeyPressed;
				pendingKeys.push_back(SDL_MOUSE_MIDDLE);
			}
		}
	}
	else //  middle mouse button is currently up
	{
		if (keys[SDL_MOUSE_MIDDLE] != KeyState::KeyUp)
		{
			keys[SDL_MOUSE_MIDDLE] = KeyState::KeyReleased;
			pendingKeys.push_back(SDL_MOUSE_MIDDLE);
		}
	}

	if ((mouse_state & 4) == 4) //  right mouse button is currently down
	{
		if (keys.find(SDL_MOUSE_RIGHT) == keys.end())
		{
			keys.emplace(SDL_MOUSE_RIGHT, KeyState::KeyPressed);
			pendingKeys.push_back(SDL_MOUSE_RIGHT);
		}
		else
		{
			if (keys[SDL_MOUSE_RIGHT] != KeyState::KeyDown)
			{
				keys[SDL_MOUSE_RIGHT] = KeyState::KeyPressed;
				pendingKeys.push_back(SDL_MOUSE_RIGHT);
			}
		}
	}
	else //  right mouse button is currently up
	{
		if (keys[SDL_MOUSE_RIGHT] != KeyState::KeyUp)
		{
			keys[SDL_MOUSE_RIGHT] = KeyState::KeyReleased;
			pendingKeys.push_back(SDL_MOUSE_RIGHT);
		}
	}
}


KeyState Input::GetKeyState(SDL_Scancode key)
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

bool Input::IsKeyUp(SDL_Scancode key)
{
	KeyState state = GetKeyState(key);
	return state == KeyState::KeyUp || state == KeyState::KeyReleased;
}

bool Input::IsKeyDown(SDL_Scancode key)
{
	KeyState state = GetKeyState(key);
	return state == KeyState::KeyDown || state == KeyState::KeyPressed;
}

bool Input::IsKeyPressed(SDL_Scancode key)
{
	KeyState state = GetKeyState(key);
	return state == KeyState::KeyPressed;
}

bool Input::IsKeyReleased(SDL_Scancode key)
{
	KeyState state = GetKeyState(key);
	return state == KeyState::KeyReleased;
}
