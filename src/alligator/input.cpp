#include "input.h"
#include <algorithm>

Input* Input::instance = nullptr;

void Input::Initialize()
{
	instance = new Input();
}

void Input::Dispose()
{
	delete instance;
}

bool Input::IsKeyDown(int key)
{
	return instance->m_keyStates[key];
}

Input::Input()
{
	std::fill(std::begin(m_keyStates), std::begin(m_keyStates) + ALLEGRO_KEY_MAX, false);
}

void Input::NotifyKeyDown(int key)
{
	instance->m_keyStates[key] = true;

	if( instance->m_inputProcessor != nullptr )
	{
		instance->m_inputProcessor->keyDown(key);
	}
}

void Input::NotifyKeyUp(int key)
{
	instance->m_keyStates[key] = false;

	if( instance->m_inputProcessor != nullptr )
	{
		instance->m_inputProcessor->keyUp(key);
	}
}

void Input::SetInputProcessor(IInputProcessor::Ptr inputProcessor)
{
	instance->m_inputProcessor = inputProcessor;
}
